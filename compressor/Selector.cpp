#include "Selector.hpp"

Selector::Selector(const int _data_size) : 
	data_size_(_data_size),
	filename_(""), 
	data_index_(0), 
	file_size_(0),
	read_data_size_(0)
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
		file_.read((char*)& byte, sizeof(char));
		data.push_back(byte);
	}
	read_data_size_ = data.size();
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
	file_.close();
}

char Selector::get_algorithm(bool compress = true) {

	if (!compress) {
		algorithm_ = DO_NOT_COMPRESS;
		return algorithm_;
	}

	if (read_data_size_ >= 0) {
		algorithm_ = HUFFMAN_CODE;
	}
	else if (read_data_size_ < 65536 && read_data_size_ > 0) {
		algorithm_ = LZW_CODE;
	} else {
		algorithm_ = DO_NOT_COMPRESS;
	}
	return algorithm_; 
}

Coder* Selector::recomended_coder(char algorithm) {
	if (algorithm == HUFFMAN_CODE) {
		return new Huffman();
	} 
	else if (algorithm == LZW_CODE){
		return new LZW();
	} 
	else {
		return nullptr;
	}
}

std::vector<char> Selector::get_compressed_data(bool compress, char& algorithm) {
	std::vector<char> data = read_data();
	algorithm = get_algorithm(compress);

	Coder* coder = recomended_coder(algorithm);
	if (coder == nullptr) {
		return data;
	}
	std::vector<char> compressed_data = coder->compress(data);
	delete coder;

	if (compressed_data.size() < data.size()) {
		return compressed_data;
	}
	else {
		algorithm = DO_NOT_COMPRESS;
		return data;
	}
}

std::vector<char> Selector::get_decompressed_data(const std::vector<char>& data, char algorithm) {

	if (algorithm == DO_NOT_COMPRESS) {
		return data;
	}

	Coder* coder = recomended_coder(algorithm);
	if (coder == nullptr) {
		return data;
	}
	std::vector<char> decompressed_data = coder->decompress(data);
	delete coder;
	return decompressed_data;
}

// эксперимент с комбинированием алгоритмов
// вряд ли это будет использоваться
std::vector<char> Selector::get_maximum_compressed_data(char& algorithm) {
	std::vector<char> data = read_data();
	Coder* coder_1 = recomended_coder(HUFFMAN_CODE);
	Coder* coder_2 = recomended_coder(LZW_CODE);

	std::vector<char> compressed_data_1 = coder_1->compress(data);
	std::vector<char> compressed_data_2 = coder_2->compress(data);
	std::vector<char> compressed_data_3 = coder_1->compress(compressed_data_2);
	std::vector<char> compressed_data_4 = coder_2->compress(compressed_data_1);

	delete coder_1;
	delete coder_2;

	std::set<size_t> mins = {data.size(), compressed_data_1.size(), compressed_data_2.size(),
			compressed_data_3.size(), compressed_data_4.size()};
	auto min_size = *mins.begin();

	if (min_size == data.size()) {
		algorithm = DO_NOT_COMPRESS;
		return data;
	}
	if (min_size == compressed_data_1.size()) {
		algorithm = HUFFMAN_CODE;
		return compressed_data_1;
	}
	if (min_size == compressed_data_2.size()) {
		algorithm = LZW_CODE;
		return compressed_data_2;
	}
	if (min_size == compressed_data_3.size()) {
		algorithm = LZW_HUF_CODE;
		return compressed_data_3;
	}
	if (min_size == compressed_data_4.size()) {
		algorithm = HUF_LZW_CODE;
		return compressed_data_4;
	}
	algorithm = DO_NOT_COMPRESS;
	return data;
}