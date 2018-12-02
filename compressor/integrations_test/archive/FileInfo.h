//
// Created by Howle on 12/11/2018.
//

#ifndef ARCH_FILEINFO_H
#define ARCH_FILEINFO_H
#include <iostream>
#include <cstring>
using std::copy;

class File_Header{
public:
    File_Header(): size(0), amount(0), settings(0) {

    }
    unsigned long size;
    unsigned long amount;
    unsigned long settings;

    void AddSize(int size);
    void AddFile();
    void SubtractSize(int size);
    void SubtractFile();
    bool IsAmountFull();
};
//class Side_Header{
//public:
//    Side_Header();
//    unsigned long int size;
//    unsigned long int pathSize;
//};

class FileInfo{
public:
    FileInfo();
    FileInfo(std::string &inpath, int &file_size);
    FileInfo(std::string inpath, int file_size);
    void AddPath(std::string &inpath);
    void AddPath(char* str);
    void AddSizeFile(int size);
    void PlusSizeFile(int size);
    void SubstractSizeFile(int size);
    bool IsFileFull();
    bool IsPathFull();
    unsigned long FileSize();
    unsigned long PathSize();
    std::string StrPath();
    char* Path();

private:
    std::string path; // Кинь сюда путь твоего файла через методы или инициализацию
    unsigned long file_size;   // Реализован выше
};

#endif //ARCH_FILEINFO_H
