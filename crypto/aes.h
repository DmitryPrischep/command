#ifndef AES_H
#define AES_H
#include <vector>
#include <key.h>

typedef unsigned char byte;
typedef std::vector<std::vector<byte>> ByteArray;

//To add 5 rules

class AES final
{
public:
    AES(const size_t size_key, const std::string& pass);
    ~AES();
    static unsigned char xor_byte(byte first, byte second);
    void xor_byte_block(ByteArray& block, ByteArray key);
    byte sub_byte(byte value, bool direction);
    void sub_bytes(ByteArray& block, bool direction);
    void shift_rows(ByteArray& block, bool direction);
    void mix_columns(ByteArray& block, bool direction);
    byte mul_galois(byte a, byte b);

    static byte get_s_element(size_t x, size_t y, bool direction);
    static byte get_c_element(size_t x, size_t y, bool direction);
    static byte get_r_con(size_t x, size_t y);

private:
    Key* key;

    static const ByteArray s_box;
    static const ByteArray inv_s_box;
    static const ByteArray c_box;
    static const ByteArray inv_c_box;
    static const ByteArray r_con;

    const int count_round = 10;
    const int length_word = 4;
    const int count_word = 4;
};

#endif // AES_H
