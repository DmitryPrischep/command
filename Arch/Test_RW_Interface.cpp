//
// Created by Howle on 25/11/2018.
//

#include "Test_RW_Interface.h"


void Test_RW_Interface::Write_and_Read_Liner() {
    RW_Interface inter;
    // Настройка количества тестовых данных
    const int Num_test_files = 4;
    // Задаем тестовую информацию
    vector<vector<char>> rubish(1);
    ofstream file;
    ifstream ifile;
    vector<FileInfo> Test_files;
    string Test_paths[Num_test_files] = {    // В стринге для удобства редактирования
            "/tmp/files/readme.txt",
            "/tmp/files/round/rou.txt",
            "/tmp/stream/str_ew.txt",
            "tmp/out.txt"
    };
    std::mt19937 gen(time(0));
    uniform_int_distribution<> memory(1024*1024*1, 1024*1024*50);
    for (int l = 0; l < Num_test_files; ++l) {
        char* tmp;
        Test_files.emplace_back( Test_paths[l], memory(gen) );
    }
    // Генерим информацию в файл

    for (int j = 0; j < Num_test_files; i++) {
        GenData( rubish[j], Test_files[j].Size() );
    }

    std:: cout << std::endl;    // Для тестирования теста
    for (auto &k : rubish) {
        Print(k); cout << "\n";
    }

    inter.TakeFileOut(file);
    inter.BeginWrite();
    if (inter->HaveOutFile()){
        for (int z = 0; z < Num_test_files; z++){
            inter.TakeHeader(Test_files[z]);
            inter.TakeBody(rubish[z]), rubish.size()); // убери второй элемент
        }
    } else {
        std::cerr << "Нет файла для записи" << "\n";
    }
    inter.EndWriting();

    inter.TakeFileIn(ifile);
    if (inter.HaveInFile()){
        inter.ReadHeader();
        for ( auto i = 0; inter.File_header()->IsAmountFull(); i++ ){
            inter.ReadFileHead();
            vector<char> Readed_rubish(inter.File_info()->FileSize());
            for ( file_info.IsFileFull() ){
                UnCompressor(inter->ReadBodyPath());
            }
        }
    } else {
        std::cerr << "Нет файла для чтения" << "\n";
    }
}
