#include <iostream>
#include <string>
#include <vector>

class Selector {
public:
	Selector();
	~Selector();
	Selector(const Selector&) = delete;
	Selector(Selector&) = delete;
	Selector& operator=(const Selector&) = delete;
	Selector& operator=(Selector&) = delete;

	std::string file_name;
	int file_size;

	void set_filesnames(std::vector<std::string>);

	bool has_file();
	bool has_data();
	void read_next_file();
	void read_next_data();
	
private:
	int buffer_size_;
	int file_index_;
	int data_index_;
	std::vector<std::string> input_files_;
};