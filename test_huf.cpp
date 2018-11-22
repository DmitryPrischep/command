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
	std::cout << "Start" << std::endl;
	
	int size = 256;
	std::vector<char> data(size);
	for (int i = 0; i < size; i++) {
		std::cin >> data[i];
	}

	AdaptiveHuffman* coder = new AdaptiveHuffman();
	std::vector<char> result = coder->compress(data);

	std::cout << "Result" << std::endl;
	for (auto b : result) {
		std::cout << (int) b;
	}
	std::cout << std::endl;
	std::cout << "Total result size: " << result.size() << std::endl;

	return 0;
}