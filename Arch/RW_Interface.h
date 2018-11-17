//
// Created by Howle on 12/11/2018.
//

#ifndef ARCH_RW_INTERFACE_H
#define ARCH_RW_INTERFACE_H
#include "FileInfo.h"
#include <iostream>
#include <vector>
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::vector;
class RW_Interface{
public:
    // Настрой Bool !!!
    bool TakeHeader(FileInfo file_header);
    void TakeFileOut(ofstream& file);
    bool TakeBody(vector<char>& array);
    virtual bool Write(vector<char>& array);
    bool Write_File(ofstream& File, vector<char>& array);
    bool Insert_Header(ofstream& File);
    bool HaveOutFile();

    bool TakeFileIn(ifstream& file);
    bool HaveInFile();
    virtual bool Read();
    bool ReadHeader();  // Считать заголовок всего документа
    bool ReadFileHead();    // Считать заголовок 1 файла


protected:
    vector<char> header;
    vector<char> bufer;
    File_Header Main_header;
    FileInfo file_info;
    ofstream* out_file;
    ifstream* in_file; // not use yet
    int file_amoun = 0;  // Считает сколько раз мы считали header & bufer
    bool state_header_was_wrote = false; // Показывает распарсен ли уже header
    bool state_body_was_wrote = false; //  Показывает была ли запись body.
    bool state_have_out_file = false; // Для проверки есть ли выходной поток
    bool state_have_in_file = false; // -\\- входной поток

};


#endif //ARCH_RW_INTERFACE_H
