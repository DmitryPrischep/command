//
// Created by Howle on 12/11/2018.
//

#ifndef ARCH_RW_INTERFACE_H
#define ARCH_RW_INTERFACE_H
#include "FileInfo.h"
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <fstream>

namespace fs = boost::filesystem;
using std::ofstream;
using std::ifstream;
using std::vector;
class RW_Interface{
public:
    ~RW_Interface();

    bool BeginWrite();
    bool Write_File(ofstream& File, vector<char>& array);   // Пишет в конец файла
    bool TakeHeader(FileInfo file_header);  // запихивает подаваемы хэдер в массив header
    void TakeFileOut(std::string &file);   // устанавливает out_file значением входного файла. Задаем вывод для класса
    bool HaveOutFile();
    bool TakeBody(vector<char> array); // передаем массив в write. По умолчанию сразу пишет и смотрит был ли задан хэдер. Если был, то пишет сначала его
    bool Take_Dictionary(vector<char>& array); // На вход ожидает словарь от Компрессора. Сохраняет его в dictionary
    // !!! На отработну завершения проги + надо добавить в хэдер смещение от конца файла
    virtual bool Write(vector<char>& array, int len_stream);    // Реализуется потомками, но задан по умолчанию трубой без буфера прям в файл.
    bool EndWriting();


    bool TakeFileIn(std::string &file);
    bool HaveInFile();
    bool ReadHeader();  // Считать заголовок всего документа
    bool ReadFileHead();    // Считать заголовок 1 файла в file_info
    vector<char> ReadBodyPath();    // Будет прыгать по файлу и читать кусочек файла. Далее передать в Разжатие, а после в FileRecoveryWrite
//    bool EndReading();

    bool RecoveryWrite(vector<char>& input);
    bool RecoveryPathDir(std::string path);  // Во



    File_Header* File_header();
    FileInfo* File_info();
protected:
    vector<char> header;
    vector<char> dictionary;
    File_Header Main_header;
    FileInfo file_info;
    ofstream out_file;
    ifstream in_file;
    const int pieceInfo = 1024*4;
    int file_amoun = 0;  // Считает сколько раз мы считали header & bufer   // Он вообще нужен??
    // Флаги на запись
    bool state_header_was_wrote = false; // Показывает распарсен ли уже header
    bool state_body_was_wrote = false; //  Показывает была ли запись body.
    bool state_have_out_file = false; // Для проверки есть ли выходной поток
    bool state_have_in_file = false; // -\\- входной поток
    bool state_have_dictionary = false;  // был ли передан словарь?
    // Флаги на чтение
    bool state_Mainheader_was_read = false; // Загловок заархивированного файла был прочитан
    bool state_header_was_read = false; // Загловок одного файла был прочитан
    bool state_header_was_read_firstly  = false;    // Загловок одного файла был прочитан впервый раз для текущего файла
    bool state_header_was_read_IsDir;   // текущий файл директория

    bool Write_File(ofstream& File, vector<char>& array, int len_stream);   // Пишет в конец файла
    bool Insert_Header();
};


#endif //ARCH_RW_INTERFACE_H
