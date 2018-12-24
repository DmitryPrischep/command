#include "key.h"
#include "aes.h"

Key::Key(const std::string& pass_string, const size_t key_size):
    length_word(4),
    key_size(key_size)
{
    check_key(key_size);
    std::vector<byte> password(key_size/8);
    for(size_t i = 0; i < key_size/8; i++){
        if(i < pass_string.size())
            password[i] = pass_string[i];
        else
            password[i] = '&';
    }
    data_key = get_encrypt_key(password);
}

byte AES::get_r_con(size_t x, size_t y)
{
    return r_con[x][y];
}

ByteArray Key::get_matrix_key(size_t index) const
{
    index *= 4;
    ByteArray result(4);
    for (size_t i = 0; i < 4; i++){
        result[i].resize(4);
        for (size_t j = 0; j < 4; j++){
            result[i][j] = data_key[index + i][j];
        }
    }
    return result;
}

std::vector<byte> Key::shift_word(const std::vector<byte> word)
{
    std::vector<byte> result(length_word);
    result[0] = word[length_word - 1];
    for (size_t i = 1; i < length_word; i++){
        result[i] = word[i - 1];
    }
    return result;
}

std::vector<byte> Key::sub_word(const std::vector<byte> word)
{
    std::vector<byte> result(length_word);
    for (size_t i = 0; i < length_word; i++){
        byte x = word[i] % 16;
        byte y = word[i] / 16;
        byte temp = AES::get_s_element(x, y, true);
        result[i] = temp;
    }
    return result;
}

ByteArray Key::get_encrypt_key(std::vector<byte> pass)
{
    ByteArray words(count_word * (count_round + 1));
    for ( size_t i = 0; i < count_word; i++){
        words[i].resize(length_word);
        for(size_t j = 0; j < length_word; j++){
            words[i][j] = pass[i * count_word + j];
        }
    }

    for (size_t i = count_word; i < (count_word * (count_round + 1)); i++){
        std::vector<byte> word = words[i - 1];
        if(i % count_word == 0){
            word = sub_word(shift_word(word));
            for (size_t j = 0; j < length_word; j++){
                word[j] = AES::xor_byte(word[j], AES::get_r_con(j, i / count_word));
            }
        } else {
            word = sub_word(word);
        }
        for (size_t k = 0; k < length_word; k++)
            word[k] =AES::xor_byte(words[i - count_word][k], word[k]);
        words[i] = word;
    }
    return words;
}

bool Key::check_key(const size_t key)
{
    switch (key) {
        case 128: {
            this->count_word = AES128::count_word;
            this->count_round = AES128::count_round;
            return true;
        }
        case 192: {
            this->count_word = AES192::count_word;
            this->count_round = AES192::count_round;
            return true;
        }
        case 256: {
            this->count_word = AES256::count_word;
            this->count_round = AES256::count_round;
            return true;
        }
        default: {
            throw "Password lenght is incorrect: only 128\\192\\256 keylength avaible";
            return false;
        }
    }
}
