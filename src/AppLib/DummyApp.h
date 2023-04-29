#pragma once

#include "App.h"
#include "GridPainter.h"
#include "TextPainter.h"
#include "Blitter.h"
#include "Viewport.h"

//-----------------------------------------------------------------------------

class DummyApp : public App {
public:
  ~DummyApp() override;

  const char* app_get_title() override;
  void app_init(int screen_w, int screen_h) override;
  void app_close() override;
  void app_update(dvec2 screen_size, double delta) override;
  void app_render_frame(dvec2 screen_size, double delta) override;
  void app_render_ui(dvec2 screen_size, double delta) override;

  GridPainter grid_painter;
  TextPainter text_painter;
  Blitter     blitter;
  ViewController view_control;

  int tex = 0;
};

//-----------------------------------------------------------------------------
