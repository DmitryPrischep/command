#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

#include "Write_Liner.h"
#include "Read_Arch.h"
#include "FileInfo.h"
#include "Test_Interface.h"

namespace fs=boost::filesystem;
using namespace std;
using namespace fs;
//template <class T>
void EXP_Write( ostream& out, unsigned long str ){
    out.write((char*)&str, sizeof(str));
//    out << static_cast<unsigned long> (str) ;
}
void func(vector<char> &a, ostream *file){
    for (int i = 0; i < a.size(); ++i) {
        file->write((char*)&a[i], sizeof(a[0]));
    }
}

int main() {
    Test_RW_Interface();
    Test_Recovery();

/*
    // open file ''example.dat'' for reading and writing
    std::filebuf buffer;
    ostream output(&buffer);
//    istream input(&buffer);
    buffer.open ("example.txt", std::ios::binary|std::ios::out );
    unsigned long num = 255;
//    output << num;
//    output.write((char*)&num, sizeof(unsigned long));
//    output << buffer.is_open();
//    buffer.close();
    unsigned long position_in_file =  output.tellp();
    vector<char> tmp;
    char sign_tmp = '1';
    for (int i = 0; i < 30; ++i) {
        tmp.push_back(sign_tmp++);
    }
    func(tmp, &output);
    output.seekp(position_in_file + 5, ios::beg);
    output.write((char*)&num, sizeof(num));
    buffer.close();
//    ifstream tmp;
//    tmp.open("1.txt", ios::in | ios::binary);
//    istream* out (&tmp);
//    istream& asd (tmp);
//    unsigned long num = 123;
//    asd.read((char*)&num, sizeof(num));
//    char a;
//    for (int i = 0; i < 8; ++i) {
//        a = (char)num<<8*i;
//    }
//    tmp.close();

*/



    /*
    // open file ''example.dat'' for reading and writing
    filebuf buffer;
    ostream output(&buffer);
//    istream input(&buffer);
    buffer.open ("example.txt", ios::binary );
    unsigned long num = 255;
//    output << num;
    output.write((char*)&num, sizeof(unsigned long));

// Ted-poll std::tread

//    for (int i=1; i<=4; i++) {
//        // write one line
//        output << i << ". line" << endl;
//
//        // print all file contents
//        input.seekg(0);          // seek to the beginning
//        char c;
//        while (input.get(c)) {
//            cout.put(c);
//        }
//        cout << endl;
//        input.clear();           // clear  eofbit and  failbit
//    }
     */
}