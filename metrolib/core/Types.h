#pragma once

//------------------------------------------------------------------------------

//#ifdef _MSC_VER

//#include <span>
//typedef std::span<const char> cspan;

//#define debugbreak() __debugbreak();

//#endif

//------------------------------------------------------------------------------

#if 0
struct Sprite {
  uint8_t y;
  uint8_t x;
  uint8_t p;
  union {
    struct {
      uint8_t pad0 : 1;
      uint8_t pad1 : 1;
      uint8_t pad2 : 1;
      uint8_t pad3 : 1;
      uint8_t pal : 1;
      uint8_t flipX : 1;
      uint8_t flipY : 1;
      uint8_t pri : 1;
    } bits;
    uint8_t f;
  } flags;
};
#endif
