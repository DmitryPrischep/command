#include <iostream>
#include "../LZW.hpp"

template <typename T>
void print(const std::vector<T>& vect) {
    for ( auto v : vect) {
        std::cout << (int) v << ", ";
    }
    std::cout << std::endl;
}

int main() {

    //char byte = 1;
    std::string input;
    while (std::cin) {
        char x;
        std::cin >> x;
        //x = byte++;
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
