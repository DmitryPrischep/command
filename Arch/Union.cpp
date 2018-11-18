//
// Created by Howle on 15/11/2018.
//

#include "Union.h"

Side_Header::Side_Header() {
    size = 0;
    pathSize = 0;
}

void File_Header::AddSize(int size) {
    this->size += size;
}

void File_Header::AddFile() {
    amount++;
}

