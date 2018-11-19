#ifndef KEY_H
#define KEY_H
#include <vector>
#include <string>

typedef unsigned char byte;
typedef std::vector<std::vector<byte>> ByteArray;

class Key final
{
public:
    Key();
    void setKey(std::string filePath);
    ByteArray getMatrixKey(size_t index);

private:
    void shiftWord(const std::vector<byte>& word);
    void subWord(const std::vector<byte>& word);
    ByteArray getEncryptKey(std::vector<byte> key);

    static ByteArray dataKey;
//    static const int countRound = 10;
//    static const int lengthWord = 4;
//    static const int countWord = 4;
};

#endif // KEY_H
