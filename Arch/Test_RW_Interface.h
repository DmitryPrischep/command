//
// Created by Howle on 25/11/2018.
//

#ifndef ARCH_TEST_RW_INTERFACE_H
#define ARCH_TEST_RW_INTERFACE_H

#include <gtest/gtest.h>
#include "RW_Interface.h"
#include "Test_Data_Generator.h"
#include <string>
#include <random>
using std::ofstream;
using std::ifstream;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

class Test_RW_Interface :
        public RW_Interface,
        public ::testing::Test {

protected:
    void Write_and_Read_Liner();

};


#endif //ARCH_TEST_RW_INTERFACE_H
