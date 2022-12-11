#include "Check.h"

//------------------------------------------------------------------------------
// GCC platform

#ifdef __GNUC__
#include <csignal>

void debugbreak() {
  raise(SIGTRAP);
}

#endif

//------------------------------------------------------------------------------
// Visual Studio platform

#ifdef _MSC_VER
#include <intrin.h>

void debugbreak() {
  __debugbreak();
}

#endif



#if 0
//-----------------------------------------------------------------------------

#ifdef __GNUC__
#include <csignal>
#define debugbreak() raise(SIGTRAP);
#endif

#ifdef _MSC_VER
#define debugbreak() __debugbreak()
#endif
#endif
