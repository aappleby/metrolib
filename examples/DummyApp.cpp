#include "DummyApp.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>

#include "symlinks/imgui/backends/imgui_impl_sdl3.h"
#include "symlinks/imgui/backends/imgui_impl_opengl3.h"

#include "metrolib/appbase/GLBase.h"

int main(int argc, char* argv[]) {
  // 1. Initialize SDL3
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return 1;
  }

  // 2. Set OpenGL Attributes
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  SDL_Window* window = SDL_CreateWindow(
    "SDL3 OpenGL",
    800, 600,
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
  );

  SDL_GLContext context = SDL_GL_CreateContext(window);

  SDL_GL_SetSwapInterval(1);


  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();

  ImGui_ImplSDL3_InitForOpenGL(window, context);
  ImGui_ImplOpenGL3_Init("#version 330");

  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);

      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    ImGui::Render();

    // --- Render with OpenGL ---
    float time = SDL_GetTicks() / 1000.0f;
    float red = 0.5f + 0.5f * sinf(time);
    float green = 0.5f + 0.5f * sinf(time + 2.0f);
    float blue = 0.5f + 0.5f * sinf(time + 4.0f);

    glClearColor(red, green, blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap front and back buffers
    SDL_GL_SwapWindow(window);
  }

  // 6. Clean Up
  SDL_GL_DestroyContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}





#if 0
#include "metrolib/appbase/GLBase.h"

#include <SDL2/SDL.h>

//-----------------------------------------------------------------------------

DummyApp::~DummyApp() {
};

const char* DummyApp::app_get_title() {
  return "DummyApp";
}

//-----------------------------------------------------------------------------

void DummyApp::app_init(int screen_w, int screen_h) {
  dvec2 screen_size(screen_w, screen_h);

  grid_painter.init(65536.0f, 65536.0f);
  text_painter.init();
  blitter.init();

  uint32_t pix[] = {
    0xFF00FFFF, 0xFF00FFFF, 0xFF00FFFF, 0xFF00FFFF,
    0xFF00FFFF, 0xFFFF00FF, 0xFFFF00FF, 0xFF00FFFF,
    0xFF00FFFF, 0xFFFF00FF, 0xFFFF00FF, 0xFF00FFFF,
    0xFF00FFFF, 0xFF00FFFF, 0xFF00FFFF, 0xFF00FFFF,
  };

  tex = create_texture_u32(4, 4, pix, false);

  view_control.init(screen_size);
}

//-----------------------------------------------------------------------------

void DummyApp::app_close() {
}

//-----------------------------------------------------------------------------

void DummyApp::app_update(dvec2 screen_size, double delta) {
  (void)delta;

  int mouse_x = 0, mouse_y = 0;
  dvec2 mouse_pos_screen(mouse_x, mouse_y);

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_MOUSEWHEEL) {
      //printf("wheel\n");
      view_control.on_mouse_wheel(mouse_pos_screen, screen_size, double(event.wheel.y) * 0.25);
    }

    if (event.motion.state & SDL_BUTTON_LMASK) {
      //printf("xrel %d\n", event.motion.xrel);
      //printf("yrel %d\n", event.motion.yrel);

      // Getting garbage xrel/yrel under WSLg
      if (abs(event.motion.xrel) < 1000 && abs(event.motion.yrel) < 1000) {
        view_control.pan(dvec2(event.motion.xrel, event.motion.yrel));
      }
    }
  }

  view_control.update(delta);
}

//-----------------------------------------------------------------------------

void DummyApp::app_render_frame(dvec2 screen_size, double delta) {
  (void)delta;

  auto& view = view_control.view_smooth_snap;

  grid_painter.render(view, screen_size);

  static int count = 0;
  text_painter.dprintf("Hello World %d\n", count++);
  text_painter.render(view, screen_size, 0, 0);

  blitter.blit(view, screen_size, tex, 128, 128, 32, 32);
}

//-----------------------------------------------------------------------------

void DummyApp::app_render_ui(dvec2 screen_size, double delta) {
  (void)screen_size;
  (void)delta;
}

//-----------------------------------------------------------------------------
#endif