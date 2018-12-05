#pragma once

#include <string>
#include <vector>

class Coder {
public:
	Coder() {};
	Coder(const Coder&) = delete;
	Coder(Coder&&) = delete;
	Coder& operator=(const Coder&) = delete;
	Coder& operator=(Coder&&) = delete;
	virtual ~Coder() {};

	virtual std::vector<char> compress(const std::vector<char>& data) = 0;
	virtual std::vector<char> decompress(const std::vector<char>& data) = 0;
};