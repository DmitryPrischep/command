#include <string>
#include <vector>
#include "Coder.hpp"

class LZW : public Coder {
public:
	LZW();
	LZW(const LZW&) = delete;
	LZW(LZW&&) = delete;
	LZW& operator=(const LZW&) = delete;
	LZW& operator=(LZW&&) = delete;
	~LZW() {};

	std::vector<unsigned char> compress(const std::vector<unsigned char>& data);
	std::vector<unsigned char> decompress(const std::vector<unsigned char>& data);

private:
	const int dictionary_size_;
	std::vector<int> encode(const std::string& data);
	std::string decode(const std::vector<int>& data);	
};