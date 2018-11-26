#include "LZW.hpp"
#include <map>
#include <cmath>

#include <iostream>

LZW::LZW() : dictionary_size_(DATA_SIZE) {

}

std::vector<int> LZW::compress(std::vector<unsigned char> data) {
  std::string str_data(data.begin(), data.end());
  std::vector<int> encoded;
  encode(str_data, std::back_inserter(encoded));

  std::vector<unsigned char> result;
  for (auto byte : encoded) {
    unsigned char high = (byte >> 16) & 0xffff; // 256?
    unsigned char little = byte & 0xffff;
    std::cout << (uint16_t) high << " " << (uint16_t) little << " ";
    result.push_back(high);
    result.push_back(little);
  }
  std::cout << std::endl;

  return encoded;
}


std::vector<int> LZW::decompress(std::vector<int> data) {

  std::string decoded = decode(data.begin(), data.end());

  std::vector<int> result(decoded.begin(), decoded.end());
  return result;
}

void LZW::encode(const std::string& data, std::back_insert_iterator<std::vector<int>> result) {

  int dict_size = dictionary_size_;  

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

std::string LZW::decode(std::vector<int>::iterator begin, std::vector<int>::iterator end) {

  int dict_size = dictionary_size_;  

  std::map<int, std::string> dict;

  for (int i = 0; i < dict_size; i++) {
    dict[i] = std::string(1, i);
  }

  std::string temp(1, *begin++);
  std::string result = temp;
  std::string entry;

  while (begin != end) {
    int code = *begin;
    //std::cout << code << std::endl;
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