#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <string>

//-----------------------------------------------------------------------------

struct Dumper {
  virtual void operator()(const char* format, ...) = 0;

  virtual void add_char(char c) { operator()("%c", c); }
  virtual void newline() { add_char('\n'); }
  virtual void indent() {}
  virtual void dedent() {}

  //----------

  void dump_bitp(const char* tag, bool b) {
    operator()("%s%c\n", tag, (b & 0x01) ? '1' : '0');
  }

  void dump_bytep(const char* tag, uint8_t b) {
    operator()(tag);
    for (int i = 7; i >= 0; i--) {
      add_char((b & (1 << i)) ? '1' : '0');
    }
    operator()(" 0x%02x %d\n", b, b);
  }

  void dump_flags(const char* tag, const void* blob, int byte_count) {
    operator()(tag);
    const uint8_t* d = (const uint8_t*)blob;
    for (int i = byte_count - 1; i >= 0; i--) {
      add_char((d[i] & 0x01) ? '1' : '0');
    }
    add_char('\n');
  }

  void dump_slicep(const char* tag, const void* blob, int byte_count) {
    operator()(tag);
    for (int i = byte_count; i < 8; i++) add_char(' ');

    const uint8_t* d = (const uint8_t*)blob;
    for (int i = byte_count - 1; i >= 0; i--) {
      // high clock = green, low clock = red
      add_char((d[i] & 0x02) ? '\002' : '\003');
      add_char((d[i] & 0x01) ? '1' : '0');
    }
    add_char('\001');

    uint16_t val = 0;
    for (int i = 0; i < byte_count; i++) val |= ((d[i] & 1) << i);

    operator()(" 0x%02x %d\n", val, val);
  }

  void dump_slice2p(const char* tag, const void* blob, int byte_count) {
    operator()(tag);
    for (int i = byte_count; i < 8; i++) add_char(' ');

    const uint8_t* d = (const uint8_t*)blob;
    for (int i = byte_count - 1; i >= 0; i--) {
      // high clock = green, low clock = red
      add_char((d[i] & 0x02) ? '\002' : '\003');
      add_char((d[i] & 0x01) ? '1' : '0');
    }
    add_char('\001');

    uint16_t val = 0;
    for (int i = 0; i < byte_count; i++) val |= ((d[i] & 1) << i);
    if (byte_count <= 8) {
      operator()(" 0x%02x %d\n", val, val);
    } else {
      operator()("\n%s0x%04x %d\n", tag, val, val);
    }
  }

  void dump_slice2n(const char* tag, const void* blob, int byte_count) {
    operator()(tag);
    for (int i = byte_count; i < 8; i++) add_char(' ');

    const uint8_t* d = (const uint8_t*)blob;
    for (int i = byte_count - 1; i >= 0; i--) {
      add_char((d[i] & 0x02) ? '\002' : '\003');
      add_char((d[i] & 0x01) ? '0' : '1');
    }
    add_char('\001');

    uint16_t val = 0;
    for (int i = 0; i < byte_count; i++) val |= ((~d[i] & 1) << i);
    if (byte_count <= 8) {
      operator()(" 0x%02x %d\n", val, val);
    } else {
      operator()("\n%s0x%04x %d\n", tag, val, val);
    }
  }

  /*
  void dump_req(const char* tag, const Req& req) {
    operator()("%s%04x:%04x %s%s\n", tag, req.addr, req.data,
      req.read  ? "\003R\001" : "-",
      req.write ? "\002W\001" : "-");
  }

  void dump_ack(const char* tag, const Ack& ack) {
    operator()("%s%04x:%04x %s -\n", tag, ack.addr, ack.data,
      ack.read  ? "\003R\001" : "-");
  }
  */
};

#define DUMP_BITP(A) d.dump_bitp(#A " : ", A.state);

//-----------------------------------------------------------------------------

struct StringDumper : public Dumper {
  std::string s;

  const char* c_str() {
    return s.c_str();
  }

  void add_char(char c) override {
    s.push_back(c);
  }

  void operator()(const char* format, ...) override {
    char source_buf[1024];
    va_list args;
    va_start (args, format);
    vsnprintf (source_buf, 1024 ,format, args);
    va_end (args);
    s.append(source_buf);
  }
  void clear() { s.clear(); }
};

//-----------------------------------------------------------------------------

struct ConsoleDumper : public Dumper {
  void operator()(const char* format, ...) override {
    va_list args;
    va_start (args, format);
    vprintf (format, args);
    va_end (args);
  }
};

//-----------------------------------------------------------------------------
