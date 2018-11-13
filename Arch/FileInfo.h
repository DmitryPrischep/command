//
// Created by Howle on 12/11/2018.
//

#ifndef ARCH_FILEINFO_H
#define ARCH_FILEINFO_H

#include "Union.h"
class FileInfo{
public:
    FileInfo();
    FileInfo(char* inpath, int file_size);
//    ~FileInfo();
    void AddPath(char* inpath);
    void AddSizeFile(int size);
    bool IsFull();
    Side_Header Length();
    char* Path();
private:
    char* path; // Кинь сюда путь твоего файла через методы или инициализыцию
    Side_Header file;   // Реализован в Union.h
    // Сделан на union тк надо будет читать в бинарный файл
    void TakePathLength();
};

#endif //ARCH_FILEINFO_H
