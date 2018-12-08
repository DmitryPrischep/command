//
// Created by Howle on 05/12/2018.
//

#include "Read_Arch.h"

bool Read_Arch::TakeFileIn(std::string &file){
    Initial_file.open (file, std::ios::binary|std::ios::in );
    if (!Initial_file.is_open()){
        std::cout << "Ошибка инизиализации потока!\n";
    }
    state_have_in_file = true;
}

//bool Read_Arch::TakeFileIn(std::ostream &file) {
//    in_file = file;
//    if (!in_file){
//        std::cout << "Ошибка инизиализации потока! ostream задан не верно!\n";
//    }
//    state_have_in_file = true;
//}

bool Read_Arch::HaveInFile() {
    return state_have_in_file && in_file;
}

bool Read_Arch::ReadHeader() {
    if (state_Mainheader_was_read){
        std::cerr << "Заголовок уже был прочитан!" << "\n";
    }
    if ( HaveInFile() ){
        in_file.seekg(0, std::ios::beg);
        in_file.read((char*)&Main_header.size, sizeof(Main_header.size));
        in_file.read((char*)&Main_header.amount, sizeof(Main_header.amount));
        in_file.read((char*)&Main_header.settings, sizeof(Main_header.settings));
        state_Mainheader_was_read = true;
        return true;
    }
    std::cerr << "\nОтсутствует файл для считывания!\n";
    return false;
}
bool Read_Arch::ReadFileHead() {
    if ( state_header_was_read ){
        state_header_was_read = !state_header_was_read;
    }
    if (!state_Mainheader_was_read){
        std::cerr << "Заголовок еще не был прочитан!" << "\n";
    }
    if ( HaveInFile() ){
        unsigned long size, pathSize;
        in_file.read((char*)&size, sizeof(size));
        in_file.read((char*)&pathSize, sizeof(pathSize));
        char* path = new char[pathSize+1];
        for (int i = 0; i < pathSize; ++i) {
            in_file.read((char*)&path[i], sizeof(char));
        }
        path[pathSize] = '\0';
        file_info.AddSizeFile(size);
        file_info.AddPath(path);
        state_header_was_read = true;
        state_header_was_read_firstly =true;
        delete path;
        return true;
    }
    std::cerr << "\nОтсутствует файл для считывания!\n";
    return false;
}

std::vector<char> Read_Arch::ReadBodyPath(char& Mode) {  // Данное архитектура плохая, но необходима для красивой и быстрой передачи данных
    if (!state_Mainheader_was_read){
        std::cerr << "Заголовок еще не был прочитан!" << "\n";
        return std::vector<char>(0);
    }
    std::vector<char> out;
    if ( HaveInFile() ){
        unsigned long Len_of_str;
        in_file.read((char*)&mode, sizeof(mode));
        Mode = mode;
        in_file.read((char*)&Len_of_str, sizeof(Len_of_str));
        out.resize(Len_of_str);
        for (int i = 0; i < Len_of_str; i++){
            in_file.read((char*)&out[i], sizeof(char));
        }
        file_info.SubstractSizeFile(Len_of_str);
        return out;
    }
    std::cerr << "\nОтсутствует файл для считывания!\n";
    return vector<char>(0);
}

Read_Arch::Read_Arch(): in_file(&Initial_file) {
}

//File_Header* Read_Arch::File_header(){
//    return &Main_header;
//}
//FileInfo Read_Arch::File_info(){
//    return file_info;
//}

bool Read_Arch::Is_Have_a_file() {
    return Main_header.IsAmountFull();
}

void Read_Arch::SubtractFile() {
    Main_header.SubtractFile();
}
unsigned long Read_Arch::Size_of_one_path(){
    return file_info.FileSize();
}
bool Read_Arch::Is_File_Info_Full(){
    return file_info.IsFileFull();
}

string Read_Arch::Give_Readed_File_Path() {
    return file_info.StrPath();
}
