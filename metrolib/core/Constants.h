#pragma once

#include <stdint.h>

inline const char* byte_to_bits(uint8_t x) {
  static const char* tab[256] = {
    "0000:0000","0000:0001","0000:0010","0000:0011","0000:0100","0000:0101","0000:0110","0000:0111",
    "0000:1000","0000:1001","0000:1010","0000:1011","0000:1100","0000:1101","0000:1110","0000:1111",
    "0001:0000","0001:0001","0001:0010","0001:0011","0001:0100","0001:0101","0001:0110","0001:0111",
    "0001:1000","0001:1001","0001:1010","0001:1011","0001:1100","0001:1101","0001:1110","0001:1111",
    "0010:0000","0010:0001","0010:0010","0010:0011","0010:0100","0010:0101","0010:0110","0010:0111",
    "0010:1000","0010:1001","0010:1010","0010:1011","0010:1100","0010:1101","0010:1110","0010:1111",
    "0011:0000","0011:0001","0011:0010","0011:0011","0011:0100","0011:0101","0011:0110","0011:0111",
    "0011:1000","0011:1001","0011:1010","0011:1011","0011:1100","0011:1101","0011:1110","0011:1111",
    "0100:0000","0100:0001","0100:0010","0100:0011","0100:0100","0100:0101","0100:0110","0100:0111",
    "0100:1000","0100:1001","0100:1010","0100:1011","0100:1100","0100:1101","0100:1110","0100:1111",
    "0101:0000","0101:0001","0101:0010","0101:0011","0101:0100","0101:0101","0101:0110","0101:0111",
    "0101:1000","0101:1001","0101:1010","0101:1011","0101:1100","0101:1101","0101:1110","0101:1111",
    "0110:0000","0110:0001","0110:0010","0110:0011","0110:0100","0110:0101","0110:0110","0110:0111",
    "0110:1000","0110:1001","0110:1010","0110:1011","0110:1100","0110:1101","0110:1110","0110:1111",
    "0111:0000","0111:0001","0111:0010","0111:0011","0111:0100","0111:0101","0111:0110","0111:0111",
    "0111:1000","0111:1001","0111:1010","0111:1011","0111:1100","0111:1101","0111:1110","0111:1111",
    "1000:0000","1000:0001","1000:0010","1000:0011","1000:0100","1000:0101","1000:0110","1000:0111",
    "1000:1000","1000:1001","1000:1010","1000:1011","1000:1100","1000:1101","1000:1110","1000:1111",
    "1001:0000","1001:0001","1001:0010","1001:0011","1001:0100","1001:0101","1001:0110","1001:0111",
    "1001:1000","1001:1001","1001:1010","1001:1011","1001:1100","1001:1101","1001:1110","1001:1111",
    "1010:0000","1010:0001","1010:0010","1010:0011","1010:0100","1010:0101","1010:0110","1010:0111",
    "1010:1000","1010:1001","1010:1010","1010:1011","1010:1100","1010:1101","1010:1110","1010:1111",
    "1011:0000","1011:0001","1011:0010","1011:0011","1011:0100","1011:0101","1011:0110","1011:0111",
    "1011:1000","1011:1001","1011:1010","1011:1011","1011:1100","1011:1101","1011:1110","1011:1111",
    "1100:0000","1100:0001","1100:0010","1100:0011","1100:0100","1100:0101","1100:0110","1100:0111",
    "1100:1000","1100:1001","1100:1010","1100:1011","1100:1100","1100:1101","1100:1110","1100:1111",
    "1101:0000","1101:0001","1101:0010","1101:0011","1101:0100","1101:0101","1101:0110","1101:0111",
    "1101:1000","1101:1001","1101:1010","1101:1011","1101:1100","1101:1101","1101:1110","1101:1111",
    "1110:0000","1110:0001","1110:0010","1110:0011","1110:0100","1110:0101","1110:0110","1110:0111",
    "1110:1000","1110:1001","1110:1010","1110:1011","1110:1100","1110:1101","1110:1110","1110:1111",
    "1111:0000","1111:0001","1111:0010","1111:0011","1111:0100","1111:0101","1111:0110","1111:0111",
    "1111:1000","1111:1001","1111:1010","1111:1011","1111:1100","1111:1101","1111:1110","1111:1111"
  };
  return tab[x];
}

#if 0
constexpr uint32_t COL_DARK_GREY    = 0x00444444;
constexpr uint32_t COL_DARK_RED     = 0x00444488;
constexpr uint32_t COL_MID_RED      = 0x004444CC;

constexpr uint32_t COL_DARK_GREEN   = 0x00448844;
constexpr uint32_t COL_PALE_BROWN   = 0x005DA2A2;
constexpr uint32_t COL_ORANGE       = 0x004488CC;

constexpr uint32_t COL_MID_GREEN    = 0x0044CC44;
constexpr uint32_t COL_LIME         = 0x0044CC88;
constexpr uint32_t COL_MID_YELLOW   = 0x0066CCCC;

constexpr uint32_t COL_DARK_BLUE    = 0x00884444;
constexpr uint32_t COL_DARK_MAGENTA = 0x00884488;
constexpr uint32_t COL_ROSE         = 0x008844CC;

constexpr uint32_t COL_DARK_TEAL    = 0x00888844;
constexpr uint32_t COL_MID_GREY     = 0x00999999;
constexpr uint32_t COL_PALE_RED     = 0x008888CC;

constexpr uint32_t COL_MINT         = 0x0088CC44;
constexpr uint32_t COL_PALE_GREEN   = 0x0088CC88;
constexpr uint32_t COL_PALE_YELLOW  = 0x0088CCCC;

constexpr uint32_t COL_MID_BLUE     = 0x00CC4444;
constexpr uint32_t COL_VIOLET       = 0x00CC4488;
constexpr uint32_t COL_MID_MAGENTA  = 0x00CC44CC;

constexpr uint32_t COL_AZURE        = 0x00CC8844;
constexpr uint32_t COL_PALE_BLUE    = 0x00CC8888;
constexpr uint32_t COL_PALE_MAGENTA = 0x00CC88CC;

constexpr uint32_t COL_MID_TEAL     = 0x00CCCC44;
constexpr uint32_t COL_PALE_TEAL    = 0x00CCCC88;
constexpr uint32_t COL_PALE_GREY    = 0x00CCCCCC;
#endif

constexpr uint32_t COL_HINT1 = 0x00111111;
constexpr uint32_t COL_HINT2 = 0x00222222;
constexpr uint32_t COL_HINT3 = 0x00333333;

// 12 half-saturated colors evenly spaced around the HSV wheel
constexpr uint32_t COL_BLUE    = 0x00FF7F7F;
constexpr uint32_t COL_SKY     = 0x00FFBF7F;
constexpr uint32_t COL_TEAL    = 0x00FFFF7F;
constexpr uint32_t COL_AQUA    = 0x00BFFF7F;
constexpr uint32_t COL_GREEN   = 0x007FFF7F;
constexpr uint32_t COL_LIME    = 0x007FFFBF;
constexpr uint32_t COL_YELLOW  = 0x007FFFFF;
constexpr uint32_t COL_ORANGE  = 0x007FBFFF;
constexpr uint32_t COL_RED     = 0x007F7FFF;
constexpr uint32_t COL_PINK    = 0x00BF7FFF;
constexpr uint32_t COL_MAGENTA = 0x00FF7FFF;
constexpr uint32_t COL_VIOLET  = 0x00FF7FBF;
