#include "LZW.hpp"
#include <map>
#include <cmath>
#include <iterator>

LZW::LZW() : dictionary_size_(DATA_SIZE), bit_resolution_(9) {

}

std::vector<unsigned char> LZW::compress(const std::vector<unsigned char>& data) {
    std::string str_data(data.begin(), data.end());
    std::vector<int> encoded = encode(str_data);

    std::vector<uint8_t> bits;
    for (auto byte : encoded) {
        for (int i = 16 - bit_resolution_; i < 16; i++) {
            unsigned char bit = ( 1 & (byte >> (15 - i)) ) ? 1 : 0;
            bits.push_back(bit);
        }
    }

    std::vector<unsigned char> result;
    for (int i = 0; i < bits.size(); i += 8) {
        unsigned char temp = 0;
        for (int j = 0; j < 8; j++) {
            temp |= bits[i+j] << (7 - j);
        }
        result.push_back(temp);
    }
    return result;
}


std::vector<unsigned char> LZW::decompress(const std::vector<unsigned char>& data) {

    std::vector<uint8_t> bits;
    for (auto byte : data) {
        for (int i = 0; i < 8; i++) {
            unsigned char bit = ( 1 & (byte >> (7 - i)) ) ? 1 : 0;
            bits.push_back(bit);
        }
    }

    std::vector<int> data2;
    for (int i = 0; i < bits.size(); i += bit_resolution_) {
        int temp = 0;
        for (int j = 0; j < bit_resolution_; j++) {
            temp |= bits[i+j] << (bit_resolution_ - 1 - j);
        }
        data2.push_back(temp);
    }

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
    if (dict.find(code) != dict.end()) {
      entry = dict[code];
    }
    else {
      entry = temp + temp[0];
    }

    result += entry;
    dict[dict_size] = temp + entry[0];
    dict_size++;
    temp = entry;

    data_it++;
  }

  return result;
}