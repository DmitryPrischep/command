#include <iostream>
#include <random>
//#include "FileInfo.h"
#include "RW_Interface.h"
#include "FileInfo.h"
#include "RW_Liner.h"
#include "Test_Data_Generator.h"
#include "Test_RW_Interface.h"

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

int main() {
    Print(readFile("/Users/howle/prog/Cpp/WTexn/C/Project/Comand_23.11/command/Arch/tmp1.txt"));

}
