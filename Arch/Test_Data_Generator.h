//
// Created by Howle on 25/11/2018.
//

#ifndef ARCH_TEST_DATA_GENERATOR_H
#define ARCH_TEST_DATA_GENERATOR_H

#include <vector>
#include <string>
using std::vector;
using std::string;
void GenData(vector<char> &data, int cupasity);
void Print(vector<char> &data);
char* CutStrings( char* &str, int size);
vector<char> UnCompressor(vector<char> vec){; // реализация компрессора

#endif //ARCH_TEST_DATA_GENERATOR_H
