#include "archive.h"


void create_archive(std::set<std::string> &&data, bool flag_compress,
                    std::string &archive_path, int size)
{

    const int data_size = size;
    Selector selector(data_size);
        selector.set_filesnames(data);
        long total_size = 0;
        long init_size = 1;
    Write_Liner wr;
    wr.TakeFileOut(archive_path);
        wr.BeginWrite();
        while (selector.has_file()) {
            selector.read_file();
            int tmp_size = selector.file_size();
            FileInfo file_header;
            string str = selector.get_filename();
            file_header.AddPath(str);
            file_header.AddSizeFile(selector.file_size());
            wr.TakeHeader(file_header);
        init_size += selector.file_size();
            while (selector.has_data()) {
                char algorithm;
                std::vector<char> compressed_data = selector.get_compressed_data(flag_compress, algorithm);
                selector.next_data();
                wr.TakeBody(&compressed_data, algorithm, selector.has_data());
                total_size += compressed_data.size();
            }
            selector.next_file();

        }
        wr.EndWriting();
}

// ########## Деархивация ##########
void dearchive(std::string path_to_archive)
{
    Selector selector(1024*1024);
    Read_Arch read_arch;
        Recovery_Arch recover;
        char algorithm;
        read_arch.TakeFileIn(path_to_archive);
        if (read_arch.HaveInFile()){
            read_arch.ReadHeader();
            for ( auto i = 0; read_arch.Is_Have_a_file(); i++ ){
                read_arch.ReadFileHead();
                string header = read_arch.Give_Readed_File_Path();
                recover.RecoveryTakePath(header);

                for ( ;read_arch.Is_File_Info_Full();){
                    vector<char> output;
                    /*har algorithm;*/
                    output = selector.get_decompressed_data(read_arch.ReadBodyPath(algorithm), algorithm);
                    recover.RecoveryWrite(&output);

                }
                read_arch.SubtractFile(); // Вместо Recovery
            }
        } else {
            std::cerr << "Нет файла для чтения" << "\n";
        }

        QFile(QString::fromStdString(path_to_archive)).remove(); // Удаление промежуточного (незашифрованного архива)
}




void encrypt_archive(const std::string &path, const std::string &pass)
{
    Key *key = new Key(pass, 128);
    AES algorithm(key);
    size_t size = 16;
    char buffer[size];
    ifstream input_stream(path, std::ios::in | std::ios::binary);
    ofstream output_stream(path + "en", std::ios::out | std::ios::binary);
    while(!input_stream.eof()){
        input_stream.read(buffer, size);
        std::vector<unsigned char> input(buffer, buffer + input_stream.gcount());
        std::vector<unsigned char> output = algorithm.encrypt(input);
        output_stream.write(reinterpret_cast<char*>(output.data()), size);
    }

    input_stream.close();
    output_stream.close();
    QFile(QString::fromStdString(path)).remove(); // Удаление промежуточного (незашифрованного архива)
}

void decrypt_archive(const std::string &path, const std::string &pass)
{
    Key* key = new Key(pass, 128);
       AES algorithm(key);
    ifstream input_stream(path, std::ios::in | std::ios::binary);
        std::string out_path;
        for (int i = 0; i < path.length() - 2; ++i) {
            out_path += path[i];
        }
        ofstream output_stream(out_path, std::ios::out | std::ios::binary);
        size_t size = 16;
        char buffer[size];
        while(!input_stream.eof()){
            input_stream.read(buffer, size);
            std::vector<unsigned char> input(buffer, buffer + size);
            std::vector<unsigned char> output = algorithm.decrypt(input);
            output_stream.write(reinterpret_cast<char*>(output.data()), input_stream.gcount());
        }

        input_stream.close();
        output_stream.close();
}
