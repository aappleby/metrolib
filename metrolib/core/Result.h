#pragma once

#include "metrolib/core/Check.h"

//-----------------------------------------------------------------------------

template<typename RES, typename ERR>
struct Result {
  Result() = delete;
  explicit Result(RES r) : _err(static_cast<ERR>(0)), _res(r), _ok(1) {}
  Result(ERR e) : _err(e), _res(static_cast<RES>(0)), _ok(0) {}

  bool operator==(const Result& x) const {
    return _ok == x._ok && _res == x._res && _err == x._err;
  }

  Result& operator &= (const Result r) {
    if (r.is_err()) {
      _res = r._res;
      _err = r._err;
      _ok = r._ok;
    }
    return *this;
  }

  static Result ok() { return Result(static_cast<RES>(0)); }

  bool is_ok()  const { return  _ok; }
  bool is_err() const { return !_ok; }

  RES unwrap() const {
    CHECK_P(_ok);
    return _res;
  }

private:
  RES _res;
  ERR _err;
  bool _ok;
};

enum struct Error {
  NONE = 0,
  NULLPTR,
  NOT_FOUND,
  CORRUPT,
  MISMATCH
};

typedef Result<uint8_t, Error> GBResult;

//-----------------------------------------------------------------------------
