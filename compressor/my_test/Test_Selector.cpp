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

    std::set<std::string> data = {"A.mp4"};
    //std::set<std::string> data = {"A.mp3"};
    bool flag_compress = true; // надо сжимать или нет

    Selector selector(data_size);    
    selector.set_filesnames(data);
    long total_size = 0;
    long init_size = 1;

    while (selector.has_file()) {
        selector.read_file();

        // для записи
        init_size = selector.file_size();
        std::ofstream fout;
        std::string foutname = "res_";
        foutname += selector.get_filename();
        fout.open(foutname, std::ios::binary);
        //

    	while (selector.has_data()) {

            char algorithm;
    		std::vector<char> compressed_data = selector.get_compressed_data(flag_compress, algorithm);
            selector.next_data();

            // отладочный вывод
            std::cout << "algorithm: " << algorithm << std::endl;
    		std::cout << "compressed size: " << compressed_data.size() << std::endl;
            total_size += compressed_data.size();
            //

    		std::vector<char> decompressed_data = selector.get_decompressed_data(compressed_data, algorithm);
            // отладочный вывод
    		std::cout << "decompressed size: " << decompressed_data.size() << std::endl;
            //

            // для записи
            for (auto code : decompressed_data) {
                fout << code;
            }
            //

    	}
    	selector.next_file();

        // для записи
        fout.close();
        //
    }

    // отладочный вывод
    std::cout << "total_size: " << total_size << std::endl;
    std::cout << "init_size: "  << init_size << std::endl;
    std::cout << "Compression: "  << 100 - 100*total_size/init_size << " %" << std::endl;
    //

    return 0;
}

/*
Расширенная логика
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
*/