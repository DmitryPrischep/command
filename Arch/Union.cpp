//
// Created by Howle on 15/11/2018.
//

#include "Union.h"

Side_Header::Side_Header() {
    size.size_int = 0;
    pathSize.pathSize_int = 0;
}

void File_Header::AddSize(int size) {
    this->size.size_int += size;
}

void File_Header::AddFile() {
    amount.amount_int++;
}

