//
// Created by Howle on 25/11/2018.
//

#ifndef ARCH_TEST_RW_INTERFACE_H
#define ARCH_TEST_RW_INTERFACE_H

//#include <gtest/gtest.h>
#include "RW_Interface.h"
//#include "Test_Data_Generator.h"
#include <string>
#include <random>
#include "RW_Interface.h"
#include "FileInfo.h"
#include "RW_Liner.h"

void Print(vector<char> data);
vector<char> UnCompressor(vector<char> input);
void GenData(vector<char> &data, int cupasity);
bool Test_RW_Interface();

#endif //ARCH_TEST_RW_INTERFACE_H
