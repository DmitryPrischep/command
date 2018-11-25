#include <iostream>
//#include "Coder.hpp"
#include "LZW.hpp"

int main() {

  int size = 256;
  std::vector<unsigned char> data(256);

  for (int i = 0; i < size; i++) {
    std::cin >> data[i];
  }

  Coder* coder = new LZW();

  std::vector<unsigned char> result = coder->compress(data);

  for (auto x : result) {
    std::cout << (uint16_t) x << " ";
  }
  std::cout << std::endl;
  std::cout << "Compress size: " << result.size() << std::endl;
  //std::string decoded = decompress(result, size);
  std::vector<unsigned char> decoded = coder->decompress(result);
  for (auto x : decoded) {
    std::cout << (uint16_t) x << " ";
  }
  std::cout << std::endl;
  std::cout << "Decompress size: " << decoded.size() << std::endl;

  delete coder;
 
  return 0;
}
