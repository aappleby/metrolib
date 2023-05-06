#pragma once

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

#define TEST_INIT(...) TestResults results; do { LOG("\r"); LOG_B("%s: ", __FUNCTION__); LOG_B("" __VA_ARGS__); LOG_INDENT(); } while(0);
#define TEST_DONE(...)                      do { if (results.check_fail) { results.test_fail++; LOG("\r"); LOG_R("%s: %d failures\n", __FUNCTION__, results.test_fail); } else { results.test_pass++; LOG_G("" __VA_ARGS__); } LOG("\r"); LOG_DEDENT(); return results; } while(0);

#define TEST_FAIL(...) { results.check_fail++; LOG("\r"); LOG_R("TEST_FAIL @ %s/%s:%d : ", __FILE__, __FUNCTION__, __LINE__); LOG_R("" __VA_ARGS__); TEST_DONE(); }

// Halts test if check fails.
#define ASSERT_EQ(A, B, ...) if ((A) == (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_R("ASSERT_EQ fail: want %02x, got %02x @ %s/%s:%d : ", A, B, __FILE__, __FUNCTION__, __LINE__); LOG_R("" __VA_ARGS__); TEST_DONE(); }
#define ASSERT_NE(A, B, ...) if ((A) != (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_R("ASSERT_NE fail: want %02x, got %02x @ %s/%s:%d : ", A, B, __FILE__, __FUNCTION__, __LINE__); LOG_R("" __VA_ARGS__); TEST_DONE(); }

// Logs a failure if check fails but does not halt test.
#define EXPECT_EQ(A, B, ...) if ((A) == (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_Y("EXPECT_EQ fail: want %02x, got %02x @ %s/%s:%d : ", A, B, __FILE__, __FUNCTION__, __LINE__); LOG_Y("" __VA_ARGS__); }
#define EXPECT_NE(A, B, ...) if ((A) != (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_Y("EXPECT_NE fail: want %02x, got %02x @ %s/%s:%d : ", A, B, __FILE__, __FUNCTION__, __LINE__); LOG_Y("" __VA_ARGS__); }

//------------------------------------------------------------------------------
// Compare strings and find substrings, treating all whitespace as if it was
// "\w+" in a regex.

#if 0
bool comp_iws(const char* a, const char* b);
bool comp_iws(const std::string& a, const std::string& b);
bool find_iws(const char* a, const char* b);
bool find_iws(const std::string& a, const std::string& b);
#endif
