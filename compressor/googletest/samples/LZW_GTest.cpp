// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

//#include <limits.h>
//#include "../../LZW.hpp"
#include "../../LZW.hpp"
#include "gtest/gtest.h"
namespace {

// Step 2. Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>
class Test_LZW : public ::testing::Test {
protected:
    LZW lzw_;
};

TEST_F(Test_LZW, Compressing) {
  std::vector<char> data_1(256, 0);
  std::vector<char> compressed_data_1 = lzw_.compress(data_1); 
  EXPECT_EQ(compressed_data_1.size() <= data_1.size(), true);

  std::string str_2 = "Hellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohello!";
  std::vector<char> data_2(str_2.begin(), str_2.end());
  std::vector<char> compressed_data_2 = lzw_.compress(data_2);
  EXPECT_EQ(compressed_data_2.size() <= data_2.size(), true);

/*
  std::vector<char> data_3(256);
  for (int i = 0; i < 256; i++) data_3[i] = i;
  std::vector<char> compressed_data_3 = lzw_.compress(data_3);
  EXPECT_EQ(compressed_data_3.size() <= data_3.size(), true);
  */

}

/*
TEST_F(Test_LZW, RecoveredData) {
  std::vector<char> data(256, 0);
  std::vector<char> compressed_data = compress(data);
  std::vector<char> recovered_data = decompress(compressed_data);
 
  EXPECT_EQ(data, recovered_data);

  data.clear();
  compressed_data.clear();
  recovered_data.clear();

  std::string str = "Hellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohello!";
  std::vector<char> data(str.begin(), str.end());
  std::vector<char> compressed_data = compress(data);
  std::vector<char> recovered_data = decompress(compressed_data);

  EXPECT_EQ(data, recovered_data);

  data.clear();
  compressed_data.clear();
  recovered_data.clear();

  std::vector<char> data(256);
  for (int i = 0; i < 256; i++) data[i] = i;
  std::vector<char> compressed_data = compress(data);
  std::vector<char> recovered_data = decompress(compressed_data);

  EXPECT_EQ(data, recovered_data);
}
*/


}  // namespace

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
