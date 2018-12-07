//
// Created by Howle on 05/12/2018.
//

#ifndef COMMAND_READ_ARCH_H
#define COMMAND_READ_ARCH_H
#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include "FileInfo.h"
using std::ofstream;
using std::ifstream;
using std::vector;
using std::string;
class Read_Arch{
public:
    Read_Arch();
    bool TakeFileIn(std::string &file); // Получить путь к Архиву на чтение
    bool TakeFileIn(std::ostream &file); // Получить поток Архива для чтения
    bool HaveInFile();  // Проверка на открытие файла и на его существование
    bool ReadHeader();  // Считать заголовок всего документа
//    File_Header* File_header();
//    FileInfo File_info();
    bool ReadFileHead();    // Считать заголовок 1 файла в file_info
    std::vector<char> ReadBodyPath();    // Будет прыгать по файлу и читать кусочек файла. Далее передать в Разжатие, а после в FileRecoveryWrite

    bool Is_Have_a_file();
    void SubtractFile();
    unsigned long Size_of_one_path();
    bool Is_File_Info_Full();
    string Give_Readed_File_Path();
protected:
    File_Header Main_header;
    FileInfo file_info;

    std::filebuf Initial_file;
    std::istream in_file;
    // Флаги на чтение
    bool state_Mainheader_was_read = false; // Загловок заархивированного файла был прочитан
    bool state_header_was_read = false; // Загловок одного файла был прочитан
    bool state_have_in_file = false; // -\\- входной поток
    bool state_header_was_read_firstly  = false;    // Загловок одного файла был прочитан впервый раз для текущего файла
    bool state_header_was_read_IsDir;   // текущий файл директория
};


#endif //COMMAND_READ_ARCH_H
