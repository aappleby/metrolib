#include "metrolib/appbase/BoxPainter.h"

#include "metrolib/appbase/GLBase.h"
#include "metrolib/core/Check.h"
#include "metrolib/glad/glad.h"

#include <SDL2/SDL.h>

//-----------------------------------------------------------------------------

const char* box_glsl = R"(
layout(std140) uniform BoxUniforms {
  vec4  viewport;
  vec4  origin;
};

float remap(float x, float a1, float a2, float b1, float b2) {
  x = (x - a1) / (a2 - a1);
  x = x * (b2 - b1) + b1;
  return x;
}

uniform bool use_tex;

#ifdef _VERTEX_

layout(location = 0) in vec4  box_pos;
layout(location = 1) in ivec4 box_col;

out vec2 frag_tex;
out vec4 frag_col;

void main() {
  float corner_x = float((gl_VertexID >> 0) & 1);
  float corner_y = float((gl_VertexID >> 1) & 1);

  float quad_x = box_pos.x + box_pos.z * corner_x;
  float quad_y = box_pos.y + box_pos.w * corner_y;
  quad_x = quad_x * origin.z + origin.x;
  quad_y = quad_y * origin.w + origin.y;

  gl_Position = vec4(remap(quad_x, viewport.x, viewport.z, -1.0,  1.0),
                     remap(quad_y, viewport.y, viewport.w,  1.0, -1.0),
                     0.0,
                     1.0);

  float glyph_x = float((box_col.a >> 0) & 0xF);
  float glyph_y = float((box_col.a >> 4) & 0xF);
  frag_tex = vec2(glyph_x + corner_x, glyph_y + corner_y) * (1.0 / 16.0);

  frag_col = vec4(box_col) * (1.0 / 255.0);
}

#else

in vec2  frag_tex;
in vec4  frag_col;
out vec4 frag_out;

// Texture should be a 16x16 grid of icons
uniform sampler2D tex;

void main() {
  //frag_out = vec4(frag_tex, 0.0, 1.0);
  if (use_tex) {
    frag_out = vec4(texture(tex, frag_tex).rrr, 1.0) * vec4(frag_col.rgb, 1.0);
  }
  else {
    frag_out = vec4(frag_col.rgb, 1.0);
  }
}

#endif
)";

static uint32_t box_prog = 0;

//-----------------------------------------------------------------------------

void BoxPainter::init() {
  if (!box_prog) {
    box_prog = create_shader("box_glsl", box_glsl);
  }

  box_data_u32 = new uint32_t[max_box_bytes / sizeof(uint32_t)];
  box_data_f32 = reinterpret_cast<float*>(box_data_u32);

  box_vao = create_vao();
  box_vbo = create_vbo(max_box_bytes, nullptr);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 20, 0);
  glVertexAttribIPointer(1, 4, GL_UNSIGNED_BYTE, 20, (void*)16);
  glVertexAttribDivisor (0, 1);
  glVertexAttribDivisor (1, 1);

  box_ubo = create_ubo();
}

//-----------------------------------------------------------------------------

void BoxPainter::push_corner_corner(float ax, float ay, float bx, float by, uint32_t col) {
  box_data_f32[box_cursor++] = ax;
  box_data_f32[box_cursor++] = ay;
  box_data_f32[box_cursor++] = bx - ax;
  box_data_f32[box_cursor++] = by - ay;
  box_data_u32[box_cursor++] = col;

  CHECK_P(box_cursor * sizeof(uint32_t) < max_box_bytes);
}

void BoxPainter::push_corner_size(float x, float y, float w, float h, uint32_t col) {
  box_data_f32[box_cursor++] = x;
  box_data_f32[box_cursor++] = y;
  box_data_f32[box_cursor++] = w;
  box_data_f32[box_cursor++] = h;
  box_data_u32[box_cursor++] = col;

  CHECK_P(box_cursor * sizeof(uint32_t) < max_box_bytes);
}

//-----------------------------------------------------------------------------

void BoxPainter::render(Viewport view, dvec2 screen_size, double x, double y, float scale) {
  if (box_cursor == 0) return;
  int box_count = box_cursor / 5;
  update_vbo(box_vbo, box_count * bytes_per_box, box_data_u32);

  if (box_cursor == 0) return;

  bind_shader(box_prog);

  box_uniforms.viewport = {
    (float)view.screen_min(screen_size).x,
    (float)view.screen_min(screen_size).y,
    (float)view.screen_max(screen_size).x,
    (float)view.screen_max(screen_size).y
  };
  box_uniforms.origin = { x, y, scale, scale };
  update_ubo(box_ubo, sizeof(box_uniforms), &box_uniforms);
  bind_ubo(box_prog, "BoxUniforms", 0, box_ubo);

  bind_vao(box_vao);

  if (box_tex) {
    glUniform1i(glGetUniformLocation(box_prog, "use_tex"), 1);
    bind_texture(box_prog, "tex", 0, box_tex);
  }
  else {
    glUniform1i(glGetUniformLocation(box_prog, "use_tex"), 0);
  }

  glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, box_count);

  box_cursor = 0;
}

//-----------------------------------------------------------------------------
