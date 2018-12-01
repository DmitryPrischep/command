#include <iostream>
#include <set>
#include "../Selector.hpp"
#include "../LZW.hpp"
#include "RW_Interface.h"
#include "FileInfo.h"
#include "RW_Liner.h"

template <typename T>
void print(const std::vector<T>& vect) {
	for ( auto v : vect) {
		std::cout << v << "";
	}
	std::cout << std::endl;
}

int main() {
    std::string outfile = "out.tartar";
    std::set<std::string> data = {"in1.txt", "in2.txt", "in3.txt"};

    Selector selector;    
    selector.set_filesnames(data);
    long total_size = 0;

    RW_Interface rw;
    rw.TakeFileOut(outfile);
    rw.BeginWrite();
    Coder* coder = new LZW();
    while (selector.has_file()) {
    	selector.read_file();

        FileInfo file(selector.get_filename(), selector.file_size());
        rw.TakeHeader(file);
    	while (selector.has_data()) {
    		std::vector<char> buffer = selector.read_data();
    		selector.next_data();
    		std::vector<char> compressed_data = coder->compress(buffer);
            total_size += compressed_data.size();
            rw.TakeBody(compressed_data);
    	}
    	selector.next_file();
    }
    rw.EndWriting();
    delete coder;
    std::cout << "total_size: " << total_size << std::endl;
    return 0;
}
