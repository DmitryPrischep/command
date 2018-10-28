#include "../LZW.h"
#include "gtest/gtest.h"

class Test_LZW : public ::testing::Test {
};

TEST_F(Test_LZW, encode) {
	char* test_input_data[256];
	for (int i = 0; i < test_input_size; i++) {
		test_input_data[i] = '0';
	}

	char* test_output_data = encode(test_input_data, test_input_size);

	EXPECT_EQ(256 >= output_size_, true);
}

TEST_F(Test_LZW, decode) {
	char* test_input_data[32];
	for (int i = 0; i < 32; i++) {
		test_input_data[i] = '0';
	}

	char* test_output_data = decode(test_input_data, test_input_size);

	EXPECT_EQ(32 <= output_size_, true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}