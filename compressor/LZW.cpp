#include "LZW.hpp"
#include <map>
#include <cmath>
#include <iterator>

LZW::LZW() : dictionary_size_(DATA_SIZE) {
    // определяем количество бит под код подстроки из словаря
    // пример, для входной последовательности длиной 256 байт, нужно 9 бит 
    // так как, размер ascii + размер входной строки = 256 + 256 = 512 = 2^9
    int i = 0;
    int dict_power = dictionary_size_ + sizeof(char);
    while ( (dict_power) >> i ) {
        i++;
    }
    bit_resolution_ = i;
}

std::vector<char> LZW::compress(const std::vector<char>& data) {

    std::string str_data(data.begin(), data.end());
    std::vector<int> encoded = encode(str_data);

    // разбиваем кодированную последовательность на биты, это необходимо, тк символы кодируются интами
    std::vector<uint8_t> bits;
    for (auto byte : encoded) {
        for (int i = 16 - bit_resolution_; i < 16; i++) {
            char bit = ( 1 & (byte >> (15 - i)) ) ? 1 : 0;
            bits.push_back(bit);
        }
    }

    // создаём последовательность байт (по 8 бит) из последовательности битов
    std::vector<char> result;
    for (int i = 0; i < bits.size(); i += 8) {
        char temp = 0;
        for (int j = 0; j < 8; j++) {
            temp |= bits[i+j] << (7 - j);
        }
        result.push_back(temp);
    }
    return result;
}


std::vector<char> LZW::decompress(const std::vector<char>& data) {

    // разбиваем входную последовательность на биты
    std::vector<uint8_t> bits;
    for (auto byte : data) {
        for (int i = 0; i < 8; i++) {
            char bit = ( 1 & (byte >> (7 - i)) ) ? 1 : 0;
            bits.push_back(bit);
        }
    }

    // определяем размер кодированной последовательности без избыточных бит
    // избыточные биты - биты, которыми заполнили младшие разряды байта, когда информационные биты закончились
    int real_bits_size = bits.size() / bit_resolution_;
    real_bits_size *= bit_resolution_;

    // собираем из битов, последовательность для декодировки
    std::vector<int> data2;
    for (int i = 0; i < real_bits_size; i += bit_resolution_) {
        int temp = 0;
        for (int j = 0; j < bit_resolution_; j++) {
            temp |= bits[i+j] << (bit_resolution_ - 1 - j);
        }
        data2.push_back(temp);
    }

    std::string decoded = decode(data2);

    std::vector<char> result(decoded.begin(), decoded.end());

    return result;
}

std::vector<int> LZW::encode(const std::string& data) {

    int dict_size = dictionary_size_;  
    std::map<std::string, int> dict;

    std::vector<int> result;
    auto result_iter = std::back_inserter(result);

    // иницилизируем словарь стандартными (ascii) символами
    for (int i = 0; i < dict_size; i++) {
        dict[std::string(1, i)] = i;
    }

    // процесс кодировки
    // если подстрока есть в словаре, вставляем её код
    // если её там нет, то добавляем её в словарь и записываем код
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

    // иницилизируем словарь стандартными (ascii) символами
    for (int i = 0; i < dict_size; i++) {
        dict[i] = std::string(1, i);
    }

    std::string temp(1, *data_it++);
    std::string result = temp;
    std::string entry;

    // ищем в словаре код
    // вставляем соответствующую коду подстроку в декодированную последовательность
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