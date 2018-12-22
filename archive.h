#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QString>
#include <QDebug>
#include <QFile>
#include <set>
#include <experimental/vector>
#include "compressor/Selector.hpp"
#include "compressor/Huffman.hpp"
#include "compressor/Coder.hpp"
#include "compressor/LZW.hpp"
#include "archive/Write_Liner.h"
#include "archive/Recovery_Arch.h"
#include "archive/FileInfo.h"
#include "archive/Read_Arch.h"
#include "crypto/key.h"
#include "crypto/aes.h"

#include <string>
#include <ostream>
#include <fstream>
#include <iostream>

void create_archive(std::set<std::string> &&data, bool flag_compress,
                    std::string &archive_path, int size = 1048576);

void dearchive(std::string path_to_archive);

void encrypt_archive(const std::string &path, const std::string &pass);

void decrypt_archive(const std::string &path, const std::string &pass);

#endif // ARCHIVE_H
