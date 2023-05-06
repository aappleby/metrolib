#include "metrolib/core/Platform.h"

#include <assert.h>
#include <memory.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <functional>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

#ifdef __GNUC__
//#include <execinfo.h>
#include <sys/stat.h>
#include <unistd.h>
#include <csignal>
#endif

// KCOV_OFF

//------------------------------------------------------------------------------

void print_escaped(char s) {
  if (s == '\n')
    printf("\\n");
  else if (s == '\r')
    printf("\\r");
  else if (s == '\t')
    printf("\\t");
  else if (s == '"')
    printf("\\\"");
  else if (s == '\\')
    printf("\\\\");
  else
    printf("%c", s);
}

void print_escaped(const char* source, int a, int b) {
  printf("\"");
  for (; a < b; a++) {
    print_escaped(source[a]);
  }
  printf("\"");
}

/*
void print_escaped(char s) {
  if      (s == '\n') printf("\\n");
  else if (s == '\r') printf("\\r");
  else if (s == '\t') printf("\\t");
  else if (s == '"')  printf("\\\"");
  else if (s == '\\') printf("\\\\");
  else                printf("%c", s);
}
*/

//------------------------------------------------------------------------------
// GCC platform

#ifdef __GNUC__

int plat_mkdir(const char* path) { return mkdir(path, S_IREAD | S_IWRITE | S_IEXEC); }

void dprintf(const char* format, ...) {
  // static char buffer[256];
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

void print_stacktrace(void) {
  /*
  void* array[1024];
  size_t size = backtrace(array, 1024);
  char** strings = backtrace_symbols(array, size);
  for (int i = 0; i < size; i++) printf("%s\n", strings[i]);
  free(strings);
  */
}

void debugbreak() {
  print_stacktrace();
  raise(SIGTRAP);
}

#endif

//------------------------------------------------------------------------------
// Visual Studio platform

#ifdef _MSC_VER

#include <Windows.h>
#include <direct.h>

void debugbreak() {
  __debugbreak();
}

int plat_mkdir(const char* path) {
  return _mkdir(path);
}

void print_stacktrace() {
}

#endif

// KCOV_ON
