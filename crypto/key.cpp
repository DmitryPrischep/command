#include "key.h"
#include <aes.h>

Key::Key()
{

}

void Key::setKey(std::string filePath)
{

}

ByteArray Key::getMatrixKey(size_t index)
{

}

std::vector<byte> Key::shiftWord(const std::vector<byte> &word)
{
    int lengthWord = AES::lengthWord;
    std::vector<byte> result(lengthWord);
    result[0] = word[lengthWord - 1];
    for (size_t i = 1; i < lengthWord; i++){
        result[i] = word[i - 1];
    }
    return result;
}

void Key::subWord(const std::vector<byte> &word)
{
    size_t lengthWord = AES::lengthWord;
    std::vector<byte> result(lengthWord);
    for (size_t i = 0; i < lengthWord; i++){
        byte indexX = word[i] % 16;
        byte indexY = word[i] / 16;
        byte tempByte = getSElement(indexX, indexY, true);
    }
    return result;
}

ByteArray Key::getEncryptKey(std::vector<byte> key)
{

}
