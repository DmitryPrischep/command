//
// Created by Howle on 04/12/2018.
//

#ifndef COMMAND_WRITE_LINER_H
#define COMMAND_WRITE_LINER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include <fstream>
#include "FileInfo.h"

using std::ofstream;
using std::ifstream;
using std::vector;

class Write_Liner{
public:
    Write_Liner();
    bool BeginWrite();
    // ostream
    bool Write_File(std::ostream& File, vector<char>* array);   // Пишет в конец файла
    bool Write_File(std::ostream& File, vector<char>* array, unsigned long len_stream);   // Пишет в конец файла
    bool TakeHeader(FileInfo file_header);  // запихивает подаваемы хэдер в массив header
    void TakeFileOut(std::string &file);   // устанавливает out_file значением входного файла. Задаем вывод для класса
    void TakeFileOut(std::ostream& out);
    bool HaveOutFile();
    bool TakeBody(vector<char>* array, char mode); // передаем массив в write. По умолчанию сразу пишет и смотрит был ли задан хэдер. Если был, то пишет сначала его
    bool Take_Dictionary(vector<char>* array); // На вход ожидает словарь от Компрессора. Сохраняет его в dictionary
    // !!! На отработну завершения проги + надо добавить в хэдер смещение от конца файла
    bool EndWriting();

//    bool TakeBody(vector<char>* array, char mode);
    bool Write(vector<char>* array, unsigned long len_stream, char mode);
    bool Write_File(std::ostream& File, vector<char>* array, unsigned long len_stream, char mode);
protected:
    std::vector<char> header;
    std::vector<char> dictionary;
    File_Header Main_header;
    FileInfo file_info;

    std::filebuf Initial_file;
    std::ostream out_file;
    // Флаги на запись
    bool state_header_was_wrote = false; // Показывает распарсен ли уже header
    bool state_body_was_wrote = false; //  Показывает была ли запись body.
    bool state_have_out_file = false; // Для проверки есть ли выходной поток
    bool state_have_dictionary = false;  // был ли передан словарь?

    virtual bool Write(vector<char>* array, unsigned long len_stream);    // Реализуется потомками, но задан по умолчанию трубой без буфера прям в файл.
    bool Insert_Header();
};


#endif //COMMAND_WRITE_LINER_H
