//
// Created by Howle on 07/12/2018.
//

#ifndef COMMAND_RECOVERY_ARCH_H
#define COMMAND_RECOVERY_ARCH_H
#include <iostream>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
using std::vector;
using std::string;
using std::ostream;
using std::filebuf;
class Recovery_Arch{
public:
    Recovery_Arch();
    Recovery_Arch(filebuf stream);

    void RecoveryTakePath(string path);     // Получить путь который будем обрабатывать
    bool RecoveryWrite(vector<char>* input);    // записывает в файл input
    bool RecoveryPathDir(std::string path);     // определить является ли путь путем к папке или путем к файлу
protected:
    string Path;

    filebuf Initialization_file;
    ostream out_file;

    bool state_header_was_read_IsDir = false;
    bool state_header_was_read_firstly = false;
};


#endif //COMMAND_RECOVERY_ARCH_H
