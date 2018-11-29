#ifndef KEY_H
#define KEY_H
#include <vector>
#include <string>

typedef unsigned char byte;
typedef std::vector<std::vector<byte>> ByteArray;

//To add 5 rules
class Key final
{
public:
    Key();
    Key(const std::string& pass, const size_t key_size, size_t nb, size_t nk, size_t nr);
    void set_key(const std::string& pass_string, size_t key_size);
    ByteArray get_matrix_key(size_t index);

private:
    std::vector<byte> shift_word(const std::vector<byte> word);
    std::vector<byte> sub_word(const std::vector<byte> word);
    ByteArray get_encrypt_key(std::vector<byte> pass);

    ByteArray data_key;
    const size_t key_size;
    const size_t length_word; //count_columns
    const size_t count_word;
    const size_t count_round;
};


#endif // KEY_H
