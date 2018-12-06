#include <iostream>
#include <cassert>
#include "../Selector.hpp"

template <typename T>
void print(const std::vector<T>& vect) {
	for ( auto v : vect) {
		std::cout << (int) v << ", ";
	}
	std::cout << std::endl;
}

int main() {

    const int data_size = 1048576; // 1 Mb

    std::set<std::string> data = {"in5.txt"};

    Selector selector(data_size);    
    selector.set_filesnames(data);
    long total_size = 0;
    long init_size = 1;

    //Coder* coder = new Huffman();
    while (selector.has_file()) {
        selector.read_file();

        // для записи
        init_size = selector.file_size();
        std::ofstream fout;
        std::string foutname = "res_";
        foutname += selector.get_filename();
        fout.open(foutname, std::ios::binary);

    	while (selector.has_data()) {
    		std::vector<char> buffer = selector.read_data();
    		selector.next_data();

            char algorithm = selector.get_algorithm();
            Coder* coder = selector.recomended_coder(algorithm);
    		std::vector<char> compressed_data = coder->compress(buffer);
            delete coder;
            std::cout << "algorithm: " << algorithm << std::endl;
    		std::cout << "compressed size: " << compressed_data.size() << std::endl;
            total_size += compressed_data.size();


            Coder* decoder = selector.recomended_coder(algorithm);
    		std::vector<char> decompressed_data = decoder->decompress(compressed_data);
            delete decoder;

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

    return 0;
}

