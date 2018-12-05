#include "Selector.hpp"

Selector::Selector(const int _data_size) : 
	data_size_(_data_size),
	filename_(""), 
	data_index_(0), 
	file_size_(0) 
{}

// входные данные - имена файлов, которые надо обработать
void Selector::set_filesnames(const std::set<std::string>& filesnames) {
	input_files_ = filesnames;
	it_ = input_files_.begin();
}

std::string Selector::get_filename() {
	return filename_;
}

bool Selector::has_file() {	
	if (it_ != input_files_.end()) {
		return true;
	}	
	else {
		file_.close();
		return false;
	}
}

bool Selector::has_data() {
	if (data_index_ < file_size_) {
		return true;
	}	
	else {
		file_.close();
		return false;
	}
}

int Selector::file_size() {
    file_.seekg(0, std::ios::end);
    int size = file_.tellg();
    file_.seekg(0, std::ios::beg);
	return size;
}

void Selector::read_file() {
	if (has_file()) {
		filename_ = *it_;
		file_.open(filename_, std::ios::binary);
		file_size_ = file_size();
    	file_.seekg(0, std::ios::beg);
	}
}

std::vector<char> Selector::read_data() {
	std::vector<char> data;
	for(int i = data_index_; (i < data_index_ + data_size_) && (i < file_size_) ; i++) {
		char byte = 0;
		file_.read( (char*)& byte, sizeof(char));
		data.push_back(byte);
	}
	return data;
}

void Selector::next_file() {
	if (it_ != input_files_.end()) {
		it_++;
		data_index_ = 0;
		file_size_ = 0;
	}
}

void Selector::next_data() {
	data_index_ += data_size_;
}

void Selector::close_file() {
	file_.close();;
}