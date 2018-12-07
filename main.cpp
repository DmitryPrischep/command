#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include "Write_Liner.h"
#include "Read_Arch.h"
#include "FileInfo.h"
#include "Test_Interface.h"

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
//    cout << "\n";
}

int main() {

//    fs::create_directories("/tmp/files");


//    create_directories("tmp/files");
//    cout << current_path() << "\t" << exists("tmp/files") << endl;
    Test_Recovery();

    /*
    // open file ''example.dat'' for reading and writing
    filebuf buffer;
    ostream output(&buffer);
//    istream input(&buffer);
    buffer.open ("example.txt", std::ios::binary|std::ios::out );
    unsigned long num = 25534;
//    output << num;
//    output.write((char*)&num, sizeof(unsigned long));
//    output << buffer.is_open();
//    buffer.close();


    vector<char> tmp;
    tmp.push_back('1');
    tmp.push_back('3');
    tmp.push_back('e');
    func(tmp, &output);
     */
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