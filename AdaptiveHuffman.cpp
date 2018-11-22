#include "AdaptiveHuffman.hpp"
#include <algorithm>
#include <iostream>


#define MAX_NODES 2 * (256 + 1)

AdaptiveHuffman::AdaptiveHuffman()
    : escape_(new Node(0, MAX_NODES))
    , root_(escape_)
    , decoder_(root_)
{
    std::fill(std::begin(leaves_), std::end(leaves_), nullptr);
    std::fill(std::begin(nodes_), std::end(nodes_), nullptr);

    nodes_[root_->number] = root_;
    ascii_.reserve(8);
}

std::vector<char> AdaptiveHuffman::compress(std::vector<char> data) noexcept {
	std::vector<bit_t> bit_result;
	std::vector<byte_t> input_data;
	for (auto x : data) {
		input_data.push_back(x);
	}

	for (int i = 0; i < input_data.size(); i++) {
		std::vector<bit_t> code = encode(input_data[i]);
		std::cout << "internal code (size): " << code.size() << std::endl;
		std::copy(std::begin(code), std::end(code), std::back_inserter(bit_result));
	}

	byte_t extra_bits = 0;
	if (bit_result.size() % 8 != 0) {
		extra_bits = 8 - bit_result.size() % 8;
		std::fill_n(std::back_inserter(bit_result), extra_bits, 0);
	}

	/*
	for (auto b : bit_result) {
		std::cout << (int) b;
	}
	std::cout << std::endl;
	std::cout << "Result size: " << bit_result.size() << std::endl;
	*/

	std::vector<char> result;
	for (int i = 0; i < bit_result.size() / 8; i++) {
		int temp = 0;
		for (int j = 0; j < 8; j++) {
			if ( (char) bit_result[i+j] > 0) {
				temp |= 1 << j;
			}		
		}
		result.push_back(temp);
	}

	return result;
}

std::vector<bit_t> AdaptiveHuffman::encode(byte_t byte) noexcept {
	std::vector<bit_t> code;
	std::cout << "input byte: " << byte << std::endl;

	// if node already encoded
	if (leaves_[byte]) {
		code = get_code(leaves_[byte]);
		std::cout << "code already encoded: " << code.size() << std::endl;
	    update_tree(leaves_[byte]);
	}
	else {
		// output code = escape code + ascii code
		code = get_code(escape_);
		std::cout << "new byte: " << code.size() << std::endl;
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

	std::cout << node->number << std::endl;

	while (node != root_) {
		code.push_back(node->parent->left == node);
		node = node->parent;
	}
	std::reverse(std::begin(code), std::end(code));

	return code;
}

std::vector<byte_t> AdaptiveHuffman::decode(const std::vector<bit_t>& code) noexcept {
    
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

void AdaptiveHuffman::add_new_byte(byte_t byte) noexcept {
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

void AdaptiveHuffman::update_tree(Node* node) noexcept {

	while (node != nullptr) {
		Node* highest = highest_node(node); 
		exchange(node, highest);
		node->weight++;
		node = node->parent;
	}
}

void AdaptiveHuffman::exchange(Node* a, Node* b) noexcept
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

Node* AdaptiveHuffman::highest_node(Node* node) const noexcept {
	Node* highest = node;

	for (size_t i = node->number + 1; i <= MAX_NODES 
			&& nodes_[i]->weight == node->weight; ++i) {
		highest = nodes_[i];
	}

	return highest;
}