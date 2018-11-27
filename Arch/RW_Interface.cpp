//
// Created by Howle on 12/11/2018.
//

#include "RW_Interface.h"

bool RW_Interface::BeginWrite() {
    Main_header.AddSize(sizeof(Main_header));
    vector<char> EmptyVec(sizeof(Main_header));
    if (HaveOutFile()) {
        Write_File(*out_file, EmptyVec);
        return true;
    }
    return false;
}
bool RW_Interface::TakeHeader(FileInfo file_header){
    file_amoun -= 1; // Считает писали ли мы тело
    Main_header.AddFile();
    Main_header.AddSize(file_header.Size()); // Функционал проверни пустого файла временно не доступен
//    if ( !state_header_was_wrote && file_header.Length().size == 0 ){
//        std::cerr << "Использование несколь раз header-а привело к ошибке" << std::endl;
//        return false;
//    }
    for (int i = 0; i < 6; i++){
        header.emplace_back(file_header.Size());
    }
    for (int i = 0; i < 2; i++){
        header.emplace_back(file_header.Length());
    }
    for ( int i = 0; i < file_header.PathLength(); i++){
        header.emplace_back(file_header.Path()[i]);
    }
    state_header_was_wrote = true;
    return true;
}
bool RW_Interface::Take_Dictionary(vector<char> &array) {
    std::copy(array.begin(), array.end(), dictionary.begin());
    state_have_dictionary = true;
}
bool RW_Interface::TakeBody(vector<char>& array, int len_stream){
    Main_header.AddSize(array.size() + 4);
    bool state_writing = Write(array, len_stream);
    state_header_was_wrote = false;
    if (!state_body_was_wrote){ // Считает писали ли мы тело
        state_body_was_wrote = true;
        file_amoun += 1;    // А это нужно?
    }
    return state_writing;
}
bool RW_Interface::Write(vector<char>& array, int len_stream){
    if (state_header_was_wrote){    // Хэдер ли это?
        Write_File(*out_file, header);
    }
    if ( HaveOutFile() ) {
        Write_File(*out_file, array, len_stream);
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
        out_file->seekp(0, std::ios::beg);
        out_file->write((char *)&Main_header.size, sizeof(Main_header.size));
        out_file->write((char *)&Main_header.amount, sizeof(Main_header.amount));
        out_file->write((char *)&Main_header.settings, sizeof(Main_header.settings));
        return true;
    }
    std::cerr << "Нет выходного файла" << "\n";
    return false;
}
bool RW_Interface::EndWriting() {
    if ( state_have_dictionary )
        if (HaveOutFile()){
            Write_File(*out_file, dictionary);
            Insert_Header();
            return true;
        }
    return false;
}
void RW_Interface::TakeFileOut(ofstream& file) {
    out_file = &file;
    state_have_out_file = true;
}
bool RW_Interface::TakeFileIn(ifstream& file){
    in_file = &file;
    state_have_in_file = true;
}
bool RW_Interface::HaveOutFile() {
    return state_have_out_file;
}
bool RW_Interface::HaveInFile() {
    return state_have_in_file;
}

bool RW_Interface::Read() {}
bool RW_Interface::ReadHeader() {
    if (state_Mainheader_was_read){
        std::cerr << "Заголовок уже был прочитан!" << "\n";
    }
    if ( HaveInFile() ){
        in_file->seekg(0, std::ios::beg);
        in_file->read((char*)&Main_header.size, sizeof(Main_header.size));
        in_file->read((char*)&Main_header.amount, sizeof(Main_header.amount));
        in_file->read((char*)&Main_header.settings, sizeof(Main_header.settings));
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
        in_file->read((char*)&file_info.GiveHeader()->size, sizeof(file_info.GiveHeader()->size));
        in_file->read((char*)&file_info.GiveHeader()->pathSize, sizeof(file_info.GiveHeader()->pathSize));
        *file_info.GivePath() = new char(file_info.Length());
        in_file->read((char*)&(*file_info.GivePath()), sizeof(file_info.Length()));
        return true;
    }
    std::cerr << "\nОтсутствует файл для считывания!\n";
    return false;
}

vector<char> RW_Interface::ReadBodyPath(bool &NoErr) {  // Данное архитектура плохая, но необходима для красивой и быстрой передачи данных
    if (!state_Mainheader_was_read){
        std::cerr << "Заголовок еще не был прочитан!" << "\n";
        NoErr = false;
        return vector<char>(0);
    }
    vector<char> out;
    if ( HaveInFile() ){
        int Len_of_str;
        in_file->read((char*)&Len_of_str, sizeof(Len_of_str));
        out.resize(Len_of_str);
        for (int i = 0; i < Len_of_str; i++){
            in_file->read((char*)&out[i], sizeof(char));
        }
        file_info.SubstractSizeFile(Len_of_str + sizeof(Len_of_str));
        NoErr = true;
        return out;
    }
    std::cerr << "\nОтсутствует файл для считывания!\n";
    NoErr = false;
    return vector<char>(0);
}





// Пример использования смотри в RW_Liner.h