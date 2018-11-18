//
// Created by Howle on 12/11/2018.
//
#include "FileInfo.h"

/* Класс используется для передачи хэдера от компрессора  */

FileInfo::FileInfo() {
    path = new char(1);
    file.pathSize = 0;
}
FileInfo::FileInfo(const char* inpath, int file_size){
    file.size = file_size;
    path = new char(sizeof(inpath)); // ///////////////////////
    copy(inpath, inpath + sizeof(inpath), path);
    file.pathSize = 0;
    TakePathLength();
}
//FileInfo::~FileInfo() {}
void FileInfo::AddPath(char* inpath){
    path = inpath;
    TakePathLength();
}
void FileInfo::AddSizeFile(int size){
    file.size = size;
}
bool FileInfo::IsFull(){  // Возвращет 1 если все поля заполненны
    return path != "" && file.size != 0;
}
Side_Header FileInfo::Length(){
    return file;
}
char* FileInfo::Path(){
    return path;
}
void FileInfo::TakePathLength(){
    file.pathSize = sizeof(path);
}
int FileInfo::PathLength() {
    return sizeof(path);
}
FileInfo::~FileInfo() {

}

Side_Header *FileInfo::GiveHeader() {
    Side_Header* tmp = &file;
    return tmp;
}

char **FileInfo::GivePath() {
    char ** tmp = &path;
    return tmp;
}
