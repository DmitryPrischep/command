#include <string>
#include <vector>

class Coder {
public:
	Coder() {};
	Coder(const Coder&) = delete;
	Coder(Coder&&) = delete;
	Coder& operator=(const Coder&) = delete;
	Coder& operator=(Coder&&) = delete;
	~Coder() {};

	virtual std::vector<int> compress(const char* data, int size) = 0;
	virtual std::vector<char> decompress(std::vector<int> data, int size) = 0;
};