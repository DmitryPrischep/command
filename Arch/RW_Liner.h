//
// Created by Howle on 15/11/2018.
//

#ifndef ARCH_RW_LINER_H
#define ARCH_RW_LINER_H
#include "RW_Liner.h"
#include "RW_Interface.h"
#include "FileInfo.h"
#include <iostream>
#include <vector>
#include <fstream>

class RW_Liner : public RW_Interface {
public:
    virtual bool Write(vector<char>& array);
    virtual bool Read(vector<char>& array);
protected:

};

// Пример использования

/*

int main() {
    RW_Interface *inter = new RW_Liner;
    FileInfo info("as.txt", 123);
    vector<vector<char>> rubish(10);
    ofstream file("/Users/howle/prog/Cpp/WTexn/C/Project/command/Arch/tmp.txt");
    inter->TakeFileOut(file);
    for (auto &j : rubish) {
        GenData(j, 1024);
    }
    std:: cout << std::endl;
    for (auto &k : rubish) {
        Print(k);
    }
    inter->TakeHeader(info);
    if (inter->HaveOutFile()){
        for (auto &i : rubish) {
            inter->TakeBody(i);
        }
    } else {
        std::cerr << "Нет файла" << std::endl;
    }
    return 0;
}
 */

#endif //ARCH_RW_LINER_H
