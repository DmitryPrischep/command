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

	std::vector<int> compress(const char* data, int size);
	std::vector<char> decompress(std::vector<int> data, int size);

private:
	void encode(const std::string& data, std::back_insert_iterator<std::vector<int>> result, int dictionary_size);
	std::string decode(std::vector<int>::iterator begin, std::vector<int>::iterator end, int dictionary_size);	
};