#pragma once

#include <string>
#include <vector>
#include "Coder.hpp"

class Arithmetic : public Coder {
public:
	Arithmetic();
	Arithmetic(const Arithmetic&) = delete;
	Arithmetic(Arithmetic&&) = delete;
	Arithmetic& operator=(const Arithmetic&) = delete;
	Arithmetic& operator=(Arithmetic&&) = delete;
	~Arithmetic() {};

	std::vector<char> compress(const std::vector<char>& data) noexcept override;
	std::vector<char> decompress(const std::vector<char>& data) noexcept override;

private:
	std::vector<char> encode(const std::vector<char>& data) noexcept;
	std::vector<char> decode(const std::vector<char>& data) noexcept;	
};