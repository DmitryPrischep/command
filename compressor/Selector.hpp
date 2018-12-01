//#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <set>

class Selector {
public:
	Selector();
	Selector(const Selector&) = delete;
	Selector(Selector&&) = delete;
	Selector& operator=(const Selector&) = delete;
	Selector& operator=(Selector&&) = delete;
	~Selector() {};

	void set_filesnames(const std::set<std::string>& filesnames);
	std::string get_filename();
	bool has_file();
	bool has_data();
	int file_size();
	void read_file();
	std::vector<char> read_data();
	void next_file();
	void next_data();
	void close_file();
	
private:
	std::string filename_;
	int data_index_;
	int file_size_;
	std::set<std::string> input_files_;
	std::set<std::string>::iterator it_;
	std::ifstream file_;
};