#pragma once
#include <vector>
#include <stdint.h>
#include "metrolib/core/Check.h"

typedef std::vector<uint8_t> blob;

//-----------------------------------------------------------------------------

struct BlobStream {
  template<typename T>
  inline bool read(T& t) {
    if (error) return false;

    CHECK_P(b.size() - cursor >= sizeof(uint64_t) + sizeof(T));
    uint64_t size = 0;
    read(&size, sizeof(uint64_t));
    if (size != sizeof(T)) {
      error = true;
      return false;
    }

    read(&t, sizeof(T));
    return true;
  }

  template<typename T>
  inline bool write(const T& t) {
    uint64_t size = sizeof(T);
    write(&size, sizeof(uint64_t));
    write(&t, sizeof(T));
    return true;
  }

  void read (      void* dst, size_t size);
  void write(const void* src, size_t size);

  blob rest();

  blob b;
  size_t cursor = 0;
  bool error = false;
};

//-----------------------------------------------------------------------------
