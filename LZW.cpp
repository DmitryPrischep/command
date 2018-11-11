#include "LZW.h"

char* LZW::encode(const char* data, int size) {
	char* result = new char[size];
	int bits = 12;
	std::unorderer_map<std::string, int> encode_dict(1 << bits);
	for (int i = 0; i < size; i++) {
		encode_dict[std::string(1,i)] = i;
	}
	int code;
	int next_code = 256;
	std::string current_string;
	for (int i = 0; i < size; i++) {
		current_string += data[i];
		if (encode_dict.find(current_string) == encode_dict.end()) {
			if (next_code <= 1 << bits) {
				std::pair<std::string, int> node;
				node.first = current_string;
				node.second = next_code;
				next_code++;
				encode_dict.insert(node);
			}
			current_string.erase(current_string.size()-1);
			result[i] = (char) encode_dict[current_string];
			current_string = data[i];
		}
		if (current_string.size()) { // ???
			result[i] = (char) encode_dict[current_string];
			current_string = data[i];
		}
	}

}

/*
struct dictionary
{
   int code_value;
   int prefix_code;
   char character;
}
dict[TABLE_SIZE];


char* result = new char[size];
	int next_code = 257;
	int code;
	int max_code = (1 << 8) - 1;

	for (int i = 0; i < size; i++) {
		dict[i].code_value = -1;
	}

	for (int i = 0; i < size; i++) {
		index = find_dictionary_match(*(data+i), data[i]);
		if (dict[index].code_value != -1) {
			code = dict[index].code_value;
		}
		else {
			if (next_code <= max_code) {
				dict[index].code_value = next_code;
				next_code++;
				dict[index].prefix_code = code;
				dict[index].character = data[i];
			}
		}
	}
*/


char* LZW::decode(const char* data, int size) {
	int bits = 12;
	unordered_map<int, std::string> decode_dict(1 << bits);

	for (int i = 0; i < size; i++) {
		decode_dict[i] = std::string(1, i);
	}
	std::string prev_str;
	int code;
	int decode = 256;
	int i = 0;
	for ( int i = 0; i < size; i++) {
		if (decode_dict(data[i] == decode_dict.end())) {
			std::pair<int, std::string> node;
			node.first = code;
			node.second = prev_str + previous_string.substr(0,1);
			encode_dict.insert(node);
		}
		result[i] = (char) decode_dict[current_string];
		current_string = data[i];
		if (prev_str.size()) {
			std::pair<int, std::string> node;
			node.first = next_code;
			next_code++;
			node.second = prev_str + decode_dict[code][0];
			encode_dict.insert(node);
		}
		result[i] = (char) encode_dict[current_string];
		current_string = data[i];
	}

	
}