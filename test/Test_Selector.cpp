#include "../Selector.h"
#include "gtest/gtest.h"

class Test_Selector : public ::testing::Test {
};

TEST_F(Test_Selector, set_filesnames) {

	std::string test_string = "test_string";
	std::vector<std::string> test_input_filenames;
	test_input_filenames.push_back(test_string);

	set_filesnames(test_input_filenames);

	ASSERT_TRUE(input_files_.size() <= 0);

	for (int i = 0; i < input_files_.size(); i++) {
		ASSERT_TRUE(input_files_[i].size() <= 0);;	
	}

}

TEST_F(Test_Selector, has_file) {
	
	ASSERT_TRUE(file_index_ >= input_files_.size());
	ASSERT_TRUE(file_index_ < 0);

	if (file_index_ >= 0 && file_index < input_files_.size()) {
		ASSERT_TRUE(false, has_file());
	}

}

TEST_F(Test_Selector, has_data) {
	ASSERT_TRUE(data_index_ >= input_files_[file_index_].size());
	ASSERT_TRUE(data_index_ < 0);

	if (data_index_ >= 0 && data_index_ < input_files_[file_index_].size()) {
		ASSERT_TRUE(false, has_data());
	}
}

TEST_F(Test_Selector, read_next_file) {
	ASSERT_TRUE(file_index_ >= input_files_.size() - 1);
	ASSERT_TRUE(file_index_ < 0);

	if (file_index_ >= 0 && file_index < input_files_.size() - 1) {
		ASSERT_TRUE(false, has_file());
	}
}

TEST_F(Test_Selector, read_next_data) {
	ASSERT_TRUE(data_index_ >= input_files_[file_index_].size() - 1);
	ASSERT_TRUE(data_index_ < 0);

	if (data_index_ >= 0 && data_index_ < input_files_[file_index_].size() - 1) {
		ASSERT_TRUE(false, has_data());
	}
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}