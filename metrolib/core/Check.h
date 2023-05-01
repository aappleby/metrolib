#pragma once
#include "metrolib/core/Log.h"

void debugbreak();

//-----------------------------------------------------------------------------

// Checks that always happen in every build.
#define CHECK_P(A)  if (!(A)) { LOG_R("ASSERT_P fail @ %s:%d : %s\n", __FILE__, __LINE__, #A); debugbreak(); }
#define CHECK_N(A)  if ((A))  { LOG_R("ASSERT_N fail @ %s:%d : %s\n", __FILE__, __LINE__, #A); debugbreak(); }

#if CONFIG_DEBUG
#define DCHECK_P(A)   if (!(A)) { LOG_R("CHECK_P fail @ %s:%d : %s\n", __FILE__, __LINE__, #A);  debugbreak(); }
#define DCHECK_N(A)   if ((A))  { LOG_R("CHECK_N fail @ %s:%d : %s\n", __FILE__, __LINE__, #A);  debugbreak(); }
#else
#define DCHECK_P(A)
#define DCHECK_N(A)
#endif

//-----------------------------------------------------------------------------
