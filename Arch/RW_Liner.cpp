//
// Created by Howle on 15/11/2018.
//

#include "RW_Liner.h"

bool RW_Liner::Write(vector<char>& array){
    // Некий Анализ ....
    if (state_header_was_wrote){    // Хэдер ли это?
        Write_File(*out_file, header);
    }
    Write_File(*out_file, array);
}


bool RW_Liner::Read(vector<char> &array) {
   // Re
}
