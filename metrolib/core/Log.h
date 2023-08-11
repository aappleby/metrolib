#pragma once
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "metrolib/core/Utils.h"

//-----------------------------------------------------------------------------
// TinyLog - simple console log with color coding, indentation, and timestamps

struct TinyLog {
  int      muted = 0;
  bool     use_color = true;
  int      indentation = 0;
  bool     start_line = true;
  uint32_t current_color = 0xA0A0A0;

  static TinyLog& get() {
    static TinyLog log;
    return log;
  }

  void indent() { indentation += 2; }
  void dedent() { indentation -= 2; }
  void mute()   { muted++; }
  void unmute() { muted--; }
  void mono()   { use_color = false; }
  void color()  { use_color = true; }

  TinyLog& color(uint32_t color) {
    this->current_color = color;
    if (color && use_color) {
      printf("\u001b[38;2;%d;%d;%dm", (color >> 0) & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF);
    }
    else {
      printf("\u001b[0m");
    }
    return *this;
  }

  void put(int c) {
    if (muted) return;
    if (start_line && c == '\r') return;
    if (c == '\r') c = '\n';

    if (start_line) {
      auto old_color = current_color;
      color(0);
      printf("[%07.3f] ", timestamp());
      for (int j = 0; j < indentation; j++) fputc(' ', stdout);
      color(old_color);
    }

    start_line = c == '\n';
    fputc(c, stdout);
    fflush(stdout);
  }

  void write(const char* text, size_t size) {
    for (auto i = 0; i < size; i++) {
      put(text[i]);
    }
  }

  void vprint(const char* format, va_list args) {
    va_list args2;
    va_copy(args2, args);
    int size = vsnprintf(nullptr, 0, format, args2);
    va_end(args2);

    auto buffer = new char[size + 1];
    vsnprintf(buffer, size_t(size) + 1, format, args);
    write(buffer, size);
    delete[] buffer;
  }

  void print(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprint(format, args);
    va_end(args);
  }
};

#define LOG_SPAN(A)   TinyLog::get().write(A.begin, A.end - A.begin)

#define LOG(...)      TinyLog::get().color(0x00000000).print(__VA_ARGS__)
#define LOG_C(c, ...) TinyLog::get().color(c         ).print(__VA_ARGS__)
#define LOG_R(...)    TinyLog::get().color(0x008080FF).print(__VA_ARGS__)
#define LOG_G(...)    TinyLog::get().color(0x0080FF80).print(__VA_ARGS__)
#define LOG_B(...)    TinyLog::get().color(0x00FFA0A0).print(__VA_ARGS__)
#define LOG_Y(...)    TinyLog::get().color(0x0080FFFF).print(__VA_ARGS__)
#define LOG_W(...)    TinyLog::get().color(0x00FFFFFF).print(__VA_ARGS__)

#define LOG_INDENT()  TinyLog::get().indent()
#define LOG_DEDENT()  TinyLog::get().dedent()

struct LogIndenter {
  LogIndenter()  { TinyLog::get().indent(); }
  ~LogIndenter() { TinyLog::get().dedent(); }
};

#define LINE_CAT1(X,Y) LINE_CAT2(X,Y)
#define LINE_CAT2(X,Y) X##Y
#define LOG_INDENT_SCOPE() LogIndenter LINE_CAT1(indenter, __LINE__)

//-----------------------------------------------------------------------------
