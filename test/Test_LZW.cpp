#include "../LZW.h"
#include "gtest/gtest.h"

class Test_LZW : public ::testing::Test {
};

TEST_F(Test_LZW, compress) {
	int size = 256;
	std::vector<unsigned char> data(256);

	for (int i = 0; i < size; i++) {
		data[i] = '0';
	}

	std::vector<unsigned char> result = compress(data);

	EXPECT_EQ(46 == result.size(), true);
}

/*
TEST_F(Test_LZW, decompress) {
	int size = 256;
	std::vector<unsigned char> data = {'a', 'b', 'c'}; //

	std::vector<unsigned char> result = decompress(data);
	
	EXPECT_EQ(32 <= output_size_, true); //
}
*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}