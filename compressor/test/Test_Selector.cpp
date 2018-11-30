#include <iostream>
#include <cassert>
#include "../Selector.hpp"
#include "../LZW.hpp"

template <typename T>
void print(const std::vector<T>& vect) {
	for ( auto v : vect) {
		std::cout << v << "";
	}
	std::cout << std::endl;
}

int main() {

    std::set<std::string> data = {"in1.txt", "in2.txt", "in3.txt"};Глава 01.mp3

    Selector selector;    
    selector.set_filesnames(data);
    long total_size = 0;

    while (selector.has_file()) {
    	selector.read_file();
    	while (selector.has_data()) {
    		std::vector<char> buffer = selector.read_data();
            //std::cout << "buffer size: " << buffer.size() << std::endl;
            assert(buffer.size() <= 256);
    		//print(data);
    		selector.next_data();

    		Coder* coder = new LZW();
    		std::vector<char> compressed_data = coder->compress(buffer);
    		//std::cout << "compressed size: " << compressed_data.size() << std::endl;
            total_size += compressed_data.size();

    		//std::vector<char> decompressed_data = coder->decompress(compressed_data);
    		//std::cout << "decompressed size: " << decompressed_data.size() << std::endl;
    		//print(decompressed_data);
            //break;

    	}
    	selector.next_file();
    }

    std::cout << "total_size: " << total_size << std::endl;
    return 0;
}
