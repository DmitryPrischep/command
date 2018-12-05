#include <iostream>
#include <cassert>
#include "../Selector.hpp"
#include "../LZW.hpp"
#include "../Huffman.hpp"

template <typename T>
void print(const std::vector<T>& vect) {
	for ( auto v : vect) {
		std::cout << (int) v << ", ";
	}
	std::cout << std::endl;
}

int main() {

    const int data_size = 1048576; // 1 Mb

    std::set<std::string> data = {"A.png"};

    Selector selector(data_size);    
    selector.set_filesnames(data);
    long total_size = 0;
    long init_size = 1;

    Coder* coder = new Huffman();
    while (selector.has_file()) {
        selector.read_file();
        init_size = selector.file_size();

        // для записи
        std::ofstream fout;
        std::string foutname = "res_";
        foutname += selector.get_filename();
        fout.open(foutname, std::ios::binary);

    	while (selector.has_data()) {
    		std::vector<char> buffer = selector.read_data();
            std::cout << "buffer size: " << buffer.size() << std::endl;
    		selector.next_data();

    		std::vector<char> compressed_data = coder->compress(buffer);
    		std::cout << "compressed size: " << compressed_data.size() << std::endl;
            total_size += compressed_data.size();

    		std::vector<char> decompressed_data = coder->decompress(compressed_data);
    		std::cout << "decompressed size: " << decompressed_data.size() << std::endl;

            // запись
            for (auto code : decompressed_data) {
                fout << code;
            }

    	}
    	selector.next_file();

        fout.close();
    }

    std::cout << "total_size: " << total_size << std::endl;
    std::cout << "init_size: "  << init_size << std::endl;
    std::cout << "Compression: "  << 100 - 100*total_size/init_size << " %" << std::endl;

    delete coder;
    return 0;
}

