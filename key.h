#ifndef KEY_H
#define KEY_H
#include <vector>
#include <string>

typedef unsigned char byte;
typedef std::vector<std::vector<byte>> ByteArray;

namespace AES128 {
    const unsigned short count_word = 4;
    const unsigned short count_round = 10;
}

namespace AES192 {
    const unsigned short count_word = 6;
    const unsigned short count_round = 12;
}

namespace AES256 {
    const unsigned short count_word = 8;
    const unsigned short count_round = 14;
}

// default 128 bit
class Key final
{
public:
    Key(const std::string& pass, const size_t key_size);
    Key(const Key& key) = delete;
    Key(const Key&& key) = delete;
    Key& operator =(const Key& key) = delete;
    Key& operator =(const Key&& key) = delete;
    ~Key() = default;

    ByteArray get_matrix_key(size_t index) const;
    size_t get_count_word() const {return this->count_word;}
    size_t get_length_word() const {return this->length_word;}
    size_t get_count_round() const {return this->count_round;}

private:
    bool check_key(const size_t key);
    std::vector<byte> shift_word(const std::vector<byte> word);
    std::vector<byte> sub_word(const std::vector<byte> word);
    ByteArray get_encrypt_key(std::vector<byte> pass);

    ByteArray data_key;
    const size_t key_size;
    size_t length_word; //count_columns
    size_t count_word;
    size_t count_round;
};


#endif // KEY_H
