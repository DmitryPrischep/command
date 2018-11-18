#ifndef AES_H
#define AES_H
#include <vector>

class AES final
{
public:
    AES();
    AES(const int sizeKey);
    ~AES();
    unsigned char xorByte(unsigned char first, unsigned char second);
    void xorByteBlock(unsigned char*** block, unsigned char** key);
    unsigned char subByte(unsigned char byte, bool systemStatus);
    void subBytes(unsigned char*** block, bool systemStatus);
    void shiftRows(unsigned char*** block, bool type);
    void mixColumns(unsigned char*** block, bool type);
    unsigned char mulGalois(unsigned char a, unsigned char b);

private:
    void initSBox();
    void initInvSBox();
    void initRcon();

    static const int countRound = 10;
    static const int lengthWord = 4;
    static const int countWord = 4;

    const unsigned char* sBox;
    const unsigned char* invsBox;
    const unsigned char** rcon[];

};

#endif // AES_H
