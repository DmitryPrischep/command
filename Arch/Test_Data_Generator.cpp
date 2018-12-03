//
// Created by Howle on 25/11/2018.
//

#include "Test_Data_Generator.h"


void GenData(vector<char> &data, int cupasity){
    srand(time(0));
    for (int i = 0; i < cupasity; ++i) {
        data.__emplace_back(rand()%50 + 25);
    }
}
void Print(vector<char> &data){
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}
char* CutStrings( char* &str, int size){
    int str_end;
    for (int i = size - 1; i > 0 ; i--) {
        if ( str[i] == '/' ){
            str_end = i;
            break;
        }
    }
    char* out = new char[str_end];
    for (int j = 0; j < str_end - 1; ++j) {
        out[j] = str[j];
    }
    return out;
}

vector<char> UnCompressor(vector<char>& vec){  // реализация компрессора
    return vec;
}