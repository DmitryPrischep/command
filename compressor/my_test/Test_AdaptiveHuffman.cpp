#include <iostream>
#include <vector>
#include <string>
#include "../AdaptiveHuffman.hpp"

template <typename T>
void print(const std::vector<T>& vect) {
    for ( auto v : vect) {
        std::cout << (int) v << " ";
    }
    std::cout << std::endl;
}

int main() {

    std::string input;
    for (int i = 0; i < 256; i++) {
        char x;
        std::cin >> x;
        input += x;
    }

    std::vector<char> data(input.begin(), input.end());

    Coder* coder = new AdaptiveHuffman();

    std::vector<char> compress_result = coder->compress(data);
    std::vector<char> decompress_result = coder->decompress(compress_result);

    print(data);
    print(compress_result);
    print(decompress_result);

    std::cout << "Input size: " << input.size() << std::endl;
    std::cout << "Compressed size: " << compress_result.size() << std::endl;
    std::cout << "Decompressed size: " << decompress_result.size() << std::endl;
    std::cout << "Compressing is: " << 100 - 100*compress_result.size()/decompress_result.size() << " %" << std::endl;


    delete coder;

    return 0;
}
