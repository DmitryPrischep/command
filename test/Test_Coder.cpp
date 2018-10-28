#include "../Coder.h"
#include "gtest/gtest.h"

class Test_Coder : public ::testing::Test {
};

TEST_F(Test_Coder, set_input_data_size) {

}

TEST_F(Test_Coder, get_output_size) {
	
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}