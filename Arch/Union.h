//
// Created by Howle on 12/11/2018.
//

#ifndef ARCH_UNION_H
#define ARCH_UNION_H

/* Все Union-ы и Strust-ы для нужд архиватора */

class File_Header{
public:
    long int size;
    long int amount;
    int settings;

    void AddSize(int size);
    void AddFile();
};
class Side_Header{
public:
    Side_Header();
    long int size;
    long int pathSize;
};


#endif //ARCH_UNION_H
