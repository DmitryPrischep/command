//
// Created by Howle on 12/11/2018.
//

#ifndef ARCH_FILEINFO_H
#define ARCH_FILEINFO_H
#include <iostream>

using std::copy;


class File_Header{
public:
    File_Header(): size(0), amount(0), settings(0) {

    }

    unsigned long int size;
    unsigned long int amount;
    unsigned int settings;

    void AddSize(int size);
    void AddFile();
    void SubtractSize(int size);
    void SubtractFile();
    bool IsAmountFull();
};
class Side_Header{
public:
    Side_Header();
    unsigned long int size;
    unsigned long int pathSize;
};

class FileInfo{
public:
    FileInfo();
//    FileInfo(FileInfo& current);
    FileInfo(char* inpath, int file_size);
    ~FileInfo();
    void AddPath(char* inpath);
    void AddSizeFile(int size);
    void PlusSizeFile(int size);
    void SubstractSizeFile(int size);
    bool IsFileFull();
    bool IsFull();
    int Size();
    int Length();
    int PathLength();
    char* Path();

    Side_Header* GiveHeader();
    char** GivePath();
private:
    char* path; // Кинь сюда путь твоего файла через методы или инициализацию
    Side_Header file;   // Реализован выше

    void TakePathLength();
};
// Пример использования
/*
      char path[5] = "123";
      FileInfo a(path, 1024);
//    FileInfo a;
//    a.AddPath(path);
//    a.AddSizeFile(1024);
      cout << a.IsFull() << " " << a.Path() << " " << a.Length().pathSize.pathSize_int << " " << a.Length().size.size_int << endl;
 */


//#include "FileInfo.cpp"
#endif //ARCH_FILEINFO_H
