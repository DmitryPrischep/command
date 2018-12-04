#include <iostream>
#include <cassert>
#include "../Selector.hpp"
#include "../LZW.hpp"

template <typename T>
void print(const std::vector<T>& vect) {
	for ( auto v : vect) {
		std::cout << (int) v << ", ";
	}
	std::cout << std::endl;
}

int main() {

    //std::set<std::string> data = {"in1.txt"};
    //std::set<std::string> data = {"im1.png"};
    std::set<std::string> data = {"Jefferson Airplane - White Rabbit.mp3"};

    Selector selector;    
    selector.set_filesnames(data);
    long total_size = 0;

    Coder* coder = new LZW();
    while (selector.has_file()) {
        selector.read_file();

        std::ofstream fout;
        std::string foutname = "res_";
        foutname += selector.get_filename();
        fout.open(foutname, std::ios::binary);

    	while (selector.has_data()) {
    		std::vector<char> buffer = selector.read_data();
            //print(buffer);
            std::cout << "buffer size: " << buffer.size() << std::endl;
    		selector.next_data();

    		std::vector<char> compressed_data = coder->compress(buffer);
    		std::cout << "compressed size: " << compressed_data.size() << std::endl;
            total_size += compressed_data.size();

    		std::vector<char> decompressed_data = coder->decompress(compressed_data);
    		std::cout << "decompressed size: " << decompressed_data.size() << std::endl;
    		//print(decompressed_data);
            for (auto code : decompressed_data) {
                fout << code;
            }

    	}
    	selector.next_file();

        fout.close();
    }

    std::cout << "total_size: " << total_size << std::endl;
    return 0;
}
