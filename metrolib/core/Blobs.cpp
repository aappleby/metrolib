#include "metrolib/core/Blobs.h"

#include <cstring>

//-----------------------------------------------------------------------------

blob BlobStream::rest() {
  auto result = blob(b.begin() + cursor, b.end());
  cursor = b.size();
  return result;
}

void BlobStream::read(void* dst, size_t size) {
  memcpy(dst, b.data() + cursor, size);
  cursor += size;
}

void BlobStream::write(const void* src, size_t size) {
  b.resize(cursor + size);
  memcpy(b.data() + cursor, src, size);
  cursor += size;
}

//-----------------------------------------------------------------------------
