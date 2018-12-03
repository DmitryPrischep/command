//
// Created by Howle on 25/11/2018.
//

#include "Test_RW_Interface.h"

void Print(vector<char> data){
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void GenData(vector<char> &data, int cupasity){
    static std::random_device rd; // Не работает
    std::mt19937 gen(rd());
    static std::uniform_int_distribution<> memory(50, 100);
    for (int i = 0; i < cupasity; ++i) {
        data[i] = rand() % 100;
    }
}
vector<char> UnCompressor(vector<char> input){
    return input;
}
bool Test_RW_Interface() {
    RW_Interface inter;
    // Настройка количества тестовых данных
    const int Num_test_files = 4;
    // Задаем тестовую информацию
    vector<char> rubish[Num_test_files];
    std::string file("out.txt");
    std::string ifile("in.txt");
    vector<FileInfo> Test_files;
    std::string Test_paths[Num_test_files] = {
            "/tmp/files/readme.txt",
            "/tmp/files/round/rou.txt",
            "/tmp/stream/str_ew.txt",
            "tmp/out.txt"
    };
    static std::random_device rd; // Не работает
    std::mt19937 gen(rd());
    static std::uniform_int_distribution<> memory(1024*1024*10, 1024*1024*100);
    for (int l = 0; l < Num_test_files; ++l) {
        FileInfo tmp;
        tmp.AddPath(Test_paths[l]);
        tmp.AddSizeFile( memory(gen) );
        Test_files.emplace_back( tmp );
    }
    // Генерим информацию в файл
    for (int m = 0; m < Num_test_files; ++m) {
        rubish[m].resize(Test_files[m].FileSize());
    }
    for (int j = 0; j < Num_test_files; j++) {
        GenData(rubish[j], static_cast<int>(Test_files[j].FileSize()));
    }

    //std:: cout << std::endl;    // Для тестирования теста
    /*for (auto &k : rubish) {
        Print(k); cout << "\n";
    }*/

    inter.TakeFileOut(file);
    inter.BeginWrite();
    if (inter.HaveOutFile()){
        for (int z = 0; z < Num_test_files; z++){
            inter.TakeHeader(Test_files[z]);
            inter.TakeBody(&rubish[z]);
        }
    } else {
        std::cerr << "Нет файла для записи" << "\n";
    }
    inter.EndWriting(); // Намудрил с булями - они не логичны
    vector<char> outTest[Num_test_files];
    inter.TakeFileIn(file);
    if (inter.HaveInFile()){
        inter.ReadHeader();
        for ( auto i = 0; inter.File_header()->IsAmountFull(); i++ ){
            inter.ReadFileHead();
            outTest[i].resize(inter.File_info().FileSize());
            for ( ;inter.File_info().IsFileFull();){
                outTest[i] = UnCompressor(inter.ReadBodyPath());
            }
            inter.File_header()->SubtractFile(); // Вместо Recovery
        }
    } else {
        std::cerr << "Нет файла для чтения" << "\n";
    }
    for (int k = 0; k < Num_test_files; ++k) {
        if ( std::equal(rubish[k].begin(), rubish[k].begin() + Test_files[k].FileSize(), outTest[k].begin() ) ){
            std::cout << "Тест для массива № " << k << " пройден.\n";
        } else {
            return false;
        }
    }
    return true;
}
