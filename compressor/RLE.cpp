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

	char prev = data[0]; // ??
	result.push_back(data[0]);

	for(auto it = data.begin(); it != data.end(); ++it) {
		same = 1;
		if (*it == prev) {
			while (*it == prev) {
				same++;
				it++;
			}
			result.push_back(prev);
			result.push_back(same);
			various = -1;
		}
		else {
			result.push_back(*it);
			result.push_back(various);
			various--;
		}
	}

	return result;
}

std::vector<char> RLE::decode(const std::vector<char>& data) noexcept {
	std::vector<char> result;

	for(auto it = data.begin(); it != data.end(); ++it) {
		char numbers = *it;
		++it;
		if (numbers > 0) {
			while (numbers > 0) {
				result.push_back(*it);
				numbers--;
			}
		}
		else {
			numbers *= -1;
			while (numbers > 0) {
				result.push_back(*it);
				numbers--;
				++it;
			}
		}
	}
	return result;

}