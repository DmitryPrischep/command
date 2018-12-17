
#include "../../LZW.hpp"
#include "gtest/gtest.h"
namespace {


class Test_LZW : public ::testing::Test {
protected:
    LZW coder_;
};

TEST_F(Test_LZW, Compressing) {
  std::vector<char> data_1(256, 0);
  std::vector<char> compressed_data_1 = coder_.compress(data_1); 
  EXPECT_EQ(compressed_data_1.size() <= data_1.size(), true);

  std::string str_2 = "Hellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohello!";
  std::vector<char> data_2(str_2.begin(), str_2.end());
  std::vector<char> compressed_data_2 = coder_.compress(data_2);
  EXPECT_EQ(compressed_data_2.size() <= data_2.size(), true);

  /*
  std::vector<char> data_3(256);
  for (int i = 0; i < 256; i++) data_3[i] = i;
  std::vector<char> compressed_data_3 = coder_.compress(data_3);
  EXPECT_EQ(compressed_data_3.size() <= data_3.size(), true);
  */

}

TEST_F(Test_LZW, RecoveredData) {
  std::vector<char> data_1(256, 0);
  std::vector<char> compressed_data_1 = coder_.compress(data_1);
  std::vector<char> recovered_data_1 = coder_.decompress(compressed_data_1); 
  for (int i = 0; i < data_1.size(); i++) {
    EXPECT_EQ(data_1[i], recovered_data_1[i]);
  }

  std::string str_2 = "Hellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohello!";
  std::vector<char> data_2(str_2.begin(), str_2.end());
  std::vector<char> compressed_data_2 = coder_.compress(data_2);
  std::vector<char> recovered_data_2 = coder_.decompress(compressed_data_2);
  for (int i = 0; i < data_2.size(); i++) {
    EXPECT_EQ(data_2[i], recovered_data_2[i]);
  }

  std::vector<char> data_3(256);
  for (int i = 0; i < 256; i++) data_3[i] = i;
  std::vector<char> compressed_data_3 = coder_.compress(data_3);
  std::vector<char> recovered_data_3 = coder_.decompress(compressed_data_3);
  for (int i = 0; i < data_3.size(); i++) {
    EXPECT_EQ(data_3[i], recovered_data_3[i]);
  }
}

}  // namespace
