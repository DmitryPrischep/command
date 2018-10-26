#include <iostream>
#include <string>
#include <vector>

class Selector {
public:
	Selector();
	~Selector() {delete[] data_buffer_;};
	Selector(const Selector&) = delete;
	Selector(Selector&) = delete;
	Selector& operator=(const Selector&) = delete;
	Selector& operator=(Selector&) = delete;

	std::string filename;
	//// and another file params
	bool has_file();
	void read_file();
	bool file_has_data();
	void read_next_file();
	void read_next_data();
	void get_input_files();
	
private:
	const int buffer_size_;
	int file_index_;
	int data_index_;
	int file_size_;
	std::vector<std::string> input_files_;
	void open_file();
};