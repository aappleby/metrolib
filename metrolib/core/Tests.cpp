#include "metrolib/core/Tests.h"

#if 0
bool comp_iws(const char* a, const char* b) {
  if (!a) return false;
  if (!b) return false;

  while (1) {
    if (isspace(*a) != isspace(*b)) return false;
    while (isspace(*a)) a++;
    while (isspace(*b)) b++;
    if (*a != *b) return false;
    if (*a == 0) break;
    a++;
    b++;
  }

  return true;
}

bool comp_iws(const std::string& a, const std::string& b) {
  return comp_iws(a.c_str(), b.c_str());
}

bool find_iws(const char* a, const char* b) {
  if (!a) return false;
  if (!b) return false;

  const char* c = a;
  const char* d = b;

  while (1) {
    if (*d == 0) return true;
    if (*c == 0) return false;

    if (isspace(*c) && isspace(*d)) {
      while (*c && isspace(*c)) c++;
      while (*d && isspace(*d)) d++;
      if (*d == 0) return true;
      if (*c == 0) return false;
    }

    if (*c != *d) {
      // Mismatch, restart
      c++;
      d = b;
    } else {
      // Match, continue
      c++;
      d++;
    }
  }
}

bool find_iws(const std::string& a, const std::string& b) {
  return find_iws(a.c_str(), b.c_str());
}


//------------------------------------------------------------------------------

static TestResults test_dummy() {
  TEST_INIT("Make sure our test framework is working.");
  LOG_INDENT_SCOPE();
  EXPECT(1 != 2, "One should not equal two.");
  TEST_DONE();
}

//------------------------------------------------------------------------------

TestResults test_comp() {
  TEST_INIT("Text comparison should treat all whitespace as \"\\w+\"");

  EXPECT(comp_iws("foo bar", "foo\nbar"), "x");
  EXPECT(comp_iws("foo bar", "foo\tbar"), "x");
  EXPECT(comp_iws("foo\nbar", "foo\tbar"), "x");
  EXPECT(comp_iws("foo\nbar", "foo bar"), "x");
  EXPECT(comp_iws("foo\tbar", "foo\nbar"), "x");
  EXPECT(comp_iws("foo\tbar", "foo bar"), "x");

  EXPECT(!comp_iws("foo bar", "foobar"), "x");

  TEST_DONE();
}

//------------------------------------------------------------------------------

TestResults test_match() {
  TEST_INIT("Substring find should treat all whitespace as \"\\w+\"");
  LOG_INDENT_SCOPE();

  EXPECT(+find_iws("foobarbaz", "bar"), "x");
  EXPECT(!find_iws("foobarbaz", " bar"), "x");
  EXPECT(!find_iws("foobarbaz", "bar "), "x");
  EXPECT(!find_iws("foobarbaz", " bar "), "x");

  EXPECT(+find_iws("foo barbaz", "bar"), "x");
  EXPECT(+find_iws("foo barbaz", " bar"), "x");
  EXPECT(!find_iws("foo barbaz", "bar "), "x");
  EXPECT(!find_iws("foo barbaz", " bar "), "x");

  EXPECT(+find_iws("foobar baz", "bar"), "x");
  EXPECT(!find_iws("foobar baz", " bar"), "x");
  EXPECT(+find_iws("foobar baz", "bar "), "x");
  EXPECT(!find_iws("foobar baz", " bar "), "x");

  EXPECT(+find_iws("foo bar baz", "bar"), "x");
  EXPECT(+find_iws("foo bar baz", " bar"), "x");
  EXPECT(+find_iws("foo bar baz", "bar "), "x");
  EXPECT(+find_iws("foo bar baz", " bar "), "x");

  TEST_DONE();
}

//------------------------------------------------------------------------------

TestResults test_utils() {
  TEST_INIT();
  results << test_translate_simple();
  results << test_dummy();
  results << test_comp();
  results << test_match();
  TEST_DONE();
}

//------------------------------------------------------------------------------
#endif
