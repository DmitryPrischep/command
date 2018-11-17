//
// Created by Howle on 12/11/2018.
//

#include "RW_Interface.h"

bool RW_Interface::TakeHeader(FileInfo file_header){
    file_amoun -= 1; // Считает писали ли мы тело
    Main_header.AddFile();
    Main_header.AddSize(file_header.Length().size.size_int);
    if ( file_amoun ){
        std::cerr << "Использование несколь раз header-а привело к ошибке" << std::endl;
        return false;
    }
    for (int i = 0; i < 6; i++){
        header.emplace_back(file_header.Length().size.size_char[i]);
    }
    for (int i = 0; i < 2; i++){
        header.emplace_back(file_header.Length().pathSize.pathSize_char[i]);
    }
    for ( int i = 0; i < file_header.PathLength(); i++){
        header.emplace_back(file_header.Path()[i]);
    }
    state_header_was_wrote = true;
    return true;
}
void RW_Interface::TakeFileOut(ofstream& file) {
    out_file = &file;
    state_have_out_file = true;
}
bool RW_Interface::TakeFileIn(ifstream& file){
    in_file = &file;
    state_have_in_file = true;
}
bool RW_Interface::TakeBody(vector<char>& array){

    Write(array);  // Так не должно быть!!! Это должна реализовывать функция ребенок!
    state_header_was_wrote = false;
    if (!state_body_was_wrote){ // Считает писали ли мы тело
        state_body_was_wrote = true;
        file_amoun += 1;
    }
//    Write_File(*out_file, array);
}
bool RW_Interface::Write(vector<char>& array){}
bool RW_Interface::Write_File(ofstream& File, vector<char>& array){
    File.seekp(0, std::ios::end);
    File.write((char*)&array, array.size());
}

bool RW_Interface::HaveOutFile() {
    return state_have_out_file;
}

bool RW_Interface::HaveInFile() {
    return state_have_in_file;
}

bool RW_Interface::Read() {}

bool RW_Interface::Insert_Header(ofstream& File) {
    File.seekp(0, std::ios::beg);
    File.write((char*)&Main_header, sizeof(Main_header));
}

bool RW_Interface::ReadHeader() {
    if ( !state_have_in_file ){
        std::cerr << "\nОтсутствует файл для считывания!\n";
        return false;
    }
    in_file->read((char*)&Main_header.size.size_int, sizeof(Main_header.size));
    in_file->read((char*)&Main_header.amount, sizeof(Main_header.amount));
    in_file->read((char*)&Main_header.settings, sizeof(Main_header.settings));
    return true;
}

bool RW_Interface::ReadFileHead() {
    in_file->read((char*)&file_info.GiveHeader()->size, sizeof(file_info.GiveHeader()->size));
    in_file->read((char*)&file_info.GiveHeader()->pathSize, sizeof(file_info.GiveHeader()->pathSize));
    *file_info.GivePath() = new char(file_info.Length().pathSize.pathSize_int);
    in_file->read((char*)&(*file_info.GivePath()), sizeof(file_info.Length().pathSize.pathSize_int));
}






// Пример использования смотри в RW_Liner.h