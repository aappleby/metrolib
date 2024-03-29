#include "metrolib/core/Err.h"

#include "metrolib/core/Log.h"

#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

// KCOV_OFF

const Err Err::ok;

//------------------------------------------------------------------------------

ErrType::ErrType(SEV_TYPE v, const char* file, int line, const char* func,
                 const char* format, ...)
    : sev(v) {
  va_list args;
  va_start(args, format);

  auto& log = TinyLog::get();

  if (v == SEV_TYPE::INFO) {
    // KCOV_OFF
    log.color(0x0080FF80);
    log.print("Info @ %s : %d : %s\n", file, line, func);
    log.print("  ");
    log.print(format, args);
    // KCOV_ON
  } else if (v == SEV_TYPE::WARN) {
    log.color(0x0080FFFF);
    log.print("Warning @ %s : %d : %s\n", file, line, func);
    log.print("  ");
    log.print(format, args);
  } else if (v == SEV_TYPE::ERR) {
    log.color(0x008080FF);
    log.print("Error @ %s : %d : %s\n", file, line, func);
    log.print("  ");
    log.vprint(format, args);
    log.print("\n");
    /*
    TinyLog::get().print(stdout, 0x008080FF, "Error @ %s : %d : %s\n", file, line, func);
    TinyLog::get().print(stdout, 0x008080FF, "  ");
    TinyLog::get().vprint(stdout, 0x008080FF, format, args);
    TinyLog::get().print(stdout, 0x008080FF, "\n");
    //assert(false);
    */
  }

  va_end(args);
}

//------------------------------------------------------------------------------

Err::Err() : err(0) {}

Err::Err(const ErrType& et) : err(int(et.sev)) {}

Err& Err::operator<<(const Err& e) {
  if (e.err & int(SEV_TYPE::ERR)) {
    //err = err;
  }
  err |= e.err;
  return *this;
}

Err& Err::operator<<(const ErrType& e) {
  if (int(e.sev) & int(SEV_TYPE::ERR)) {
    //err = err;
  }

  err |= int(e.sev);
  return *this;
}

bool Err::has_info() const { return err & 1; }
bool Err::has_warn() const { return err & 2; }
bool Err::has_err() const { return err & 4; }

//------------------------------------------------------------------------------

// KCOV_ON
