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
    std::cout << "total_size: " << total_size << std::endl;	
// Теоретически можно обратиться к Архиватору и фзять у него внутренний счетчик кол-во байтов для проверки. Там на нем своя проверка есть, на коректность считывания.

    rw.TakeFileIn(outfile);
    std::cout << outfile << std::endl;
    std::cout << rw.HaveInFile() << std::endl;
    if (rw.HaveInFile()) {
        rw.ReadHeader();        
        std::cout << "rw.ReadHeader()" << std::endl;
        // не заходит в цикл
        for (auto i = 0; rw.File_header()->IsAmountFull(); i++) {
            std::cout << "loop - " << i << std::endl;
            rw.ReadFileHead();
            // file_info - где инициализация?
	    // Внутри rw в RW_Interface - там он один создается на запись и чтение и постепенно юзается. 
            for ( file_info.IsFileFull() )  {
                std::vector<char> uncompressed_data(rw.File_info()->FileSize());
                std::vector<char> decompressed_data = coder->decompress(uncompressed_data);
                std::cout << "decompressed: " << decompressed_data.size() << std::endl;
            }
        }
    }

    delete coder;
    return 0;
}
