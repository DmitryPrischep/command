#include "RLE.hpp"
#include <limits>

RLE::RLE() {

}

std::vector<char> RLE::compress(const std::vector<char>& data) noexcept {
	return encode(data);
}

std::vector<char> RLE::decompress(const std::vector<char>& data) noexcept {
	return decode(data);
}
	
std::vector<char> RLE::encode(const std::vector<char>& data) noexcept {
	std::vector<char> result;
	size_t char_limit = std::numeric_limits<unsigned char>::max();
	char same = 1;
	char various = -1;


	char prev = data[0];
	result.push_back(data[0]);

	// переделать
	for (int i = 1; i < data.size(); i++) {
		if (same < char_limit && prev == data[i]) {
			same++;
			various = -1;
		}
		else {
			result.push_back(same);
			result.push_back(data[i]);
			prev = data[i];
			same = 1;
			various--;
	}
}

std::vector<char> RLE::decode(const std::vector<char>& data) noexcept {

}