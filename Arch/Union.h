//
// Created by Howle on 12/11/2018.
//

#ifndef ARCH_UNION_H
#define ARCH_UNION_H

/* Все Union-ы и Strust-ы для нужд архиватора */

union Main_header_sizeFile{
    long int size_int;
    unsigned char size_char[8];
};
union Main_header_amountFile{
    long int amount_int;
    unsigned char amount_char[8];
};
union Main_header_settings{
    int settings_int;
    unsigned char settings_char[4];
};
struct File_Header{
    Main_header_sizeFile size;
    Main_header_amountFile amount;
    Main_header_settings settings;
};
union Side_header_size {
    long int size_int ;
    unsigned char size_char[8];
};
union Side_header_pathSize {
    long int pathSize_int;
    unsigned char pathSize_char[8];
};
struct Side_Header{
    Side_header_size size;
    Side_header_pathSize pathSize;
};

#endif //ARCH_UNION_H
