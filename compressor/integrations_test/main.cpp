#include <iostream>
#include "Test_RW_Interface.h"

int main() {
    bool test1 = Test_RW_Interface();
    if ( test1 ){
        std:: cout << "Тест удачно пройден!";
    }
    return 0;
}
