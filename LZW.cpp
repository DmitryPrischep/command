#include "LZW.hpp"
#include <map>
#include <cmath>
#include <iterator>

//#include <iostream>

LZW::LZW() : dictionary_size_(DATA_SIZE) {

}

std::vector<unsigned char> LZW::compress(const std::vector<unsigned char>& data) {
  std::string str_data(data.begin(), data.end());
  std::vector<int> encoded = encode(str_data);

  std::vector<unsigned char> result;
  for (auto byte : encoded) {
    unsigned char high = (byte >> 8) & 0xff;
    unsigned char little = byte & 0xff;
    //std::cout << (uint16_t) high << " " << (uint16_t) little << " ";
    result.push_back(high);
    result.push_back(little);
  }
  //std::cout << std::endl;

  return result;
}


std::vector<unsigned char> LZW::decompress(const std::vector<unsigned char>& data) {

  std::vector<int> data2;
  for (int i = 0; i < data.size(); i += 2) {
    int element = (data[i] << 8) | data[i+1];
    //std::cout << element << " ";
    data2.push_back(element);
  }
  //std::cout << std::endl;

  std::string decoded = decode(data2);

  std::vector<int> result2(decoded.begin(), decoded.end());
  std::vector<unsigned char> result(result2.size());
  for (int i = 0; i < result2.size(); i++) {
    result[i] = (unsigned char) result2[i];
  }
  return result;
}

std::vector<int> LZW::encode(const std::string& data) {

  int dict_size = dictionary_size_;  
  std::map<std::string, int> dict;

  std::vector<int> result;
  //std::back_insert_iterator<std::vector<int>> result_iter = std::back_inserter(result);
  auto result_iter = std::back_inserter(result);

  for (int i = 0; i < dict_size; i++) {
    dict[std::string(1, i)] = i;
  }
 
  std::string temp;
  for (auto it = data.begin(); it != data.end(); ++it) {
    char symbol = *it;
    std::string loc_temp = temp + symbol;
    if (dict.find(loc_temp) != dict.end()) {
      temp = loc_temp;
    }
    else {
        *result_iter++ = dict[temp];
        dict[loc_temp] = dict_size++;
        temp = std::string(1, symbol);
    }
  }
 
  if (!temp.empty()) {
    *result_iter++ = dict[temp];
  }

  return result;

}

std::string LZW::decode(const std::vector<int>& data) {

  int dict_size = dictionary_size_;  
  std::map<int, std::string> dict;

  auto data_it = data.begin();

  for (int i = 0; i < dict_size; i++) {
    dict[i] = std::string(1, i);
  }

  std::string temp(1, *data_it++);
  std::string result = temp;
  std::string entry;

  while (data_it != data.end()) {
    int code = *data_it;
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

    data_it++;
  }

  return result;
}