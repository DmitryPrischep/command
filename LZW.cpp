#include "LZW.h"

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
	int dict_size = 256;
	encode(str_data, encoded, dict_size);

	// translate vector<int> to bits !!!
	//return bits
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
