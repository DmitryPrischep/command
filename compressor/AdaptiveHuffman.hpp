#include <string>
#include <iterator>
#include <vector>
#include "Coder.hpp"
#include "Node.hpp"

#define NODES_SIZE 2 * DATA_SIZE + 1

class AdaptiveHuffman : public Coder {
public:
	AdaptiveHuffman();
	AdaptiveHuffman(const AdaptiveHuffman&) = delete;
	AdaptiveHuffman(AdaptiveHuffman&&) = delete;
	AdaptiveHuffman& operator=(const AdaptiveHuffman&) = delete;
	AdaptiveHuffman& operator=(AdaptiveHuffman&&) = delete;
	~AdaptiveHuffman() {}; //{delete escape_;};

	std::vector<unsigned char> compress(std::vector<unsigned char> data);
	std::vector<unsigned char> decompress(std::vector<unsigned char> data);

private:
	int nodes_size_;
	Node* escape_;					// указатель на узел со спец символом
	Node* root_;					// указатель на корень
	Node* leaves_[DATA_SIZE];   // fast access to the leaves by byte
	Node* nodes_[NODES_SIZE];		// доступ по индексу к узлам
	Node* dec_;


	std::vector<uint8_t> encode(unsigned char byte) noexcept;
	std::vector<unsigned char> decode(const std::vector<uint8_t>& code) noexcept;

	std::vector<uint8_t> get_code(const Node* node) const noexcept;
	void add_new_byte(unsigned char byte) noexcept;
	void update_tree(Node* node) noexcept;
	void exchange(Node* a, Node* b) noexcept;
	Node* highest_node(Node* node) const noexcept;
};