#include <utility>

#include <utility>

//
// Created by Howle on 07/12/2018.
//

#include "Recovery_Arch.h"

bool Recovery_Arch::RecoveryWrite(vector<char> *input) {
        state_header_was_read_firstly = false;
        if ( state_header_was_read_IsDir ){
            return true;
        } else {
            for (int i = 0; i < input->size(); ++i) {
                out_file.write((char*)&(*input)[i], sizeof((*input)[0]));
            }
        }
//        Main_header.SubtractFile();
}

bool Recovery_Arch::RecoveryPathDir(std::string path) {
    auto i = path.size() - 1;

    if ( path[i] == '/' ) {
        if ( fs::exists(path) ) {
            return true; // Создана директория
        } else {
            fs::create_directories(path);
            return true;
        }
    }
    i -= 1;
    for (; i > 0 && path[i] != '/'; --i) {}
    if ( i != 0 ){
        std::string tmp_path = path.substr(0,i);
        fs::create_directories(path.substr(0,i));
//        bool havethisdir = fs::exists(path.substr(0,i));
//        fs::path root = fs::current_path();
    }
    return false;
}

void Recovery_Arch::RecoveryTakePath(string path) {
    this->Path = path;
    if ( !state_header_was_read_firstly ){
        state_header_was_read_IsDir = RecoveryPathDir(Path);
        state_header_was_read_firstly = !state_header_was_read_firstly;
        if ( !state_header_was_read_IsDir ){
            Initialization_file.close();
            Initialization_file.open(Path, std::ios::binary|std::ios::out );
        }
    }
}

Recovery_Arch::Recovery_Arch(): out_file(&Initialization_file) {
}
Recovery_Arch::Recovery_Arch(filebuf stream): out_file(&stream) {
}
