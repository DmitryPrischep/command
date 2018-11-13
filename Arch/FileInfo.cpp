//
// Created by Howle on 12/11/2018.
//

#include "FileInfo.h"

/* Класс используется для передачи хэдера от компрессора  */

FileInfo::FileInfo(): path(""){

    file.pathSize.pathSize_int = 0;
}
FileInfo::FileInfo(char* inpath, int file_size) : path(inpath){
    file.size.size_int = file_size;
    file.pathSize.pathSize_int = 0;
    TakePathLength();
}
//FileInfo::~FileInfo() {}
void FileInfo::AddPath(char* inpath){
    path = inpath;
    TakePathLength();
}
void FileInfo::AddSizeFile(int size){
    file.size.size_int = size;
}
bool FileInfo::IsFull(){  // Возвращет 1 если все поля заполненны
    return ((path != "" && file.size.size_int != 0) ? true : false );
}
Side_Header FileInfo::Length(){
    return file;
}
char* FileInfo::Path(){
    return path;
}
void FileInfo::TakePathLength(){
    file.pathSize.pathSize_int = sizeof(path);
}
