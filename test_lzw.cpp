#include <iostream>
#include "LZW.hpp"

int main() {

  int size = 256;
  std::vector<unsigned char> data(256);

  for (int i = 0; i < size; i++) {
    std::cin >> data[i];
  }

  LZW* coder = new LZW();

  std::vector<int> result = coder->compress(data);

  for (auto x : result) {
    std::cout << (int) x << " ";
  }
  std::cout << std::endl;
  std::cout << "Compress size: " << result.size() << std::endl;

  std::vector<int> decoded = coder->decompress(result);
  for (auto x : decoded) {
    std::cout << (int) x << " ";
  }
  std::cout << std::endl;
  std::cout << "Decompress size: " << decoded.size() << std::endl;

  delete coder;
 
  return 0;
}
