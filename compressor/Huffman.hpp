#pragma once

#include <string>
#include <vector>
#include "Coder.hpp"
//#include "Node.hpp"
#include <map>

class Huffman : public Coder {
public:
	Huffman();
	Huffman(const Huffman&) = delete;
	Huffman(Huffman&&) = delete;
	Huffman& operator=(const Huffman&) = delete;
	Huffman& operator=(Huffman&&) = delete;
	~Huffman() {};

	std::vector<char> compress(const std::vector<char>& data) noexcept override;
	std::vector<char> decompress(const std::vector<char>& data) noexcept override;

private:
	int dict_size_;
	char empty_bits_;
    std::map <char, std::string> haf_dict_;
    std::map <std::string, char> rev_haf_dict_;
	std::vector<char> encode(const std::vector<char>& data) noexcept;
	std::vector<char> decode(const std::string& data) noexcept;
	std::vector<char> make_bytes(std::vector<char>& data) noexcept;
	std::vector<char> make_bits(const std::vector<char>& data) noexcept;
	std::vector<char> save_dict() noexcept;
	int recover_dict(const std::vector<char>& data) noexcept;

};