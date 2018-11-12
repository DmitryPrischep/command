#include <iostream>
#include <map>
#include <string>
#include <iterator>

class LZW : public Coder {
public:
	LZW() : Coder {};
	~LZW(delete[] output_data_;);
	LZW(const LZW&) = delete;
	LZW(LZW&) = delete;
	LZW& operator=(const LZW&) = delete;
	LZW& operator=(LZW&) = delete;

	char* compress(const char* data, int size);
	char* decompress(const char* data, int size);

protected:
	int input_size_;
	int output_size_;
	const char* input_data_; // а нужна ли?
	char* output_data_;

	encode(const std::string& data, std::back_insert_iterator result, dictionary_size);
	decode(std::back_insert_iterator begin, std::back_insert_iterator end, int dictionary_size);
	
};