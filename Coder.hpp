#include <string>
#include <vector>

#define DATA_SIZE 256

class Coder {
public:
	Coder(const int _data_size = DATA_SIZE) : data_size_(_data_size) {};
	Coder(const Coder&) = delete;
	Coder(Coder&&) = delete;
	Coder& operator=(const Coder&) = delete;
	Coder& operator=(Coder&&) = delete;
	~Coder() {};

	virtual std::vector<unsigned char> compress(const std::vector<unsigned char>& data) = 0;
	virtual std::vector<unsigned char> decompress(const std::vector<unsigned char>& data) = 0;

protected:
	const int data_size_;
};