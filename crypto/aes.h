#ifndef AES_H
#define AES_H
#include <vector>
#include <key.h>

typedef unsigned char byte;
typedef std::vector<std::vector<byte>> ByteArray;


typedef std::vector<std::vector<unsigned char>> ByteArray;
typedef unsigned char byte;

class ICrypto
{
public:
    ICrypto() {}
    virtual ~ICrypto(){}
    virtual const std::vector<byte> encrypt(const std::vector<byte>& buffer) = 0;
    virtual const std::vector<byte> decrypt(const std::vector<byte>& buffer) = 0;
    virtual const std::vector<byte> generate_key(const std::string password) = 0;
};

//AES 128 default
class AES final : ICrypto{
public:
//    AESEncryptor(size_t key_length) : key(GenerateKey(key_length)) {}
    AES(const size_t size_key, const std::string& pass, const short nk, const short nr);
    AES(const AES& algorithm) = delete;
    AES(const AES&& algorithm) = delete;
    AES& operator =(const AES& algorithm) = delete;
    AES& operator =(const AES&& algorithm) = delete;
    ~AES();

    const std::vector<byte> encrypt(const std::vector<byte>& buffer);
    const std::vector<byte> decrypt(const std::vector<byte>& buffer);
    const std::vector<byte> generate_key(const size_t size_key, const std::string password);

    static unsigned char xor_byte(byte first, byte second);
    static byte get_s_element(size_t x, size_t y, bool direction);
    static byte get_c_element(size_t x, size_t y, bool direction);
    static byte get_r_con(size_t x, size_t y);

private:
    void encrypt_block(ByteArray& block);
    void decrypt_block(ByteArray& block);

    void sub_bytes(ByteArray& block, bool direction);
    void shift_rows(ByteArray& block, bool direction);
    void mix_columns(ByteArray& block, bool direction);
    byte mul_galois(byte a, byte b);

    void xor_byte_block(ByteArray& block, ByteArray key);
    byte sub_byte(byte value, bool direction);

    Key* key;

    static const ByteArray s_box;
    static const ByteArray inv_s_box;
    static const ByteArray c_box;
    static const ByteArray inv_c_box;
    static const ByteArray r_con;

    //128-bit settings
    const int count_round = 10;
    const int length_word = 4;
    const int count_word = 4;
};

#endif // AES_H
