//
// Created by Howle on 12/11/2018.
//

#ifndef ARCH_FILEINFO_H
#define ARCH_FILEINFO_H
#include "Union.h"
#include <iostream>

using std::copy;

class FileInfo{
public:
    FileInfo();
    FileInfo(const char* inpath, int file_size);
    ~FileInfo();
    void AddPath(char* inpath);
    void AddSizeFile(int size);
    bool IsFull();
    Side_Header Length();
    int PathLength();
    char* Path();

    Side_Header* GiveHeader();
    char** GivePath();
private:
    char* path; // Кинь сюда путь твоего файла через методы или инициализыцию
    Side_Header file;   // Реализован в Union.h
    // Сделан на union тк надо будет читать в бинарный файл
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
