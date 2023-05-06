#include "metrolib/core/Utils.h"

#include <time.h>

#ifdef __GNUC__
uint32_t byteswap(uint32_t x) { return __builtin_bswap32(x); }
uint64_t byteswap(uint64_t x) { return __builtin_bswap64(x); }
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
uint32_t byteswap(uint32_t x) { return _byteswap_ulong(x); }
uint64_t byteswap(uint64_t x) { return _byteswap_uint64(x); }
#endif



uint32_t mix(uint32_t h) {
  return byteswap(h * 0xed558ccd);
}

uint64_t mix(uint64_t h) {
  return byteswap(h * 0xff51afd7ed558ccd);
}

uint64_t hash_blob(uint64_t h, const void* blob, size_t len) {
  const uint8_t* base = (uint8_t*)blob;
  for (auto i = 0; i < len; i++) {
    h = mix(h ^ base[i]);
  }
  return h;
}

uint64_t hash_blob(const void* blob, size_t len) {
  return hash_blob(HASH_INIT, blob, len);
}

double timestamp() {
  static uint64_t _time_origin = 0;
  timespec ts;
  (void)timespec_get(&ts, TIME_UTC);
  uint64_t now = ts.tv_sec * 1000000000ull + ts.tv_nsec;
  if (!_time_origin) _time_origin = now;
  return double(now - _time_origin) / 1.0e9;
}

static struct autorun {
  autorun() {
    timestamp();
  }
} _autorun;
