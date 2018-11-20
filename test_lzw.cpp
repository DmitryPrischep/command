#include <iostream>
//#include "Coder.hpp"
#include "LZW.hpp"

int main() {

  int size = 256;
  char data[256];

  for (int i = 0; i < size; i++) {
    std::cin >> data[i];
  }

  Coder* coder = new LZW();

  std::vector<int> result = coder->compress(data, size);

  for (auto x : result) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  std::cout << "Compress size: " << result.size() << std::endl;

  //std::string decoded = decompress(result, size);
  std::vector<char> decoded = coder->decompress(result, size);
  for (auto x : decoded) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  std::cout << "Decompress size: " << decoded.size() << std::endl;

  delete coder;
 
  return 0;
}
