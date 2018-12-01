//
// Created by Howle on 12/11/2018.
//
#include "FileInfo.h"

/* Класс используется для передачи хэдера от компрессора  */

FileInfo::FileInfo(std::string &inpath, int &file_size) {
    path = inpath;
    file_size = static_cast<unsigned long>(file_size);
}

FileInfo::FileInfo(std::string inpath, int file_size) {
    path = inpath;
    file_size = static_cast<unsigned long>(file_size);
}

void FileInfo::AddPath(std::string &inpath) {
    path = inpath;
}

void FileInfo::AddSizeFile(int size) {
    file_size = static_cast<unsigned long>(size);
}

void FileInfo::PlusSizeFile(int size) {
    file_size += size;
}

void FileInfo::SubstractSizeFile(int size) {
    file_size -= size;
}

bool FileInfo::IsFileFull() {
    return file_size > 0 ? true : false;
}

bool FileInfo::IsPathFull() {
    return path.size() > 0 ? true : false;
}

unsigned long FileInfo::FileSize() {
    return file_size;
}

unsigned long FileInfo::PathSize() {
    return path.size();
}

char *FileInfo::Path() {
    char* tmp = new char(path.size()); //Круглые скобки? (Это работает на божьей силе);
    strcpy(tmp, path.c_str());
    return tmp;
}

FileInfo::FileInfo() : path(""), file_size(0) {}

void FileInfo::AddPath(char *str) {
    std::string tmp(str);
    path = tmp;
}

void File_Header::AddSize(int size) {
    this->size += size;
}

void File_Header::AddFile() {
    amount++;
}

void File_Header::SubtractSize(int size) {
    this->size -= size;
}

void File_Header::SubtractFile() {
    amount--;
}

bool File_Header::IsAmountFull() {
    return amount > 0 ? true : false;
}
