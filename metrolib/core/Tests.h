#pragma once

#include <string>
#include "metrolib/core/Log.h"

//-----------------------------------------------------------------------------

struct TestResults {
  TestResults() {}

  void operator << (TestResults r) {
    test_pass += r.test_pass;
    test_fail += r.test_fail;
    check_pass += r.check_pass;
    check_fail += r.check_fail;
  }

  int test_pass = 0;
  int test_fail = 0;

  int check_pass = 0;
  int check_fail = 0;

  int show_result() {
    LOG("\r");
    if (test_fail) {
        LOG_R("\n");
        LOG_R("+---------------------------------+\n");
        LOG_R("|    #######  #####  ## ##        |  "); LOG_G("test  pass %d\n", test_pass);
        LOG_R("|    ##      ##   ## ## ##        |  "); LOG_R("test  fail %d\n", test_fail);
        LOG_R("|    #####   ####### ## ##        |  "); LOG_G("check pass %d\n", check_pass);
        LOG_R("|    ##      ##   ## ## ##        |  "); LOG_R("check fail %d\n", check_fail);
        LOG_R("|    ##      ##   ## ## #######   |  "); LOG_R("\n");
        LOG_R("+---------------------------------+\n");
        LOG_R("\n");
        return 1;
    }
    else {
        LOG_G("\n");
        LOG_G("+---------------------------------+\n");
        LOG_G("| ######   #####  ####### ####### |  "); LOG_G("test  pass %d\n", test_pass);
        LOG_G("| ##   ## ##   ## ##      ##      |  "); LOG_G("test  fail %d\n", test_fail);
        LOG_G("| ######  ####### ####### ####### |  "); LOG_G("check pass %d\n", check_pass);
        LOG_G("| ##      ##   ##      ##      ## |  "); LOG_G("check fail %d\n", check_fail);
        LOG_G("| ##      ##   ## ####### ####### |  "); LOG_G("\n");
        LOG_G("+---------------------------------+  "); LOG_G("\n");
        if (test_fail == 0 && check_fail == 0) {
          LOG_G("All tests pass\n");
        }
        LOG_G("\n");
        return 0;
    }
  }
};

/*
inline void print_want_got(const void* A, const void* B) { LOG_R("want %p, got %p ", A, B); }
inline void print_want_got(uint64_t A, uint64_t B)       { LOG_R("want 0x%lx, got 0x%lx ", A, B); }
inline void print_want_got(uint32_t A, uint32_t B)       { LOG_R("want 0x%x, got 0x%x ", A, B); }
inline void print_want_got(uint16_t A, uint16_t B)       { LOG_R("want 0x%x, got 0x%x ", A, B); }
inline void print_want_got(uint8_t A,  uint8_t B)        { LOG_R("want 0x%x, got 0x%x ", A, B); }

inline void print_want_got(int64_t A,  int64_t B)        { LOG_R("want %ld, got %ld ", A, B); }
inline void print_want_got(int32_t A,  int32_t B)        { LOG_R("want %d, got %d ", A, B); }
inline void print_want_got(int16_t A,  int16_t B)        { LOG_R("want %d, got %d ", A, B); }
inline void print_want_got(int8_t A,   int8_t B)         { LOG_R("want %d, got %d ", A, B); }

inline void print_want_got(double A,   double B)         { LOG_R("want %f, got %f ", A, B); }
inline void print_want_got(float A,    float B)          { LOG_R("want %f, got %f ", A, B); }
inline void print_want_got(bool A,     bool B)           { LOG_R("want %s, got %s ", A ? "true" : "false", B ? "true" : "false"); }

inline void print_want_got(const std::string& a, const std::string& b) {
  LOG_R("want {%s}, got {%s} ", a.c_str(), b.c_str());
}
*/
template<typename A, typename B>
inline void print_want_got(const A& a, const B& b) { }

#define TEST_INIT(...) TestResults results; do { LOG("\r"); LOG_B("%s: ", __FUNCTION__); LOG_B("" __VA_ARGS__); LOG_INDENT(); } while(0);
#define TEST_DONE(...)                      do { if (results.check_fail) { results.test_fail++; LOG("\r"); LOG_R("%s: %d failures\n", __FUNCTION__, results.test_fail); } else { results.test_pass++; LOG_G("" __VA_ARGS__); } LOG("\r"); LOG_DEDENT(); return results; } while(0);

#define TEST_FAIL(...) { results.check_fail++; LOG("\r"); LOG_R("TEST_FAIL @ %s/%s:%d : ", __FILE__, __FUNCTION__, __LINE__); LOG_R("" __VA_ARGS__); TEST_DONE(); }

// Halts test if check fails.
#define ASSERT_EQ(A, B, ...) if ((A) == (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_R("ASSERT_EQ fail: "); print_want_got(A, B); LOG_R("@ %s/%s:%d : ", __FILE__, __FUNCTION__, __LINE__); LOG_R("" __VA_ARGS__); TEST_DONE(); }
#define ASSERT_NE(A, B, ...) if ((A) != (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_R("ASSERT_NE fail: "); print_want_got(A, B); LOG_R("@ %s/%s:%d : ", __FILE__, __FUNCTION__, __LINE__); LOG_R("" __VA_ARGS__); TEST_DONE(); }

// Logs a failure if check fails but does not halt test.
#define EXPECT_EQ(A, B, ...) if ((A) == (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_Y("EXPECT_EQ fail: "); print_want_got(A, B); LOG_R("@ %s/%s:%d : ", __FILE__, __FUNCTION__, __LINE__); LOG_Y("" __VA_ARGS__); }
#define EXPECT_NE(A, B, ...) if ((A) != (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_Y("EXPECT_NE fail: "); print_want_got(A, B); LOG_R("@ %s/%s:%d : ", __FILE__, __FUNCTION__, __LINE__); LOG_Y("" __VA_ARGS__); }

#define EXPECT_TRUE(A, ...)  EXPECT_EQ(true,  A, __VA_ARGS__)
#define EXPECT_FALSE(A, ...) EXPECT_EQ(false, A, __VA_ARGS__)

#define EXPECT_PTR(A, ...)   EXPECT_NE(nullptr, A, __VA_ARGS__)
#define EXPECT_NULL(A, ...)  EXPECT_EQ(nullptr, A, __VA_ARGS__)

//------------------------------------------------------------------------------
// Compare strings and find substrings, treating all whitespace as if it was
// "\w+" in a regex.

#if 0
bool comp_iws(const char* a, const char* b);
bool comp_iws(const std::string& a, const std::string& b);
bool find_iws(const char* a, const char* b);
bool find_iws(const std::string& a, const std::string& b);
#endif
