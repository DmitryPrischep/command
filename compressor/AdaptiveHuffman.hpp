#include <string>
#include <vector>
#include "Coder.hpp"
#include "Node.hpp"

const char DATA_SIZE = 2048;
const char NODES_SIZE = 2*DATA_SIZE + 1;

class AdaptiveHuffman : public Coder {
public:
	AdaptiveHuffman();
	AdaptiveHuffman(const AdaptiveHuffman&) = delete;
	AdaptiveHuffman(AdaptiveHuffman&&) = delete;
	AdaptiveHuffman& operator=(const AdaptiveHuffman&) = delete;
	AdaptiveHuffman& operator=(AdaptiveHuffman&&) = delete;
	~AdaptiveHuffman() {delete escape_;};

	std::vector<char> compress(const std::vector<char>& data) noexcept override;
	std::vector<char> decompress(const std::vector<char>& data) noexcept override;

private:
	int nodes_size_;
	Node* escape_;					// указатель на узел со спец символом
	Node* root_;					// указатель на корень
	Node* leaves_[DATA_SIZE];   	// словарь
	Node* nodes_[NODES_SIZE];		// доступ по индексу к узлам

	std::vector<uint8_t> encode(char byte) noexcept;
	std::vector<char> decode(const std::vector<uint8_t>& code) noexcept;

	std::vector<uint8_t> get_code(const Node* node) const noexcept;
	void add_new_byte(char byte) noexcept;
	void update_tree(Node* node) noexcept;
	void exchange(Node* a, Node* b) noexcept;
	Node* highest_node(Node* node) const noexcept;
};