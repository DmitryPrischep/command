#ifndef KEY_H
#define KEY_H
#include <vector>
#include <string>

class Key final
{
public:
    Key();
    void setKey(std::string filePath);
    unsigned char** getMatrixKey(int index);

private:
    /*unsigned char**/ void shiftWord(const std::vector<unsigned char>& word);
    /*unsigned char**/ void subWord(const std::vector<unsigned char>& word);
    unsigned char** getEncryptKey(std::vector<unsigned char> key);

    static unsigned char** key;

};

#endif // KEY_H
