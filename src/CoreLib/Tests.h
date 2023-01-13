#if 0
#pragma once

#include "Log.h"

//-----------------------------------------------------------------------------

struct TestResults {
  void operator += (TestResults r) {
    expect_pass += r.expect_pass;
    expect_fail += r.expect_fail;
    test_pass += r.test_pass;
    test_fail += r.test_fail;
  }

  int expect_pass = 0;
  int expect_fail = 0;

  int test_pass = 0;
  int test_fail = 0;

  bool ok() const { return (expect_fail == 0) && (test_fail == 0); }

  TestResults& finish(const char* function_name) {
    LOG_DEDENT();
    if (!test_pass && !test_fail) {
      expect_fail ? test_fail++ : test_pass++;
    }

    if (test_fail) {
      LOG_R("%s: %d expect failures, %d test failures\n", function_name, expect_fail, test_fail);
    }
    else {
      //LOG_G("PASS!\n");
    }
    return *this;
  }
};

#define TEST_INIT(...) TestResults results; do { LOG("%s: ", __FUNCTION__); LOG_B("" __VA_ARGS__); LOG("\n"); LOG_INDENT(); } while(0);
#define TEST_DONE()    do { return results.finish(__FUNCTION__); } while(0);
#define TEST_PASS()    do { results.test_pass++; return results.finish(__FUNCTION__); } while(0);
#define TEST_FAIL(...) do { results.test_fail++; LOG_R("\n"); LOG_R("%s: ", __FUNCTION__); LOG_R("" __VA_ARGS__); LOG_R("\n"); return results.finish(__FUNCTION__); } while(0);

#define EXPECT(A, ...)       if ((A))        { results.expect_pass++; } else { LOG_Y("EXPECT fail @ %s : %d ",                                          __FILE__, __LINE__); LOG_Y(__VA_ARGS__); LOG("\n"); results.expect_fail++; }
#define EXPECT_EQ(A, B, ...) if ((A) == (B)) { results.expect_pass++; } else { LOG_Y("EXPECT_EQ fail: %02x != %02x @ %s : %d ", A, B, __FILE__, __LINE__); LOG_Y(__VA_ARGS__); LOG("\n"); results.expect_fail++; }
#define EXPECT_NE(A, B, ...) if ((A) != (B)) { results.expect_pass++; } else { LOG_Y("EXPECT_NE fail: %02x == %02x @ %s : %d ", A, B, __FILE__, __LINE__); LOG_Y(__VA_ARGS__); LOG("\n"); results.expect_fail++; }

#define ASSERT_EQ(A, B, ...) if ((A) == (B)) { results.expect_pass++; } else { LOG_R("ASSERT_EQ fail: %02x != %02x @ %s : %d ", A, B, __FILE__, __LINE__); LOG_R(__VA_ARGS__); LOG("\n"); TEST_FAIL(); }
#define ASSERT_NE(A, B, ...) if ((A) != (B)) { results.expect_pass++; } else { LOG_R("ASSERT_NE fail: %02x == %02x @ %s : %d ", A, B, __FILE__, __LINE__); LOG_R(__VA_ARGS__); LOG("\n"); TEST_FAIL(); }

//-----------------------------------------------------------------------------
#endif


#pragma once

#include "Log.h"

//-----------------------------------------------------------------------------

struct TestResults {

  void operator += (TestResults r) {
    test_pass += r.test_pass;
    test_fail += r.test_fail;
    check_pass += r.check_pass;
    check_fail += r.check_fail;
  }

  int test_pass = 0;
  int test_fail = 0;

  int check_pass = 0;
  int check_fail = 0;

  bool ok() const { return (test_fail == 0) && (check_fail == 0); }

  void dump() {
    LOG("\r");
    if (test_fail) {
        LOG_R("\n");
        LOG_R("+---------------------------------+\n");
        LOG_R("|    #######  #####  ## ##        |  "); LOG_G("test  pass %d\n", test_pass);
        LOG_R("|    ##      ##   ## ## ##        |  "); LOG_R("test  fail %d\n", test_fail)
        LOG_R("|    #####   ####### ## ##        |  "); LOG_G("check pass %d\n", check_pass);
        LOG_R("|    ##      ##   ## ## ##        |  "); LOG_R("check fail %d\n", check_fail);
        LOG_R("|    ##      ##   ## ## #######   |  "); LOG_R("\n")
        LOG_R("+---------------------------------+\n");
        LOG_R("\n");
    }
    else {
        LOG_G("\n");
        LOG_G("+---------------------------------+\n");
        LOG_G("| ######   #####  ####### ####### |  "); LOG_G("test  pass %d\n", test_pass);
        LOG_G("| ##   ## ##   ## ##      ##      |  "); LOG_G("test  fail %d\n", test_fail)
        LOG_G("| ######  ####### ####### ####### |  "); LOG_G("check pass %d\n", check_pass);
        LOG_G("| ##      ##   ##      ##      ## |  "); LOG_G("check fail %d\n", check_fail);
        LOG_G("| ##      ##   ## ####### ####### |  "); LOG_G("\n")
        LOG_G("+---------------------------------+  "); LOG_G("\n");
        if (test_fail == 0 && check_fail == 0) {
          LOG_G("All tests pass\n");
        }
        LOG_G("\n");
    }
  }
};

#define TEST_INIT(...) TestResults results; do { LOG("\r"); LOG_B("%s: ", __FUNCTION__); LOG_B("" __VA_ARGS__); LOG_INDENT(); } while(0);
#define TEST_DONE(...)                      do { if (results.check_fail) { results.test_fail++; LOG("\r"); LOG_R("%s: %d failures\n", __FUNCTION__, results.test_fail); } else { results.test_pass++; LOG_G("" __VA_ARGS__); } LOG("\r"); LOG_DEDENT(); return results; } while(0);
#define TEST_FAIL(...)                      do { results.test_fail++; LOG_R("" __VA_ARGS__); LOG("\r"); LOG_DEDENT(); return results; } while(0);

#define ASSERT_EQ(A, B, ...) if ((A) == (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_R("ASSERT_EQ fail: %02x != %02x @ %s/%s:%d : ", A, B, __FILE__, __FUNCTION__, __LINE__); LOG_R("" __VA_ARGS__); TEST_DONE(); }
#define ASSERT_NE(A, B, ...) if ((A) != (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_R("ASSERT_NE fail: %02x == %02x @ %s/%s:%d : ", A, B, __FILE__, __FUNCTION__, __LINE__); LOG_R("" __VA_ARGS__); TEST_DONE(); }

#define EXPECT_EQ(A, B, ...) if ((A) == (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_Y("EXPECT_EQ fail: %02x != %02x @ %s/%s:%d : ", A, B, __FILE__, __FUNCTION__, __LINE__); LOG_Y("" __VA_ARGS__); }
#define EXPECT_NE(A, B, ...) if ((A) != (B)) { results.check_pass++; } else { results.check_fail++; LOG("\r"); LOG_Y("EXPECT_NE fail: %02x == %02x @ %s/%s:%d : ", A, B, __FILE__, __FUNCTION__, __LINE__); LOG_Y("" __VA_ARGS__); }

//-----------------------------------------------------------------------------
