#include "AdaptiveHuffman.h"

std::vector<bit_t> AdaptiveHuffman::encode(byte_t byte) noexcept {
	std::vector<bit_t> code;

	// if node already encoded
	if (leaves_[byte]) {
		code = get_code(leaves_[byte]);
	    update_tree(leaves_[byte]);
	}
	else {
		// output code = escape code + ascii code
		code = get_code(escape_);
		for (size_t i = 0; i < 8 * sizeof(byte_t); ++i) {
		    code.push_back(0x1 & (byte >> (7 - i)));
		}
		add_new_byte(byte);
	}

	return code;
}

std::vector<byte_t> AdaptiveHuffman::get_code(const Node* node) const noexcept {
	// left is 1 and right is 0
	std::vector<bit_t> code;

	while (node != root_) {
		code.push_back(node->parent->left == node);
		node = node->parent;
	}
	std::reverse(begin(code), end(code));

	return code;
}

std::vector<byte_t> Tree::decode(const std::vector<bit_t>& code) noexcept {
    
    std::vector<byte_t> result;

    for (bit_t bit : code) {
		// Decode a new byte.
		// This stage occurs when decoder comes to the escape node.
		// That means a new byte occur. So read next 8 bits from input sequence.
		if (decoder_ == escape_) {
		    ascii_.push_back(bit);

		    if (ascii_.size() == 8 * sizeof(byte_t)) {
				// convert a bit sequence into the byte
				byte_t byte = 0;
				for (size_t i = 0; i < 8 * sizeof(byte_t); ++i) {
				    byte |= (ascii_[i] << (7 - i));
				}
				ascii_.clear();

				result.push_back(byte);
				add_new_byte(byte);
				decoder_ = root_;
		    }

		    continue;
		}

		//  Go to the next node.
		decoder_ = (bit == 1 ? decoder_->left : decoder_->right);

		// Decode an existing node.
		// This stage occurs when decoder comes to a leaf but not the escape node.
		if (!decoder_->left && decoder_ != escape_) {
		    result.push_back(decoder_->byte);
		    update_tree(leaves_[decoder_->byte]);
		    decoder_ = root_;
		}
    }

    return result;
}

void Tree::add_new_byte(byte_t byte) noexcept {
    // create a node with data
    escape_->left  = new Node(byte, escape_->number - 1, 0, escape_);
    // create a new escape node
    escape_->right = new Node(0, escape_->number - 2, 0, escape_);

    // save fast-access pointers to the nodes
    leaves_[byte] = escape_->left;
    nodes_[escape_->left->number] =  escape_->left;
    nodes_[escape_->right->number] = escape_->right;
    escape_ = escape_->right;

    update_tree(leaves_[byte]);
}

void Tree::update_tree(Node* node) noexcept {

	while (node != nullptr) {
		Node* highest = highest_node(node); 
		exchange(node, highest);
		node->weight++;
		node = node->parent;
	}
}

void Tree::exchange(Node* a, Node* b) noexcept
{
	// avoid unnecessary and dangerous situations
	if (a == root_ || b == root_ || a == b || a->parent == b || b->parent == a) {
	    return;
	}

	// swap subtrees
	if (a->parent->left == a && b->parent->left == b) {
		std::swap(a->parent->left, b->parent->left);
	}
	else if (a->parent->left == a && b->parent->right == b) {
		std::swap(a->parent->left, b->parent->right);
	}
	else if (a->parent->right == a && b->parent->left == b) {
		std::swap(a->parent->right, b->parent->left);
	}
	else if (a->parent->right == a && b->parent->right == b) {
		std::swap(a->parent->right, b->parent->right);
	}

	std::swap(nodes_[a->number], nodes_[b->number]);
	std::swap(a->number, b->number);
	std::swap(a->parent, b->parent);
}

#define MAX_NODES 2 * (256 + 1)

Node* Tree::highest_node(Node* node) const noexcept {
	Node* highest = node;

	for (size_t i = node->number + 1; i <= MAX_NODES && _nodes[i]->weight == node->weight; ++i) {
		highest = _nodes[i];
	}

	return highest;
}