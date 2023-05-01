#pragma once
#include <stddef.h>
#include <stdint.h>

double timestamp();
uint32_t byteswap(uint32_t x);
uint64_t byteswap(uint64_t x);

//-----------------------------------------------------------------------------

//constexpr uint64_t HASH_INIT = 0x12345678;
constexpr uint64_t HASH_INIT = 0;
uint32_t mix(uint32_t h);
uint64_t mix(uint64_t h);
uint64_t hash_blob(const void* blob, size_t len);
uint64_t hash_blob(uint64_t h, const void* blob, size_t len);

//-----------------------------------------------------------------------------

template<typename T>
T remap(T x, T a1, T a2, T b1, T b2) {
  double y = (double(x) - double(a1)) / (double(a2) - double(a1));
  double z = y * (double(b2) - double(b1)) + b1;
  return T(z);
}

template<typename T>
T remap_clamp(T x, T a1, T a2, T b1, T b2) {
  double y = (double(x) - double(a1)) / (double(a2) - double(a1));
  if (y < 0) y = 0;
  if (y > 1) y = 1;
  double z = y * (double(b2) - double(b1)) + b1;
  return T(z);
}

template<typename S, typename T>
inline T clamp(S a, T min, T max) {
  return (a < min) ? min : (a > max) ? max : T(a);
}

template<typename T>
T remap_wrap(T x, T a1, T a2, T b1, T b2) {
  double y = (double(x) - double(a1)) / (double(a2) - double(a1));
  y -= (int)y;
  if (y < 0) y += 1.0;
  double z = y * (double(b2) - double(b1)) + b1;
  return T(z);
}

template<typename T>
void sort(T& a, T& b) {
  if (a > b) {
    auto temp = a;
    a = b;
    b = temp;
  }
}

constexpr bool in_range(uint16_t addr, uint16_t begin, uint16_t end) {
  return (begin <= addr) && (addr <= end);
}

constexpr uint8_t bit_reverse(uint8_t b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

constexpr uint32_t xorshift32(uint32_t& x)
{
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}

//-----------------------------------------------------------------------------
