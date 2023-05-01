#pragma once

#include "metrolib/appbase/Viewport.h"

#include <string>

class DumpPainter {
public:

  void init_hex_u8();
  void init_hex_u32();
  void init_ascii();

  void dump(Viewport view, dvec2 screen_size,
            double world_x, double world_y,
            double scale_x, double scale_y,
            int bytes_per_row,
            int rows_per_block,
            vec4 color,
            const uint8_t* dump);

  int highlight_x = -1;
  int highlight_y = -1;

private:

  uint32_t dump_prog = 0;
  uint32_t dump_vao = 0;

  uint32_t dump_tab = 0;
  uint32_t glyph_tex = 0;

  uint32_t ruler_x_tab = 0;
  uint32_t ruler_y_tab = 0;

  int bytes_per_tile;
  int cells_per_tile;
  int tile_w;
  int tile_h;
  int cell_w;
  int cell_h;

  int32_t  offsets[16] = {0}; // Data offset per cell
  uint32_t shifts[16] = {0};  // Data shift per cell
  uint32_t masks[16] = {0};   // Data mask per cell
};
