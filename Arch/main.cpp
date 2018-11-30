#include <iostream>
#include <random>
//#include "FileInfo.h"
#include "RW_Interface.h"
#include "FileInfo.h"
#include "RW_Liner.h"
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
std::vector<char> readFile(const char* filename)
{
    // open the file:
    std::ifstream file(filename, std::ios::binary);
    if (file){
        cout << "File" << endl;
    }
    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    int fileSize;

    file.seekg(0, std::ios::end);

    fileSize = static_cast<int>(file.tellg());
    cout << fileSize;
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<char> vec(fileSize);


    // read the data:
//    file.read((char*)&vec, 100);
    for (int i = 0; i < fileSize; ++i) {
        file.read((char*)&vec[i], sizeof(char));
    }
    return vec;
}

struct Kilobyte {
    char vec[1024];
};
void GenData(vector<char> &data, int cupasity){
    srand(time(0));
    for (int i = 0; i < cupasity; ++i) {
        data.emplace_back(rand()%50 + 25);
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
//    Print(readFile("/Users/howle/prog/Cpp/WTexn/C/Project/Comand_23.11/command/Arch/tmp1.txt"));
    RW_Interface inter;
    // Настройка количества тестовых данных
    const int Num_test_files = 4;
    // Задаем тестовую информацию
    vector<vector<char>> rubish(Num_test_files);
    char* file = new char[100];
    file = "/Users/howle/prog/Cpp/WTexn/C/Project/Comand_23.11/command/Arch/out.txt";
    char* ifile = new char[100];
    ifile = "/Users/howle/prog/Cpp/WTexn/C/Project/Comand_23.11/command/Arch/in.txt";
    vector<FileInfo> Test_files;
    string Test_paths[Num_test_files] = {    // В стринге для удобства редактирования
            "/tmp/files/readme.txt",
            "/tmp/files/round/rou.txt",
            "/tmp/stream/str_ew.txt",
            "/tmp/out.txt"
    };
    std::mt19937 gen(time(0));
    uniform_int_distribution<> memory(1024*1024*1, 1024*1024*5);
    for (int l = 0; l < Num_test_files; ++l) {
        char* tmp = new char[Test_paths[l].size()+1];
        cout << endl << Test_paths[l].size();
        strcpy( tmp, Test_paths[l].c_str() );   // Это не эффективно, но пока так удобнее. Позже будет или оптимальнее, или автогенерация пути.
        FileInfo Ftmp(tmp, memory(gen));
        Test_files.emplace_back( Ftmp );
        delete[] tmp;
    }
    // Генерим информацию в файл

    for (int j = 0; j < Num_test_files; j++) {
        GenData( rubish[j], Test_files[j].Size() );
    }

    std::cout << std::endl;    // Для тестирования теста
    for (auto &k : rubish) {
//        LPrint(k); cout << "\n";
    }
//    ofstream a(file);
    inter.TakeFileOut(file);
    inter.BeginWrite();
    if (inter.HaveOutFile()){
        for (int z = 0; z < Num_test_files; z++){
            inter.TakeHeader(Test_files[z]);
            inter.TakeBody(rubish[z], rubish.size());
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
            vector<char> Readed_rubish(rubish[i].size());
            for ( ;inter.File_info()->IsFileFull(); ){
                bool problem;
                UnCompressor(inter.ReadBodyPath(problem));
            }
        }
    } else {
        std::cerr << "Нет файла для чтения" << "\n";
    }
//    vector<char> a;
////    int tmp=1801;
////    for (int i = 0; i < 4; ++i) {
////        a.push_back(tmp >> 8*i);
////    }
////    for (auto&s:a){
////        cout << s;
////    }
}
