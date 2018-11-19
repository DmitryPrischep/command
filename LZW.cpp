#include "LZW.h"
#include <map>
#include <cmath>

void LZW::encode(const std::string& data, std::back_insert_iterator result, dictionary_size) {

	int dict_size = dictionary_size;  

	std::map<std::string, int> dict;

	for (int i = 0; i < dict_size; i++) {
		dict[std::string(1, i)] = i;
	}
 
	std::string temp;
	for (std::string::const_iterator it = uncompressed.begin(); it != uncompressed.end(); ++it) {
		char symbol = *it;
		std::string loc_temp = temp + symbol;
		if (dict.find(loc_temp) != dict.end()) {
			temp = loc_temp;
		}
		else {
	  		*result++ = dict[temp];
	  		dict[loc_temp] = dict_size++;
	  		temp = std::string(1, symbol);
		}
	}
 
	if (!temp.empty()) {
		*result++ = dict[temp];
	}
}

std::string LZW::decode(std::back_insert_iterator begin, std::back_insert_iterator end, int dictionary_size) {

	int dict_size = dictionary_size;  

	std::map<int, std::string> dict;

	for (int i = 0; i < dict_size; i++) {
		dict[i] = std::string(1, i);
	}

	std::string temp(1, *begin++);
	std::string result = temp;
	std::string entry;

	while (begin != end) {
		int code = *begin;
		if (dict.find(code) != dict.end()) {
			entry = dict[code];
		}
		else {
			entry = temp + temp[0]; // if bad compress?
		}

		result += entry;
		dict[dict_size] = temp + entry[0];
		dict_size++;
	 	temp = entry;
	}

	return result;
}

char* LZW::compress(const char* data, int size) {
	std::string str_data(data, size);
	std::vector<int> encoded;
	std::vector<char> result;
	int dict_size = 256;
	encode(str_data, std::back_inserter(encoded), dict_size);

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

}


char* LZW::decompress(const char* data, int size) {
	// make data from bits !!!
	char* new_data;
	std::vector<int> decoded(new_data, std::end(data)); // char* -> int* ????
	int dict_size = 256;
	std::string result = decode(decoded.begin(), decoded.end(), dict_size);

	char* result;
	// make char array from string
	return result;
}
