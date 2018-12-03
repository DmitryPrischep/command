#include <iostream>
#include <random>
#include "RW_Interface.h"
#include "FileInfo.h"
//#include "RW_Liner.h"
#include <memory>
//#include "Test_Data_Generator.h"
//#include "Test_RW_Interface.h"

using namespace std;
void Print(vector<char> data){
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}
//std::vector<char> readFile(const char* filename)
//{
//    // open the file:
//    std::ifstream file(filename, std::ios::binary);
//    if (file){
//        cout << "File" << endl;
//    }
//    // Stop eating new lines in binary mode!!!
//    file.unsetf(std::ios::skipws);
//
//    // get its size:
//    int fileSize;
//
//    file.seekg(0, std::ios::end);
//
//    fileSize = static_cast<int>(file.tellg());
//    cout << fileSize;
//    file.seekg(0, std::ios::beg);
//
//    // reserve capacity
//    std::vector<char> vec(fileSize);
//
//
//    // read the data:
////    file.read((char*)&vec, 100);
//    for (int i = 0; i < fileSize; ++i) {
//        file.read((char*)&vec[i], sizeof(char));
//    }
//    return vec;
//}

struct Kilobyte {
    char vec[1024];
};
void GenData(vector<char> &data, int cupasity){
    for (int i = 0; i < cupasity; ++i) {
        data[i] = rand() % 100;
    }
}
void LPrint(vector<char> &data){
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}
vector<char> UnCompressor(vector<char> input){
    return input;
}
int main() {
    RW_Interface inter;
    // Настройка количества тестовых данных
    const int Num_test_files = 1;
    // Задаем тестовую информацию
//    vector<vector<char>> rubish(1);
    vector<char> rubish[Num_test_files];
    string file("out.txt");
    string ifile("in.txt");
    vector<FileInfo> Test_files;
    string Test_paths[4] = {    // В стринге для удобства редактирования
            "/tmp/files/readme.txt",
            "/tmp/files/round/rou.txt",
            "/tmp/stream/str_ew.txt",
            "tmp/out.txt"
    };
//    static std::random_device rd; // Не работает
//    std::mt19937 gen(rd());
//    static std::uniform_int_distribution<> memory(1024*1024*1, 1024*1024*50);
    srand(time(0));
    for (int l = 0; l < Num_test_files; ++l) {
        FileInfo tmp;
        tmp.AddPath(Test_paths[l]);
        tmp.AddSizeFile( (16)  );
        Test_files.emplace_back( tmp );
    }
    // Генерим информацию в файл
    for (int m = 0; m < Num_test_files; ++m) {
        rubish[m].resize(Test_files[m].FileSize());
    }
    for (int j = 0; j < Num_test_files; j++) {
        GenData(rubish[j], static_cast<int>(Test_files[j].FileSize()));
    }

    std:: cout << std::endl;    // Для тестирования теста
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

    inter.TakeFileIn(file);
    if (inter.HaveInFile()){
        inter.ReadHeader();
        for ( auto i = 0; inter.File_header().IsAmountFull(); i++ ){
            inter.ReadFileHead();
            vector<char> Readed_rubish;
            Readed_rubish.reserve(inter.File_info().FileSize());
            for ( ;inter.File_info().IsFileFull(); ){
                vector<char> tmp_vec = UnCompressor(inter.ReadBodyPath());
                inter.RecoveryWrite(tmp_vec);
            }
        }
    } else {
        std::cerr << "Нет файла для чтения" << "\n";
    }
}
