#include <iostream>
#include <map>
#include <string>

class AdaptiveHuffman : public Coder {
public:
	AdaptiveHuffman() : Coder {};
	~AdaptiveHuffman(delete[] output_data_;);
	AdaptiveHuffman(const AdaptiveHuffman&) = delete;
	AdaptiveHuffman(AdaptiveHuffman&) = delete;
	AdaptiveHuffman& operator=(const AdaptiveHuffman&) = delete;
	AdaptiveHuffman& operator=(AdaptiveHuffman&) = delete;

	char* encode(const char* data, int size);
	char* decode(const char* data, int size);

protected:
	int input_size_;
	int output_size_;
	const char* input_data_; // а нужна ли?
	char* output_data_;

private:
	std::map<char, int> huf_dict; 
	std::map<std::string, char> huf_code; // мб немного не так
};