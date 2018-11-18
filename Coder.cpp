#include "Coder.h"
#include <vector>

void Coder::set_input_data_size(const int size) {

}


int Coder::get_output_size() {
	
}

void Coder::write_bit(std::vector<char>& data, bool bit, int& bits_count) {
	if (bits_count == 0) {
		data.push_back(0);
	}
	if (bit) {
		data.back() |= 1 << bits_count;
	}
	bits_count = (bits_count + 1) % 8;
}

void Coder::write_byte(char value) {
	for (int i = 0; i < 8; i++) {
		write_bit( (value & (1 << i)) != 0 );
	}
}