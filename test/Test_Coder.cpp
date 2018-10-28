#include "../Coder.h"
#include "gtest/gtest.h"

class Test_Coder : public ::testing::Test {
};

TEST_F(Test_Coder, set_input_data_size) {
	
	int test_data_size = 256;
	set_input_data_size(test_data_size);

	EXPECT_EQ(test_data_size, input_size_);
	ASSERT_TRUE(input_size_ == 0);
}

TEST_F(Test_Coder, get_output_data_size) {

	int test_data_size = get_output_data_size();

	EXPECT_EQ(test_data_size, output_size_);
	ASSERT_TRUE(output_size_ == 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}