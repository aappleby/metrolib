#include "metrolib/core/FieldInfo.h"

#include "metrolib/core/Log.h"

//-----------------------------------------------------------------------------

void print_field_at(int offset, const FieldInfo* fields) {
  if (fields == nullptr) return;

  const FieldInfo* field = nullptr;
  int min_delta = 1000000;

  for (auto cursor = fields; cursor->name != nullptr; cursor++) {
    int delta = offset - cursor->offset;
    if (delta >= 0 && delta < cursor->size && delta < min_delta) {
      field = cursor;
      min_delta = delta;
    }
  }

  if (field != nullptr) {
    LOG_R("%s + %d", field->name, min_delta);
  }
  else {
    LOG_R("<could not find field at offset %d>", offset);
  }
}

//-----------------------------------------------------------------------------

bool diff_blobs(const void* blob_a, const void* blob_b, size_t size, uint8_t mask, const FieldInfo* fields) {
  bool result = true;

  uint8_t* bytes_a = (uint8_t*)blob_a;
  uint8_t* bytes_b = (uint8_t*)blob_b;

  for (int i = 0; i < size; i++) {
    int byte_a = bytes_a[i] & mask;
    int byte_b = bytes_b[i] & mask;

    if (byte_a != byte_b) {
      LOG_R("MISMATCH @ %5d - ", i);
      print_field_at(i, fields);
      LOG_R(": 0x%02x 0x%02x\n", byte_a, byte_b);
      result = false;
    }
  }

  return result;
}

bool bit_cmp(const uint8_t* pa, const uint8_t* pb, size_t size, uint8_t mask, FieldInfo* field_info) {
  bool result = true;
  for (size_t i = 0; i < size; i++) {
    auto ba = pa[i] & mask;
    auto bb = pb[i] & mask;
    if (ba != bb) {
      LOG_R("bit_cmp mismatch at offset %3d - 0x%02x 0x%02x, mask 0x%02x",  (int)i, ba, bb, mask);
      if (field_info) {
        LOG_R(" : ");
        print_field_at((int)i, field_info);
      }
      LOG_R("\n");
      result = false;
    }
  }
  return result;
}
