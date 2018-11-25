#include <string>
#include <iterator>
#include <vector>
#include "Coder.hpp"

class LZW : public Coder {
public:
	LZW() {};
	LZW(const LZW&) = delete;
	LZW(LZW&&) = delete;
	LZW& operator=(const LZW&) = delete;
	LZW& operator=(LZW&&) = delete;
	~LZW() {};

	std::vector<unsigned char> compress(std::vector<unsigned char> data);
	std::vector<unsigned char> decompress(std::vector<unsigned char> data);

private:
	int dictionary_size_ = DATA_SIZE;
	void encode(const std::string& data, std::back_insert_iterator<std::vector<int>> result, int dictionary_size);
	std::string decode(std::vector<int>::iterator begin, std::vector<int>::iterator end, int dictionary_size);	
};