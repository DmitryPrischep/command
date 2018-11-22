#include <string>
#include <iterator>
#include <vector>
#include "Coder.hpp"
#include "Node.hpp"

typedef std::uint_fast8_t byte_t;

//A bit type declaration. Yep, I know it's not a really bit.
//This type was introduced specially to increase code readability.
typedef std::uint_fast8_t bit_t;

//class AdaptiveHuffman : public Coder {
class AdaptiveHuffman {
public:
	AdaptiveHuffman();
	AdaptiveHuffman(const AdaptiveHuffman&) = delete;
	AdaptiveHuffman(AdaptiveHuffman&&) = delete;
	AdaptiveHuffman& operator=(const AdaptiveHuffman&) = delete;
	AdaptiveHuffman& operator=(AdaptiveHuffman&&) = delete;
	~AdaptiveHuffman() {};

	
	std::vector<bit_t> encode(byte_t byte) noexcept;
	std::vector<byte_t> decode(const std::vector<bit_t>& code) noexcept;



private:
	Node* escape_;                 //! a pointer to the special escape node
	Node* root_;                   //! a tree root
	Node* leaves_[256 + 1];  //! fast access to the leaves by byte
	Node* nodes_[515];   //! fast access to the nodes by number
	Node* decoder_;                //! pointer to the current decoding node
	std::vector<bit_t> ascii_;     //! decoder ASCII buffer

	std::vector<bit_t> get_code(const Node* node) const noexcept;
	void add_new_byte(byte_t byte) noexcept;
	void update_tree(Node* node) noexcept;
	void exchange(Node* a, Node* b) noexcept;
	Node* highest_node(Node* node) const noexcept;

	//std::vector<bit_t> encode(byte_t byte) noexcept override;
	//std::vector<byte_t> decode(const std::vector<bit_t>& code) noexcept override;

};