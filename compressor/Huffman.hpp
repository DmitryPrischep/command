#include <string>
#include <iterator>
#include <vector>
#include "Coder.hpp"

#define NODES_SIZE 2 * DATA_SIZE + 1

class Huffman : public Coder {
public:
	Huffman();
	Huffman(const Huffman&) = delete;
	Huffman(Huffman&&) = delete;
	Huffman& operator=(const Huffman&) = delete;
	Huffman& operator=(Huffman&&) = delete;
	~Huffman() {}; //{delete escape_;};

	std::vector<char> compress(const std::vector<char>& data);
	std::vector<char> decompress(const std::vector<char>& data);

private:



	/*
	int nodes_size_;
	Node* escape_;					// указатель на узел со спец символом
	Node* root_;					// указатель на корень
	Node* leaves_[DATA_SIZE];   // fast access to the leaves by byte
	Node* nodes_[NODES_SIZE];		// доступ по индексу к узлам


	std::vector<uint8_t> encode(char byte) noexcept;
	std::vector<char> decode(const std::vector<uint8_t>& code) noexcept;

	std::vector<uint8_t> get_code(const Node* node) const noexcept;
	void add_new_byte(char byte) noexcept;
	void update_tree(Node* node) noexcept;
	void exchange(Node* a, Node* b) noexcept;
	Node* highest_node(Node* node) const noexcept;
	*/
};