//
// Created by Howle on 12/11/2018.
//

#include "RW_Interface.h"
#include "FileInfo.h"
#include "Union.h"
#include <vector>

class RW_Interface{
public:
    bool TakeHeader(File){

    }
private:
    vector<char> header;
    vector<char> bufer;
    File_Header Main_header;
    int file_amoun;

};
