	/*
	int fill = 0; // количество записанных бит в байте
	for (int i = 0; i < size; i++) {
		int value = encoded[i];
		int bits_count = log(value) / log(2); // количество значащих бит в числе
		for (int j = 0; j < bits_count; j++) { // не уверен, что учел выход за 8 бит !!!!!!
			if (fill == 0) {
				result.push_back(0);
			}
			result.back() |= ( (value >> j) & 1u ) << (7 - fill); // "конкатенируем" значащие биты
			fill = (fill + 1) % 8;
		}
	}
	*/

	//return result;

#include <iostream>
#include <vector>
#include <iterator>
#include "AdaptiveHuffman.hpp"

int main() {
	std::cout << "Start" << std::endl;
	
	int size = 256;
	char data[256];

	for (int i = 0; i < size; i++) {
		std::cin >> data[i];
	}

	std::cout << "Read data" << std::endl;

	AdaptiveHuffman* coder = new AdaptiveHuffman();

	std::vector<byte_t> r_buffer(size);
	std::vector<bit_t> w_buffer;

	for(int i = 0; i < size; i++) {
		r_buffer[i] = data[i];
	}


	std::cout << "Input size: " << r_buffer.size() << std::endl;

	for (int i = 0; i < size; i++) {
		std::vector<bit_t> code = coder->encode(r_buffer[i]);
		std::copy(std::begin(code), std::end(code), std::back_inserter(w_buffer));
	}

	byte_t extra_bits = 0;
	if (w_buffer.size() % 8 != 0) {
		extra_bits = 8 - w_buffer.size() % 8;
		std::fill_n(std::back_inserter(w_buffer), extra_bits, 0);
	}

	std::cout << "Result size: " << w_buffer.size() << std::endl;

	return 0;
}