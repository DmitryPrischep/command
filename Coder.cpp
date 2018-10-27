#include <iostream>

class Coder {
public:
	Coder();
	~Coder() {delete[] output_data_;};
	Coder(const Coder&) = delete;
	Coder(Coder&) = delete;
	Coder& operator=(const Coder&) = delete;
	Coder& operator=(Coder&) = delete;

	char algorithm;
	void set_input_data_size(const int size);
	virtual char* encode(const char* data, int size) = 0;
	virtual char* decode(const char* data, int size) = 0;
	int get_output_size();

protected:
	int input_size_;
	int output_size_;
	const char* input_data_; // а нужна ли?
	char* output_data_;
};