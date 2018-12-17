#include "Huffman.hpp"
#include <queue>
#include <iterator>
#include <limits>

Huffman::Huffman() : empty_bits_(0) {
   dict_size_ = std::numeric_limits<unsigned char>::max() + 1;
}

std::vector<char> Huffman::compress(const std::vector<char>& data) noexcept { 
    std::vector<char> encoded = encode(data); 
    std::vector<char> compressed = make_bytes(encoded);

    // записываем словарь в начало сжатых данных
    std::vector<char> dict = save_dict();
    std::vector<char> result;
    std::copy(dict.begin(), dict.end(), std::back_inserter(result));
    std::copy(compressed.begin(), compressed.end(), std::back_inserter(result));
    haf_dict_.clear();

    return result;
}


std::vector<char> Huffman::decompress(const std::vector<char>& data) noexcept {
    int pos = recover_dict(data);
    std::vector<char> compressed(data.begin() + pos, data.end());
    std::vector<char> encoded = make_bits(compressed);
    encoded.resize(encoded.size() - empty_bits_);
    std::string encoded_str(encoded.begin(), encoded.end());
    std::vector<char> result = decode(encoded_str);
    rev_haf_dict_.clear();
    return result;
}

std::vector<char> Huffman::encode(const std::vector<char>& data) noexcept {
    char left = 0;
    char right = 1;

    // считаем частоту повотрения для каждого символа
    std::map<std::string, int> haf_freq;
    for (auto byte : data) {
        std::string str(1, byte);
        if (haf_freq.find(str) != haf_freq.end()) {
            haf_freq[str]++;
        }
        else {
            haf_freq[str] = 1; 
        }
    }

    // кладем узлы в очередь с приоритетом
    auto cmp = [] ( std::pair<std::string, int> A, std::pair<std::string, int> B) { return A.second > B.second; };
    std::priority_queue <std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(cmp)> q(cmp);
    for ( auto byte : haf_freq ) {
        q.push(byte);    
    }

    // заполняем словарь Хаффмана  
    if ( haf_freq.size() == 1) {
        haf_dict_[data[0]] = left;
    } 
    else {  
        while (q.size() > 1) {
            auto qq1 = q.top();
            q.pop();
            auto qq2 = q.top();
            q.pop();
            
            for ( auto byte : qq1.first ) {
                haf_dict_[byte] = left + haf_dict_[byte];
            }           
            for ( auto byte : qq2.first ) {
                haf_dict_[byte] = right + haf_dict_[byte];
            }   
            
            qq2.first  = qq1.first  + qq2.first;
            qq2.second = qq1.second + qq2.second;
            q.push(qq2);
        }
    }

    std::vector<char> result;
    for (auto symbol : data) {
        std::string code = haf_dict_[symbol];
        std::copy(code.begin(), code.end(), std::back_inserter(result));
    }

    return result;  
}

std::vector<char> Huffman::decode(const std::string& data) noexcept {
    std::string result_str;
    int pos = 0;
    while ( pos < data.size() ) {
        int ofset = 1;
        while (true) {
            std::string temp = data.substr(pos, ofset);
            if (rev_haf_dict_.find(temp) != rev_haf_dict_.end()) {
                pos += temp.size();
                result_str += rev_haf_dict_[temp];
                break;
            }
            else {
                ofset++;
            }
        }
    }
    std::vector<char> result(result_str.begin(), result_str.end());
    return result;
}

std::vector<char> Huffman::make_bytes(std::vector<char>& data) noexcept {
    std::vector<char> result;
    empty_bits_ = 0;
    while (data.size() % 8 != 0) {
        data.push_back(0);
        empty_bits_++;
    }
    for (int i = 0; i < data.size(); i+=8) {
        char temp = 0;
        for (int j = 0; j < 8; j++) {
            temp |= data[i+j] << (7 - j);
        }        
        result.push_back(temp);
    }
    return result;
}

std::vector<char> Huffman::make_bits(const std::vector<char>& data) noexcept {
    std::vector<char> result;
    for (auto byte : data) {
        for (int i = 0; i < 8; i++) {
            char bit = ( 1 & (byte >> (7 - i)) ) ? 1 : 0;
            result.push_back(bit);
        }
    }
    return result;
}


std::vector<char> Huffman::save_dict() noexcept {
    /*
    1 байт - кол-во пустых битов
    256 байт - число бит на каждый символ
    дальше коды символов слепленные в байты
    */

    std::vector<char> result;    
    result.push_back(empty_bits_);
    for(int i = 0; i < dict_size_; i++) {
        char symbol = (char) i;
        char code_size = 0;
        if (haf_dict_.find(symbol) != haf_dict_.end()) {
            code_size = (char) haf_dict_[symbol].size();  
        }
        result.push_back(code_size);
    } 
    std::vector<char> bits;
    for (int i = 0; i < dict_size_; i++) {
        char symbol = (char) i;
        std::string code = haf_dict_[symbol];
        std::vector<char> temp(code.begin(), code.end());
        std::copy(temp.begin(), temp.end(), std::back_inserter(bits));
    }
    std::vector<char> bytes = make_bytes(bits);
    std::copy(bytes.begin(), bytes.end(), std::back_inserter(result));
    return result;
}


int Huffman::recover_dict(const std::vector<char>& data) noexcept {
    /*
    1 байт - кол-во записей в словаре (N)
    N*(1 байт - символ + 1 байт - кол-во бит в коде символа)
    дальше коды символов слепленные в байты
    */
    empty_bits_ = data[0];
    int ofset = 1;

    int codes_size = 0;
    for (int i = ofset; i < dict_size_ + ofset; i++) {
        char code_size = data[i];      
        codes_size += code_size;
    } 
    int byte_codes_size = (codes_size % 8 == 0) ? codes_size / 8 : codes_size / 8 + 1;
    std::vector<char> bytes;
    for (int i = dict_size_ + ofset; i < dict_size_ + ofset + byte_codes_size ; i++) {
        bytes.push_back(data[i]);
    }

    std::vector<char> bits = make_bits(bytes);
    int pos = 0;
    for (int i = 0; i < dict_size_; i++) {
        char symbol = (char) i;
        std::string code;
        for (int j = 0; j < data[i+1]; j++) {
            code += bits[pos];
            pos++;
        } 
        rev_haf_dict_[code] = symbol;       
    }

    return dict_size_ + ofset + byte_codes_size ;
}
