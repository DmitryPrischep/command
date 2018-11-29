#include <iostream>
#include "../LZW.hpp"
#include <cassert>

template <typename T>
void print(const std::vector<T>& vect) {
    for ( auto v : vect) {
        std::cout << (int) v << " ";
    }
    std::cout << std::endl;
}

int main() {

    //std::string input = "Lempel–Ziv–Welch (LZW) is a universal lossless data compression algorithm created by Abraham Lempel, Jacob Ziv, and Terry Welch. It was published by Welch in 1984 as an improved implementation of the LZ78 algorithm published by Lempel and Ziv in 1978!!";
    //assert(input.size() == 256);

    std::string input;
    for (int i = 0; i < 256; i++) {
        char x;
        std::cin >> x;
        input += x;
    }

    std::vector<char> data(input.begin(), input.end());

    Coder* coder = new LZW();

    std::vector<char> compress_result = coder->compress(data);
    std::vector<char> decompress_result = coder->decompress(compress_result);

    print(compress_result);
    print(decompress_result);

    std::cout << "Input size: " << input.size() << std::endl;
    std::cout << "Compressed size: " << compress_result.size() << std::endl;
    std::cout << "Decompressed size: " << decompress_result.size() << std::endl;
    std::cout << "Compressing is: " << 100 - 100*compress_result.size()/decompress_result.size() << " %" << std::endl;


    delete coder;

    return 0;
}
