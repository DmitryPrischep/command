#pragma once

#include <string>
#include <vector>
#include "Coder.hpp"

class RLE : public Coder {
public:
	RLE();
	RLE(const RLE&) = delete;
	RLE(RLE&&) = delete;
	RLE& operator=(const RLE&) = delete;
	RLE& operator=(RLE&&) = delete;
	~RLE() {};

	std::vector<char> compress(const std::vector<char>& data) noexcept override;
	std::vector<char> decompress(const std::vector<char>& data) noexcept override;

private:
	std::vector<char> encode(const std::vector<char>& data) noexcept;
	std::vector<char> decode(const std::vector<char>& data) noexcept;	
};