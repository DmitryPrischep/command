#include <iostream>
#include "../Huffman.hpp"

template <typename T>
void print(const std::vector<T>& vect) {
    for ( auto v : vect) {
        std::cout << (char) v << "";
    }
    std::cout << std::endl;
}

int main() {

    std::string input;
    char byte = 0;
    for (int i = 0; i < DATA_SIZE; i++) {
        char x;
        std::cin >> x;
        //x = byte++;
        input += x;
    }

    std::vector<char> data(input.begin(), input.end());

    //Coder* coder = new LZW();
    Coder* coder = new Huffman();

    std::vector<char> compress_result = coder->compress(data);
    //print(compress_result);
    std::vector<char> decompress_result = coder->decompress(compress_result);
    //print(decompress_result);

    std::cout << "Input size: " << input.size() << std::endl;
    std::cout << "Compressed size: " << compress_result.size() << std::endl;
    std::cout << "Decompressed size: " << decompress_result.size() << std::endl;
    std::cout << "Compressing is: " << 100 - 100*compress_result.size()/decompress_result.size() << " %" << std::endl;


    delete coder;

    return 0;
}
