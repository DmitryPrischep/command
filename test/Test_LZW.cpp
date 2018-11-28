#include <iostream>
#include "LZW.hpp"
#include <cassert>

int main() {

    std::string input = "Lempel–Ziv–Welch (LZW) is a universal lossless data compression algorithm created by Abraham Lempel, Jacob Ziv, and Terry Welch. It was published by Welch in 1984 as an improved implementation of the LZ78 algorithm published by Lempel and Ziv in 1978!!";

    assert(input.size() == 256);

    std::vector<char> data(input.begin(), input.end());

    Coder* coder = new LZW();

    std::vector<char> compress_result = coder->compress(data);
    std::vector<char> decompress_result = coder->decompress(compress_result);

    for (auto x : decompress_result) {
    std::cout << (char) x << "";
    }
    std::cout << std::endl;

    std::cout << "Input size: " << input.size() << std::endl;
    std::cout << "Compressed size: " << compress_result.size() << std::endl;
    std::cout << "Decompressed size: " << decompress_result.size() << std::endl;
    std::cout << "Compressing is: " << 100 - 100*compress_result.size()/decompress_result.size() << " %" << std::endl;


    delete coder;

    return 0;
}
