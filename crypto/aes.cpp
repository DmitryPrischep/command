#include "aes.h"
#include <vector>
#include <string>



AES::AES()
{

}

AES::AES(const int sizeKey)
{

}

unsigned char AES::xorByte(unsigned char first, unsigned char second)
{

}

void AES::xorByteBlock(unsigned char*** block, unsigned char** key)
{

}

unsigned char AES::subByte(unsigned char byte, bool systemStatus)
{

}

void AES::subBytes(unsigned char*** block, bool systemStatus)
{

}

void AES::shiftRows(unsigned char*** block, bool type)
{

}

void AES::mixColumns(unsigned char*** block, bool type)
{

}

unsigned char AES::mulGalois(unsigned char a, unsigned char b)
{

}

void AES::initSBox()
{

}

void AES::initInvSBox()
{

}

void AES::initRcon()
{

}
