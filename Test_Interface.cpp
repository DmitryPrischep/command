//
// Created by Howle on 25/11/2018.
//

#include "Test_Interface.h"

void Print(vector<char> data){
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void GenData(vector<char> &data, int cupasity){
    static std::random_device read_arch; // Не работает
    std::mt19937 gen(read_arch());
    static std::uniform_int_distribution<> memory(50, 100);
    for (int i = 0; i < cupasity; ++i) {
        data[i] = rand() % 100;
    }
}
vector<char> UnCompressor(vector<char> input){
    return input;
}
bool Test_RW_Interface() {

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
    std::random_device rd;
    std::mt19937 gen(rd());
    static std::uniform_int_distribution<> memory(1024*1024*1, 1024*1024*5);
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

    Write_Liner wr;
    wr.TakeFileOut(file);
    wr.BeginWrite();
    if (wr.HaveOutFile()){
        for (int z = 0; z < Num_test_files; z++){
            wr.TakeHeader(Test_files[z]);
            wr.TakeBody(&rubish[z]);
        }
    } else {
        std::cerr << "Нет файла для записи" << "\n";
    }
    wr.EndWriting(); // Намудрил с булями - они не логичны
    vector<char> outTest[Num_test_files];

    Read_Arch read_arch;
    read_arch.TakeFileIn(file);
    if (read_arch.HaveInFile()){
        read_arch.ReadHeader();
        for ( auto i = 0; read_arch.Is_Have_a_file(); i++ ){
            read_arch.ReadFileHead();
            outTest[i].resize(read_arch.Size_of_one_path());
            for ( ;read_arch.Is_File_Info_Full();){
                outTest[i] = UnCompressor(read_arch.ReadBodyPath());
            }
            read_arch.SubtractFile(); // Вместо Recovery
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
bool Test_Recovery() {

    // Настройка количества тестовых данных
    const int Num_test_files = 4;
    // Задаем тестовую информацию
    vector<char> rubish[Num_test_files];
    std::string file("out.txt");
    std::string ifile("in.txt");
    vector<FileInfo> Test_files;
    std::string Test_paths[Num_test_files] = {
            "tmp/files/readme.txt",
            "tmp/files/round/rou.txt",
            "tmp/stream/str_ew.txt",
            "tmp/out.txt"
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    static std::uniform_int_distribution<> memory(16, 16);
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

    Write_Liner wr;
    wr.TakeFileOut(file);
    wr.BeginWrite();
    if (wr.HaveOutFile()){
        for (int z = 0; z < Num_test_files; z++){
            wr.TakeHeader(Test_files[z]);
            wr.TakeBody(&rubish[z]);
        }
    } else {
        std::cerr << "Нет файла для записи" << "\n";
    }
    wr.EndWriting(); // Намудрил с булями - они не логичны
    vector<char> outTest[Num_test_files];

    Read_Arch read_arch;
    Recovery_Arch recover;
    read_arch.TakeFileIn(file);
    if (read_arch.HaveInFile()){
        read_arch.ReadHeader();
        for ( auto i = 0; read_arch.Is_Have_a_file(); i++ ){
            read_arch.ReadFileHead();
            string header = read_arch.Give_Readed_File_Path();
            recover.RecoveryTakePath(header);
            outTest[i].resize(read_arch.Size_of_one_path());
            for ( ;read_arch.Is_File_Info_Full();){
                outTest[i] = UnCompressor(read_arch.ReadBodyPath());
                recover.RecoveryWrite(&outTest[i]);
            }
            read_arch.SubtractFile(); // Вместо Recovery
        }
    } else {
        std::cerr << "Нет файла для чтения" << "\n";
    }
    for (int k = 0; k < Num_test_files; ++k) {
        if ( fs::exists(Test_paths[k]) ){
            std::cout << "Тест для файла № " << k << " пройден.\n";
        } else {
            return false;
        }
    }
    return true;
}
