#include <iostream>
#include <string>
#include <vector>
#include "chrono"
#include "aes.h"
#include "sha512.h"
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

void test_01()
{
    unsigned char one = 0x05;
    unsigned char two = 0x09;
    byte res = AES::xor_byte(one, two);
    if(res == 0x0C){
        std::cout << "Test_01 PASS" <<std::endl;
    } else {
        std::cout << "Test_01 FAIL" <<std::endl;
        std::cout << "The expected value is " << 0x0C << " Get the value " << res << std::endl;
    }
}

void test_02()
{
    unsigned char one = 0x12;
    unsigned char two = 0x15;
    byte res = AES::xor_byte(one, two);
    if(res == 0x07){
        std::cout << "Test_02 PASS" <<std::endl;
    } else {
        std::cout << "Test_02 FAIL" <<std::endl;
        std::cout << "The expected value is " << std::hex << 0x07
                  << " Get the value " << std::hex << res << std::endl;
    }
    std::cout << res;
}

void test_03()
{
    unsigned char one = 0x10;
    unsigned char two = 0x10;
    byte res = AES::xor_byte(one, two);
    if(res == 0x00){
        std::cout << "Test_03 PASS" <<std::endl;
    } else {
        std::cout << "Test_03 FAIL" <<std::endl;
        std::cout << "The expected value is " << 0x00 << " Get the value " << res << std::endl;
    }
}

void test_04()
{
    ByteArray one = {{0x00, 0x02, 0x04, 0x06},
                     {0x08, 0x0A, 0x0C, 0x0E},
                     {0x10, 0x12, 0x14, 0x16},
                     {0x18, 0xA0, 0xC0, 0xE0}};
    ByteArray two = {{0x01, 0x03, 0x05, 0x07},
                     {0x09, 0x0B, 0x0D, 0x0F},
                     {0x11, 0x13, 0x15, 0x17},
                     {0x19, 0xB0, 0xD0, 0xF0}};
    ByteArray result_test = {{0x01, 0x01, 0x01, 0x01},
                             {0x01, 0x01, 0x01, 0x01},
                             {0x01, 0x01, 0x01, 0x01},
                             {0x01, 0x01, 0x01, 0x01}};

//    AES::xor_byte_block(one, two);
    for(size_t i = 0; i < one.size(); i++){
        for(size_t j = 0; j < one[i].size(); j++){
            if(result_test[i][j] != one[i][j]){
                std::cout << "Test_04 FAIL" <<std::endl;
            }
        }
    }
    std::cout << "Test_04 PASS" <<std::endl;
}



int main()
{
    //Функция encode_file()
    //_______________________________________________
    Key* key = new Key("complete", 128); // 1- это path 2- ключа
    AES algorithm(key);
    auto start_time = std::chrono::steady_clock::now();
    ifstream input_stream("7z.exe", ios::in | ios::binary);
    ofstream output_stream("data.bin", ios::out | ios::binary);

    const size_t size_validation = 256;
    char buffer_validation[size_validation + 1];
    std::fill_n(buffer_validation, size_validation + 1, '#');
    input_stream.read(buffer_validation, size_validation);
    buffer_validation[size_validation] = '\0';
    std::string hash = sha512(std::string(buffer_validation, size_validation));
    output_stream.write(hash.data(), hash.size());
    char flag = '%';
    output_stream.write(&flag, 1);
    input_stream.seekg(0, ios::beg);
    size_t size = 16;
    char buffer[size];
    while(!input_stream.eof()){
        input_stream.read(buffer, size);
        std::vector<unsigned char> input(buffer, buffer + input_stream.gcount());
        std::vector<unsigned char> output = algorithm.encrypt(input);
        output_stream.write(reinterpret_cast<char*>(output.data()), size);
    }    
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << elapsed_ns.count() << " ns\n";
    input_stream.close();
    output_stream.close();

    //Функция decode_file()
    // она будет возращать bool. Если обосрались, то возвращаем false
    // переспрашиваешь пароль, поэтому эта функция должна работать, пока не вернет true
    //_______________________________________________
    Key* key2 = new Key("complete", 128);
    AES algorithm_decode(key2);


    start_time = std::chrono::steady_clock::now();
    ifstream input_stream2("data.bin", ios::in | ios::binary);
    const size_t size_hash_data = 128;
    char hash_buffer[size_hash_data + 1];
    std::fill_n(hash_buffer, size_hash_data + 1, '#');
    input_stream2.read(hash_buffer, size_hash_data);
    hash_buffer[size_hash_data] = '\0';
    std::string hash_string(hash_buffer);
    char check_flag = '\0';
    input_stream2.read(&check_flag, 1);
    if(check_flag == '%'){
        const size_t size_buffer = 256;
        const short size_block = 16;
        std::string sssssss;
        for(size_t i = 0; i < size_buffer; i+= size_block){
            char data_buffer[size_block];
            input_stream2.read(data_buffer, size_block);
            std::vector<unsigned char> decode_byte(data_buffer, data_buffer + size_block);
            std::vector<unsigned char> origin_data = algorithm_decode.decrypt(decode_byte);
            sssssss += std::string(origin_data.begin(), origin_data.end());
        }
//        std::string file_hash = sha512(sssssss);
//        std::cout << file_hash <<std::endl;
//        std::cout << hash_string <<std::endl;
        if( sha512(sssssss) != hash_string){
            std::cout << "GO in ASSSSSS" << std::endl;
            return -1;
        }
    }

    input_stream2.seekg(-256, ios::cur); // переделать на запись
    ofstream output_stream2("out7z.exe", ios::out | ios::binary);
    while(!input_stream2.eof()){
        input_stream2.read(buffer, size);
        std::vector<unsigned char> input(buffer, buffer + size);
        std::vector<unsigned char> output = algorithm_decode.decrypt(input);
        output_stream2.write(reinterpret_cast<char*>(output.data()), input_stream2.gcount());
    }
    end_time = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << elapsed_ns.count() << " ns\n";

    input_stream2.close();
    output_stream2.close();
    // Конец decode_file()
    cout << "OK"<< endl;


//    string input = "grape";
//    string output1 = sha512(input);

//    cout << output1 << endl;
//    cout << sha512("grape") << endl;

    test_01();
    test_02();
    test_03();

    return 0;
}
