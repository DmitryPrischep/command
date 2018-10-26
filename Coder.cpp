#include <iostream>

class Coder {
public:
	Coder();
	~Coder() {delete[] data_buffer_;};
	Coder(const Coder&) = delete;
	Coder(Coder&) = delete;
	Coder& operator=(const Coder&) = delete;
	Coder& operator=(Coder&) = delete;

	char algorithm;
	char* get_compressed_data();
	char* read_data();
	void refresh();
	virtual void compress();
	virtual void decompress();

private:
	char* data_buffer_;
};