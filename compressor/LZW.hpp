#pragma once

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

	std::vector<char> compress(const std::vector<char>& data) noexcept; // hfp,bn yf gjlrkfccs
	std::vector<char> decompress(const std::vector<char>& data) noexcept;

private:
	std::vector<int> encode(const std::vector<char>& data) noexcept;
	std::string decode(const std::vector<int>& data) noexcept;	
	int calculate_bit_resolution(const int data_size) noexcept;
};