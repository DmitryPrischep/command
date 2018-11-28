#ifndef AES_H
#define AES_H
#include <vector>
#include <key.h>

typedef unsigned char byte;
typedef std::vector<std::vector<byte>> ByteArray;

class AES final
{
public:
    AES();
    AES(const int sizeKey);
    ~AES();
    unsigned char xor_byte(byte first, byte second);
    void xor_byte_block(ByteArray& block, ByteArray key);
    byte sub_byte(byte value, bool direction);
    void sub_bytes(ByteArray& block, bool direction);
    void shift_rows(ByteArray& block, bool direction);
    void mix_columns(ByteArray& block, bool direction);
    byte mul_galois(byte a, byte b);

    static byte get_s_element(size_t x, size_t y, bool direction);
    static byte get_c_element(size_t x, size_t y, bool direction);
    static byte get_r_gon(size_t x, size_t y);

private:
    void init_s_box();
    void init_inv_s_box();
    void init_r_con();
    void init_c_box();
    void init_inv_c_box();
    Key key;

    static const int count_round = 10;
    static const int length_word = 4;
    static const int count_word = 4;
    static const ByteArray s_box;
    static const ByteArray inv_s_box;
    static const ByteArray c_box;
    static const ByteArray inv_c_box;
    static const ByteArray r_con;
};

#endif // AES_H
