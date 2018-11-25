#include "AdaptiveHuffman.hpp"
#include <algorithm>
#include <iostream>

AdaptiveHuffman::AdaptiveHuffman() : escape_(new Node(0, NODES_SIZE - 1)) , root_(escape_) {
	dec_ = root_;
    std::fill(std::begin(leaves_), std::end(leaves_), nullptr);
    std::fill(std::begin(nodes_), std::end(nodes_), nullptr);
    nodes_[root_->number] = root_;
}

std::vector<unsigned char> AdaptiveHuffman::compress(std::vector<unsigned char> data) {
	std::vector<uint8_t> bit_result;

	for (int i = 0; i < data.size(); i++) {
		std::vector<uint8_t> code = encode(data[i]);
		/*
		for (auto sym : code) {
			std::cout << (sym ? 1 : 0);
		}
		std::cout << std::endl;
		*/
		std::copy(std::begin(code), std::end(code), std::back_inserter(bit_result));
	}
	
	std::cout << "Bit results: " << std::endl;
	for (auto sym : bit_result) {
		std::cout << (sym ? 1 : 0);
	}
	std::cout << std::endl;
	

	unsigned char extra_bits = 0;
	if (bit_result.size() % 8 != 0) {
		//std::cout << "extra_bits + " << bit_result.size() % 8 << std::endl;
		extra_bits = 8 - bit_result.size() % 8;
		std::fill_n(std::back_inserter(bit_result), extra_bits, 0);
	}

	std::vector<unsigned char> result;
	for (int i = 0; i < bit_result.size(); i += 8) {
		unsigned char temp = 0;
		for (int j = 0; j < 8; j++) {
			if (bit_result[i+j] > 0) {
				//temp |= 1 << j;
				temp |= bit_result[i+j] << (7 - j);
			}		
		}
		result.push_back(temp);
	}
	result.push_back(extra_bits);

	return result;
}

std::vector<unsigned char> AdaptiveHuffman::decompress(std::vector<unsigned char> data) {
	std::vector<uint8_t> bit_input;
	for (auto data_byte : data) {
		for (int i = 0; i < 8; i++) {
			unsigned char bit = ( 1 & (data_byte >> (7 - i)) ) ? 1 : 0;
			bit_input.push_back(bit);
		}
	}
	unsigned char extra_bits = data[data.size() - 1];
	bit_input.resize(bit_input.size() - 8 - extra_bits);
	//
	for (auto b : bit_input) {
		std::cout << (uint16_t) b << "";
	}
	std::cout << std::endl;
	//
	while (bit_input.size() < 256) {
		bit_input.push_back(0);
	}
	std::vector<unsigned char> result = decode(bit_input);
	return result;
}

std::vector<uint8_t> AdaptiveHuffman::encode(unsigned char byte) noexcept {
	std::vector<uint8_t> code;

	// если узел в словаре
	if (leaves_[byte]) {
		code = get_code(leaves_[byte]);
	    update_tree(leaves_[byte]);
	}
	else {
		code = get_code(escape_);
		for (size_t i = 0; i < 8 * sizeof(unsigned char); i++) {
		    code.push_back(0x1 & (byte >> (7 - i))); // 1u ? // (8 - 1)*sizeof(unsigned char)
		}
		add_new_byte(byte);
	}

	return code;
}

std::vector<unsigned char> AdaptiveHuffman::decode(const std::vector<uint8_t>& code) noexcept {
    
    std::vector<unsigned char> result;
    std::vector<uint8_t> temp;
    temp.reserve(8);
    Node* decoder = root_;
    //Node* decoder = dec_;

    for (auto bit : code) {
    	// записываем в байт последовательнойть бит, пока не встретим escape 
		if (decoder == escape_) {
			std::cout << "see escape" << std::endl;
		    temp.push_back(bit);

		    if (temp.size() == 8 * sizeof(unsigned char)) {
				unsigned char byte = 0;
				for (size_t i = 0; i < 8 * sizeof(unsigned char); i++) {
				    byte |= temp[i] << (7 - i);
				}
				temp.clear();

				result.push_back(byte);
				add_new_byte(byte);
				decoder = root_;
		    }

		    continue;
		}

		//  к следующему узлу
		decoder = (bit) ? decoder->left : decoder->right;

		// Decode an existing node.
		// This stage occurs when decoder comes to a leaf but not the escape node.
		if (!decoder->left && decoder != escape_) {
			//std::cout << "dont see escape" << std::endl;
		    result.push_back(decoder->byte);
		    update_tree(leaves_[decoder->byte]);
		    decoder = root_;
		}
    }
    dec_ = decoder;
    return result;
}

std::vector<uint8_t> AdaptiveHuffman::get_code(const Node* node) const noexcept {
	// для узлов слева - 1, для узлов справа - 0
	std::vector<uint8_t> code;

	while (node != root_) {
		code.push_back(node->parent->left == node);
		node = node->parent;
	}
	std::reverse(std::begin(code), std::end(code));

	return code;
}

void AdaptiveHuffman::add_new_byte(unsigned char byte) noexcept {
    // создаем узел с данными
    escape_->left  = new Node(byte, escape_->number - 1, 0, escape_);
    // новый escape узел
    escape_->right = new Node(0, escape_->number - 2, 0, escape_);

    // для быстрого доступа
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
	// на всякий
	if (a == root_ || b == root_ || a == b || a->parent == b || b->parent == a) {
	    return;
	}

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

	for (size_t i = node->number + 1; i < NODES_SIZE 
			&& nodes_[i]->weight == node->weight; ++i) {
		highest = nodes_[i];
	}

	return highest;
}