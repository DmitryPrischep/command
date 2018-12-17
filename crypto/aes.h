#ifndef AES_H
#define AES_H
#include <vector>
#include "key.h"

class IKey
{
public:
    IKey() {}
    virtual ~IKey(){}
    size_t lenght_word;
    size_t count_word;
    size_t count_rounds;
};

class ICrypto
{
public:
    ICrypto() {}
    virtual ~ICrypto(){}
    virtual const std::vector<byte_t> encrypt(const std::vector<byte_t>& buffer) = 0;
    virtual const std::vector<byte_t> decrypt(const std::vector<byte_t>& buffer) = 0;
};

//AES 128 default
class AES final : public ICrypto{
public:
    AES(const Key* key);
    AES(const AES& algorithm) = delete;
    AES(const AES&& algorithm) = delete;
    AES& operator =(const AES& algorithm) = delete;
    AES& operator =(const AES&& algorithm) = delete;
    ~AES() = default;

    const std::vector<byte_t> encrypt(const std::vector<byte_t>& buffer);
    const std::vector<byte_t> decrypt(const std::vector<byte_t>& buffer);

    static byte_t xor_byte(byte_t first, byte_t second);
    static byte_t get_s_element(size_t x, size_t y, bool direction);
    static byte_t get_c_element(size_t x, size_t y, bool direction);
    static byte_t get_r_con(size_t x, size_t y);

private:
    void encrypt_block(ByteArray& block);
    void decrypt_block(ByteArray& block);

    void sub_bytes(ByteArray& block, bool direction);
    void shift_rows(ByteArray& block, bool direction);
    void mix_columns(ByteArray& block, bool direction);
    byte_t mul_galois(byte_t a, byte_t b);

    void xor_byte_block(ByteArray& block, ByteArray key);
    byte_t sub_byte(byte_t value, bool direction);

    const Key* key;

    static const ByteArray s_box;
    static const ByteArray inv_s_box;
    static const ByteArray c_box;
    static const ByteArray inv_c_box;
    static const ByteArray r_con;
    const size_t count_round;
    const size_t length_word;
    const size_t count_word;
};

#endif // AES_H
