//
// Created by Howle on 12/11/2018.
//

#include "RW_Interface.h"
#include "string.h"
bool RW_Interface::BeginWrite() {
    Main_header.AddSize(sizeof(Main_header));
    vector<char> EmptyVec(sizeof(Main_header));
    if (HaveOutFile()) {
        Write_File(out_file, EmptyVec);
        return true;
    }
    return false;
}
bool RW_Interface::TakeHeader(FileInfo file_header){
    file_amoun -= 1; // Считает писали ли мы тело
    Main_header.AddFile();
    Main_header.AddSize(file_header.FileSize());

    for (int i = 0; i < sizeof(unsigned long); i++){
        header.emplace_back(file_header.FileSize() >> 8*i);
    }
    for (int i = 0; i < sizeof(unsigned long); i++){
        header.emplace_back(file_header.PathSize() >> 8*i);
    }
    char* str = file_header.Path();
    for ( int i = 0; i < file_header.PathSize(); i++){
        header.emplace_back(str[i]);
    }
    state_header_was_wrote = true;
    return true;
}
bool RW_Interface::Take_Dictionary(vector<char> &array) {
    std::copy(array.begin(), array.end(), dictionary.begin());
    state_have_dictionary = true;
}
bool RW_Interface::TakeBody(vector<char> array){
    Main_header.AddSize(static_cast<int>(array.size() + sizeof(int)));
    bool state_writing = Write(array, static_cast<int>(array.size()));
    state_header_was_wrote = false;
    if (!state_body_was_wrote){ // Считает писали ли мы тело
        state_body_was_wrote = true;
    }
    return state_writing;
}
bool RW_Interface::Write(vector<char>& array, int len_stream){
    if (state_header_was_wrote){    // Хэдер ли это?
        Write_File(out_file, header);
    }
    if ( HaveOutFile() ) {
        Write_File(out_file, array, len_stream);
        return true;
    }
    std::cerr << "Нет выходного файла" << "\n";
    return false;
}
bool RW_Interface::Write_File(ofstream& File, vector<char>& array, int len_stream){
    File.seekp(0, std::ios::end);
    File.write((char *) &len_stream, sizeof(len_stream));
    File.write((char *) &array, array.size());
}
bool RW_Interface::Write_File(ofstream& File, vector<char>& array){
    File.seekp(0, std::ios::end);
    File.write((char *) &array, array.size());
    return true;
}
bool RW_Interface::Insert_Header() {
    if (HaveOutFile()){
        out_file.seekp(0, std::ios::beg);
        out_file.write((char *)&Main_header.size, sizeof(Main_header.size));
        out_file.write((char *)&Main_header.amount, sizeof(Main_header.amount));
        out_file.write((char *)&Main_header.settings, sizeof(Main_header.settings));
        return true;
    }
    std::cerr << "Нет выходного файла" << "\n";
    return false;
}
bool RW_Interface::EndWriting() {
    out_file.close();
    if ( state_have_dictionary )
        if (HaveOutFile()){
            Write_File(out_file, dictionary);
            Insert_Header();
            return true;
        }
    return false;
}
void RW_Interface::TakeFileOut(std::string &file) {
    out_file.open(file);
    if (!out_file){
        std::cout << "ERR\n";
    }
    state_have_out_file = true;
}
bool RW_Interface::TakeFileIn(std::string &file){
    in_file.open(file);
    if (!in_file){
        std::cout << "ERR\n";
    }
    state_have_in_file = true;
}
bool RW_Interface::HaveOutFile() {
    return state_have_out_file;
}
bool RW_Interface::HaveInFile() {
    return state_have_in_file;
}

bool RW_Interface::ReadHeader() {
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
bool RW_Interface::ReadFileHead() {
    if (!state_Mainheader_was_read){
        std::cerr << "Заголовок еще не был прочитан!" << "\n";
    }
    if ( HaveInFile() ){
        unsigned long size, pathSize;
        in_file.read((char*)&size, sizeof(size));
        in_file.read((char*)&pathSize, sizeof(pathSize));
        char* path = new char(pathSize);
        in_file.read((char*)&path, pathSize);
        file_info.AddSizeFile(size);
        file_info.AddPath(path);
        delete path;
        return true;
    }
    std::cerr << "\nОтсутствует файл для считывания!\n";
    return false;
}

vector<char> RW_Interface::ReadBodyPath() {  // Данное архитектура плохая, но необходима для красивой и быстрой передачи данных
    if (!state_Mainheader_was_read){
        std::cerr << "Заголовок еще не был прочитан!" << "\n";
        return vector<char>(0);
    }
    vector<char> out;
    if ( HaveInFile() ){
        int Len_of_str;
        in_file.read((char*)&Len_of_str, sizeof(Len_of_str));
        out.resize(Len_of_str);
        for (int i = 0; i < Len_of_str; i++){
            in_file.read((char*)&out[i], sizeof(char));
        }
        file_info.SubstractSizeFile(Len_of_str + sizeof(Len_of_str));
        return out;
    }
    std::cerr << "\nОтсутствует файл для считывания!\n";
    return vector<char>(0);
}
File_Header* RW_Interface::File_header(){
    return &Main_header;
}
FileInfo* RW_Interface::File_info(){
    return &file_info;
}
/*
bool RW_Interface::RecoveryPathDir(std::string path) {
    auto i = path.size();
    if ( path[i-1] == '/' ) {
        if ( fs::exists(path) ) {
            return true; // Создана директория
        } else {
            fs::create_directory(path);
            return true;
        }
    }
    i = path.size() - 2;
    for (; i > 0 && path[i] != '/'; ++i) {}
    if ( i != 0 ){
        std::string tmp_path;
        for (int j = 0; j < i; ++j) {
            tmp_path[j] = path[j];
        }
        fs::create_directory(tmp_path);
        return false;
    } else {
        return false;
    }

}
*/

bool RW_Interface::RecoveryWrite() {
    return false;
}





// Пример использования смотри в RW_Liner.h