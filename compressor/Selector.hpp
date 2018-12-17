// Читает фиксированные отрезки байт 
// из входных файлов и сжимает их
#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <set>
#include "LZW.hpp"
#include "Huffman.hpp"

const char HUFFMAN_CODE = 'h';
const char LZW_CODE = 'l';
const char ADA_HUF_CODE = 'a';
const char RLE_CODE = 'r';
const char ARTH_CODE = 'A';
const char DO_NOT_COMPRESS = '0';

class Selector {
public:
	Selector(const int _data_size);
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

	char get_algorithm(bool compress);
	Coder* recomended_coder(char algorithm);
	std::vector<char> get_compressed_data(bool compress, char& algorithm);
	std::vector<char> get_decompressed_data(const std::vector<char>& data, char algorithm);

private:
	char algorithm_;
	std::string filename_;
	const int data_size_;
	int read_data_size_;
	int data_index_;
	int file_size_;
	std::set<std::string> input_files_;
	std::set<std::string>::iterator it_;
	std::ifstream file_;
};