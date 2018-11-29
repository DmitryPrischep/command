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

#include <iostream>
#include <vector>
#include <iterator>
#include "AdaptiveHuffman.hpp"

int main() {
	
	int size = 256;
	std::vector<unsigned char> data(size);
	for (int i = 0; i < size; i++) {
		std::cin >> data[i];
		std::cout << (uint16_t) data[i] << " "; 
	}
	std::cout << std::endl;

	Coder* coder = new AdaptiveHuffman();
	std::vector<unsigned char> result = coder->compress(data);

	std::cout << "Result" << std::endl;
	for (auto b : result) {
		std::cout << (uint16_t) b << " ";
	}
	std::cout << std::endl;
	std::cout << "Total result size: " << result.size() << std::endl;

	std::vector<unsigned char> prev_data = coder->decompress(result);	
	std::cout << "Decompress" << std::endl;
	for (auto b : prev_data) {
		std::cout << (uint16_t) b << " ";
	}
	std::cout << std::endl;
	std::cout << "Total decompress size: " << prev_data.size() << std::endl;

	return 0;
}