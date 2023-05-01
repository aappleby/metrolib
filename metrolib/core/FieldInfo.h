#pragma once
#include "metrolib/core/Log.h"

#include <stddef.h>
#include <stdint.h>

//-----------------------------------------------------------------------------

struct FieldInfo {
  const char* name;
  int offset;
  int size;
};

#define DECLARE_FIELD(T, A) { #A, offsetof(T, A), sizeof(T::A) }
#define END_FIELDS() { nullptr, 0, 0 }

void print_field_at(int offset, const FieldInfo* fields);
bool diff_blobs(const void* blob_a, const void* blob_b, size_t size, uint8_t mask, const FieldInfo* fields);

//-----------------------------------------------------------------------------

bool bit_cmp(const uint8_t* pa, const uint8_t* pb, size_t size, uint8_t mask = 0xFF, FieldInfo* field_info = nullptr);

template<typename T>
bool bit_cmp(const T& a, const T& b, uint8_t mask = 0xFF, FieldInfo* field_info = nullptr) {
  const uint8_t* pa = (const uint8_t*)&a;
  const uint8_t* pb = (const uint8_t*)&b;
  return bit_cmp(pa, pb, sizeof(T), mask, field_info);
}

//-----------------------------------------------------------------------------
