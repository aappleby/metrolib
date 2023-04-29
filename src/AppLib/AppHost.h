#pragma once

#include "App.h"
#include "Viewport.h"

//-----------------------------------------------------------------------------

class AppHost {
public:
  AppHost(App* _app) { app = _app; }
  int app_main(int argc, const char** argv);

private:

  App* app = nullptr;

  bool quit = false;
  void* window = nullptr;
  void* gl_context = nullptr;

  uint32_t imgui_prog = 0;
  uint32_t imgui_tex = 0;
  uint32_t imgui_vao = 0;
  uint32_t imgui_vbo = 0;
  uint32_t imgui_ibo = 0;
};

//-----------------------------------------------------------------------------
