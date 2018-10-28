#include <iostream>
#include <map>
#include <string>

class LZW : public Coder {
public:
	LZW() : Coder {};
	~LZW(delete[] output_data_;);
	LZW(const LZW&) = delete;
	LZW(LZW&) = delete;
	LZW& operator=(const LZW&) = delete;
	LZW& operator=(LZW&) = delete;

	char* encode(const char* data, int size);
	char* decode(const char* data, int size);

protected:
	int input_size_;
	int output_size_;
	const char* input_data_; // а нужна ли?
	char* output_data_;

private:
	std::map <std::string, char> dict;
};