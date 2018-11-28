#include "key.h"
#include <aes.h>

Key::Key(const std::string pass, const size_t key_size, size_t nb, size_t nk, size_t nr):
    key_size(key_size),
    length_word(nb),
    count_word(nk),
    count_round(nr)
{
    set_key(pass, 16);
}

void Key::set_key(std::string pass_string, size_t key_size = 16)
{
    std::vector<byte> password(key_size);
    for(size_t i = 0; i < key_size; i++){
        if(i < key_size)
            password[i] = pass_string[i];
        else
            password[i] = 0;
    }
    data_key = get_encrypt_key(password);
}

ByteArray Key::get_matrix_key(size_t index)
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

std::vector<byte> Key::shift_word(const std::vector<byte>& word)
{
    std::vector<byte> result(length_word);
    result[0] = word[length_word - 1];
    for (size_t i = 1; i < length_word; i++){
        result[i] = word[i - 1];
    }
    return result;
}

std::vector<byte> Key::sub_word(const std::vector<byte>& word)
{
    std::vector<byte> result(length_word);
    for (size_t i = 0; i < length_word; i++){
        byte indexX = word[i] % 16;
        byte indexY = word[i] / 16;
        byte tempByte = get_s_element(indexX, indexY, true);
    }
    return result;
}

ByteArray Key::get_encrypt_key(std::vector<byte> pass)
{
    ByteArray words(count_word * (count_round + 1));
    for ( size_t i = 0; i < count_word; i++){
        words[i].reserve(length_word);
        for(size_t j = 0; j < length_word; j++){
            words[i][j] = pass[i * count_word + j];
        }
    }

    for (size_t i = count_word; i < (count_word * (count_round + 1)); i++){
        std::vector<byte> word = words[i - 1];
        if(i % count_word == 0){
            word = sub_word(shift_word(word));
            for (size_t j = 0; j < length_word; j++){
                word[j] = AES::xorByte(word[j], get_r_con(j, i / count_word));
            }
        } else {
            word = sub_word(word);
        }
        for (size_t k = 0; k < length_word; k++)
            word[k] =AES::xorByte(words[i - count_word][k], word[k]);
        words[i] = word;
    }
    return words;
}
