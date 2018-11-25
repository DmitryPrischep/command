#include "LZW.hpp"
#include <map>
#include <cmath>

void LZW::encode(const std::string& data, std::back_insert_iterator<std::vector<int>> result, int dictionary_size) {

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

std::string LZW::decode(std::vector<int>::iterator begin, std::vector<int>::iterator end, int dictionary_size) {

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

std::vector<unsigned char> LZW::compress(std::vector<unsigned char> data) {
  std::string str_data(data.begin(), data.end());
  std::vector<int> encoded;
  int dict_size = dictionary_size_;
  encode(str_data, std::back_inserter(encoded), dict_size);

  std::vector<unsigned char> result(encoded.begin(), encoded.end());
  //for (int i = 0; i < encoded.size(); i++) {
  //  result[i] = static_cast<unsigned char>(encoded[i]);
  //}

  return result;
}


std::vector<unsigned char> LZW::decompress(std::vector<unsigned char> data) {

  std::veсtor<int> int_data(data.begin(), data.end());

  int dict_size = dictionary_size_; 
  std::string decoded = decode(int_data.begin(), int_data.end(), dict_size);

  std::vector<unsigned char> result(decoded.begin(), decoded.end());
  return result;
}