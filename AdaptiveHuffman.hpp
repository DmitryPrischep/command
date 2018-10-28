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
	std::map <std::string, int> haf_freq_; // unordered_map ?
	std::map <char, std::string> haf_dict_;
	auto cmp = [] ( std::pair<std::string, int> A, std::pair<std::string, int> B) { return A.second > B.second; }; // ток по человечески написать
	std::priority_queue <std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(cmp)> queue_(cmp);
};