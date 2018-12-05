#pragma once

#include <string>
#include <vector>
#define DATA_SIZE 256

class Coder {
public:
	Coder() : data_size_(DATA_SIZE) {}; /// deleted!!!
	Coder(const Coder&) = delete;
	Coder(Coder&&) = delete;
	Coder& operator=(const Coder&) = delete;
	Coder& operator=(Coder&&) = delete;
	virtual ~Coder() {};

	virtual std::vector<char> compress(const std::vector<char>& data) = 0;
	virtual std::vector<char> decompress(const std::vector<char>& data) = 0;

protected:
	const int data_size_;
};