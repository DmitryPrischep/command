//
// Created by Howle on 04/12/2018.
//

#include "Write_Liner.h"


bool Write_Liner::BeginWrite() {
    Main_header.AddSize(sizeof(Main_header));
    vector<char> EmptyVec(sizeof(Main_header));
    if (HaveOutFile()) {
        Write_File(out_file, &EmptyVec);
        return true;
    }
    std::cerr << "Не удалось начать писать файл\n";
    return false;
}
bool Write_Liner::TakeHeader(FileInfo file_header){
    Main_header.AddFile();
    Main_header.AddSize(sizeof(file_header));
    unsigned long filesize = file_header.FileSize(),
            file_pathsize = file_header.PathSize();
    out_file.write((char*)&filesize, sizeof(filesize));
    out_file.write((char*)&file_pathsize, sizeof(file_pathsize));
    char* str = file_header.Path();
    for (int i = 0; i < file_header.PathSize(); ++i) {
        out_file.write((char*)&str[i], sizeof(str[0]));
    }
    delete []str;
    state_header_was_wrote = true;
    return true;
}
bool Write_Liner::Take_Dictionary(vector<char>* array) {
    std::copy(array->begin(), array->end(), dictionary.begin());
    state_have_dictionary = true;
}
bool Write_Liner::TakeBody(vector<char>* array, char mode, bool is_it_ending){
    Main_header.AddSize(array->size() + sizeof(unsigned long) + sizeof(mode) + sizeof(is_it_ending));
    bool state_writing = Write(array, array->size(), mode, is_it_ending);
    state_header_was_wrote = false;
    if (!state_body_was_wrote){ // Считает писали ли мы тело
        state_body_was_wrote = true;
    }
    return state_writing;
}
bool Write_Liner::Write(vector<char>* array, unsigned long len_stream){
    if (!state_header_was_wrote){
        std::cerr << "Не был записан заголовок для этого файла!\n";
    }
    if ( HaveOutFile() ) {
        Write_File(out_file, array, len_stream);
        return true;
    }
    std::cerr << "Нет выходного файла" << "\n";
    return false;
}
bool Write_Liner::Write(vector<char>* array, unsigned long len_stream, char mode, bool is_it_ending){
    if ( HaveOutFile() ) {
        Write_File(out_file, array, len_stream, mode, is_it_ending);
        return true;
    }
    std::cerr << "Нет выходного файла" << "\n";
    return false;
}
bool Write_Liner::Write_File(std::ostream& File, vector<char>* array, unsigned long len_stream){
    File.seekp(0, std::ios::end);
    File.write((char *) &len_stream, sizeof(len_stream));
    for (int i = 0; i < array->size(); i++){
        File.write((char *) &(*array)[i], sizeof((*array)[0]));
    }

}
bool Write_Liner::Write_File(std::ostream& File, vector<char>* array, unsigned long len_stream, char mode, bool is_it_ending){
    File.seekp(0, std::ios::end);
    File.write((char*)&mode, sizeof(mode));
    File.write((char *) &len_stream, sizeof(len_stream));
    for (int i = 0; i < array->size(); i++){
        File.write((char *) &(*array)[i], sizeof((*array)[0]));
    }
    File.write((char*)&is_it_ending, sizeof(is_it_ending));
}
bool Write_Liner::Write_File(std::ostream& File, vector<char>* array){
    File.seekp(0, std::ios::end);
    for (int i = 0; i < array->size(); i++){
        File.write((char *) &(*array)[i], sizeof((*array)[0]));
    }
    return true;
}
bool Write_Liner::Insert_Header() {
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
bool Write_Liner::EndWriting() {
    if ( state_have_dictionary ) {
        if (HaveOutFile()) {
            Write_File(out_file, &dictionary);
            Insert_Header();
        }
    }
    Insert_Header();
    if ( Initial_file.is_open() ){
        Initial_file.close();
        return true;
    }
    std::cerr << "Ощибка закрытия потока на запись!\n";
    return false;
}
void Write_Liner::TakeFileOut(std::string &file) {
    Initial_file.open (file, std::ios::binary|std::ios::out );
    if (!Initial_file.is_open()){
        std::cout << "Ошибка инизиализации потока!\n";
    }
    state_have_out_file = true;
}
//void Write_Liner::TakeFileOut(std::ostream &out) {    // Функция временно не доступна
//    out_file = out;
//    if (!out_file){
//        std::cerr << "Ошибка инизиализации потока! ostream задан не верно!\n"
//    }
//    state_have_out_file = true;
//}
bool Write_Liner::HaveOutFile() {
    return state_have_out_file && Initial_file.is_open();
}

Write_Liner::Write_Liner():out_file(&Initial_file) {
}

