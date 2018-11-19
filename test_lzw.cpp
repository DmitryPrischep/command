#include <string>
#include <map>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>

void encode(const std::string& data, std::back_insert_iterator<std::vector<int>> result, int dictionary_size) {

  int dict_size = dictionary_size;  

  std::map<std::string, int> dict;

  for (int i = 0; i < dict_size; i++) {
    dict[std::string(1, i)] = i;
  }
 
  std::string temp;
  for (std::string::const_iterator it = data.begin(); it != data.end(); ++it) {
    char symbol = *it;
    std::string loc_temp = temp + symbol;
    if (dict.find(loc_temp) != dict.end()) {
      temp = loc_temp;
    }
    else {
        *result++ = dict[temp];
        dict[loc_temp] = dict_size++;
        temp = std::string(1, symbol);
    }
  }
 
  if (!temp.empty()) {
    *result++ = dict[temp];
  }

  /*
  for (auto d : dict) {
    std::cout << "int: " << d.second << " string: " << d.first << std::endl;
  }
  */
}

std::string decode(std::vector<int>::iterator begin, std::vector<int>::iterator end, int dictionary_size) {

  int dict_size = dictionary_size;  

  std::map<int, std::string> dict;

  for (int i = 0; i < dict_size; i++) {
    dict[i] = std::string(1, i);
  }

  std::string temp(1, *begin++);
  std::string result = temp;
  std::string entry;

  while (begin != end) {
    int code = *begin;
    std::cout << code << std::endl;
    if (dict.find(code) != dict.end()) {
      entry = dict[code];
    }
    else {
      entry = temp + temp[0]; // if bad compress?
    }

    result += entry;
    dict[dict_size] = temp + entry[0];
    dict_size++;
    temp = entry;

    begin++;
  }

  return result;
}

std::vector<int> compress(const char* data, int size) {
  std::string str_data(data, size);
  std::vector<int> encoded;
  int dict_size = 256;
  encode(str_data, std::back_inserter(encoded), dict_size);

  return encoded;
}


std::vector<char> decompress(std::vector<int> data, int size) {

  int dict_size = 256;
  std::string decoded = decode(data.begin(), data.end(), 256);
  std::vector<char> result(decoded.begin(), decoded.end());
  return result;
}


int main() {

  int size = 256;
  char data[256];

  for (int i = 0; i < size; i++) {
    std::cin >> data[i];
  }

  std::vector<int> result = compress(data, size);

  for (auto x : result) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  std::cout << "Compress size: " << result.size() << std::endl;

  //std::string decoded = decompress(result, size);
  std::vector<char> decoded = decompress(result, size);
  for (auto x : decoded) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  std::cout << "Decompress size: " << decoded.size() << std::endl;
 
  return 0;
}
