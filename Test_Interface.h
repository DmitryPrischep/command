//
// Created by Howle on 25/11/2018.
//

#ifndef ARCH_TEST_RW_INTERFACE_H
#define ARCH_TEST_RW_INTERFACE_H

//#include <gtest/gtest.h>
//#include "Test_Data_Generator.h"
#include <string>
#include <random>
#include "Write_Liner.h"
#include "Read_Arch.h"
#include "FileInfo.h"
#include "Recovery_Arch.h"
void Print(vector<char> data);
vector<char> UnCompressor(vector<char> input);
void GenData(vector<char> &data, int cupasity);
bool Test_RW_Interface();
bool Test_Recovery();

#endif //ARCH_TEST_RW_INTERFACE_H
