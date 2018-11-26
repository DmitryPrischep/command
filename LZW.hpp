#include <string>
#include <iterator>
#include <vector>
#include "Coder.hpp"


#define DATA_SIZE 256

//class LZW : public Coder {
class LZW {
public:
	LZW();
	LZW(const LZW&) = delete;
	LZW(LZW&&) = delete;
	LZW& operator=(const LZW&) = delete;
	LZW& operator=(LZW&&) = delete;
	~LZW() {};

	std::vector<int> compress(std::vector<unsigned char> data);
	std::vector<int> decompress(std::vector<int> data);

private:
	int dictionary_size_;
	void encode(const std::string& data, std::back_insert_iterator<std::vector<int>> result);
	std::string decode(std::vector<int>::iterator begin, std::vector<int>::iterator end);	
};