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
    unsigned char xorByte(byte first, byte second);
    void xorByteBlock(ByteArray &block, ByteArray key);
    byte subByte(byte value, bool direction);
    void subBytes(ByteArray &block, bool direction);
    void shiftRows(ByteArray& block, bool direction);
    void mixColumns(ByteArray& block, bool direction);
    byte mulGalois(byte a, byte b);

private:
    void initSBox();
    void initInvSBox();
    void initRcon();

    static const int countRound = 10;
    static const int lengthWord = 4;
    static const int countWord = 4;

    Key key;
    ByteArray sBox;
    ByteArray invsBox;
    ByteArray rcon;
};

#endif // AES_H
