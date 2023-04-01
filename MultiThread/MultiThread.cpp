#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

constexpr size_t BUFFER_1MB = 1048576;
constexpr size_t BUFFER_20MB = 20971520;
constexpr size_t BUFFER_4MB = 4299161; //actually 4.1 mb
constexpr size_t BUFFER_4KB = 4096;
constexpr size_t BUFFER_1KB = 1024;
void read_and_write(const string& input_file, const string& output_file) {
    ifstream in_file(input_file);
    stringstream buffer;
    buffer << in_file.rdbuf();
    string file_content = buffer.str();

    ofstream out_file(input_file);
    out_file << file_content;
}
void read_and_write_binary(const string& input_file, const string& output_file) {
    ifstream in_file(input_file, std::ios::binary);
    stringstream buffer;
    buffer << in_file.rdbuf();
    string file_content = buffer.str();

    ofstream out_file(input_file, std::ios::binary);
    out_file << file_content;
}


void read_and_write_nostringstream(const string& input_file, const string& output_file) {
    std::ifstream in_file(input_file, std::ios::binary);
    std::vector<char> buffer((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());

    std::ofstream out_file(output_file, std::ios::binary);
    out_file.write(buffer.data(), buffer.size());
}

void read_and_write_small_buffer(const string& input_file, const string& output_file) {
    std::ifstream in_file(input_file, std::ios::binary);
    std::ofstream out_file(output_file, std::ios::binary);

    char buffer[BUFFER_4KB];

    while (in_file.read(buffer, BUFFER_4KB)) {
        size_t bytes_read = in_file.gcount();
        out_file.write(buffer, bytes_read);
    }
}
void read_and_write_smaller_buffer(const string& input_file, const string& output_file) {
    std::ifstream in_file(input_file, std::ios::binary);
    std::ofstream out_file(output_file, std::ios::binary);

    char buffer[BUFFER_1KB];

    while (in_file.read(buffer, BUFFER_1KB)) {
        size_t bytes_read = in_file.gcount();
        out_file.write(buffer, bytes_read);
    }
}

void read_and_write_big_buffer(const string& input_file, const string& output_file) {
    std::ifstream in_file(input_file, std::ios::binary);
    std::ofstream out_file(output_file, std::ios::binary);

    char* buffer = new char[BUFFER_1MB];

    while (in_file.read(buffer, BUFFER_1MB)) {
        size_t bytes_read = in_file.gcount();
        out_file.write(buffer, bytes_read);
    }
    delete[] buffer;
}

void read_and_write_bigger_buffer(const string& input_file, const string& output_file) {
    std::ifstream in_file(input_file, std::ios::binary);
    std::ofstream out_file(output_file, std::ios::binary);

    char* buffer = new char[BUFFER_20MB];

    while (in_file.read(buffer, BUFFER_20MB)) {
        size_t bytes_read = in_file.gcount();
        out_file.write(buffer, bytes_read);
    }
    delete[] buffer;
}

void read_and_write_4MB_buffer(const string& input_file, const string& output_file) {
    std::ifstream in_file(input_file, std::ios::binary);
    std::ofstream out_file(output_file, std::ios::binary);

    char* buffer = new char[BUFFER_4MB];

    while (in_file.read(buffer, BUFFER_4MB)) {
        size_t bytes_read = in_file.gcount();
        out_file.write(buffer, bytes_read);
    }
    delete[] buffer;
}
//Threaded VERSION:
int main() {
    vector<string> input_files = {
        "TextFiles/file1.txt",
        "TextFiles/file2.txt",
        "TextFiles/file3.txt",
        "TextFiles/file4.txt",
    };

    vector<string> output_files = {
        "TextFiles/output1.txt",
        "TextFiles/output2.txt",
        "TextFiles/output3.txt",
        "TextFiles/output4.txt",
    };
    auto timer1 = high_resolution_clock::now();
    vector<thread> threads;

    //stringstream buffer
    //for (size_t i = 0; i < input_files.size(); ++i) {
    //    threads.push_back(thread(read_and_write, input_files[i], output_files[i]));
    //}
    
    //stringstream buffer binary:
    //for (size_t i = 0; i < input_files.size(); ++i) {
    //    threads.push_back(thread(read_and_write_binary, input_files[i], output_files[i]));
    //}
    
    //4kb buffer:
    //for (size_t i = 0; i < input_files.size(); ++i) {
    //    threads.push_back(thread(read_and_write_small_buffer, input_files[i], output_files[i]));
    //}
    
    //1kb buffer:
    //for (size_t i = 0; i < input_files.size(); ++i) {
    //    threads.push_back(thread(read_and_write_smaller_buffer, input_files[i], output_files[i]));
    //}

    //1MB BUFFER
    //for (size_t i = 0; i < input_files.size(); ++i) {
    //    threads.push_back(thread(read_and_write_big_buffer, input_files[i], output_files[i]));
    //}

    //dynamically allocated vector buffer:
    //for (size_t i = 0; i < input_files.size(); ++i) {
    //    threads.push_back(thread(read_and_write_nostringstream, input_files[i], output_files[i]));
    //}
    //20mb buffer
    /*for (size_t i = 0; i < input_files.size(); ++i) {
        threads.push_back(thread(read_and_write_bigger_buffer, input_files[i], output_files[i]));
    }*/

    //4mb buffer
    for (size_t i = 0; i < input_files.size(); ++i) {
        threads.push_back(thread(read_and_write_4MB_buffer, input_files[i], output_files[i]));
    }
    for (auto& thread : threads) {
        thread.join();
    }
    auto timer2 = high_resolution_clock::now();
    
    auto ms_int = duration_cast<milliseconds>(timer2 - timer1);
    duration<double, std::milli> ms_double = timer2 - timer1;
    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
    return 0;
}
//
////SEQUENTIAL VERSION: 
//int main() {
//    vector<string> input_files = {
//        "TextFiles/file1.txt",
//        "TextFiles/file2.txt",
//        "TextFiles/file3.txt",
//        "TextFiles/file4.txt",
//    };
//
//    vector<string> output_files = {
//        "TextFiles/output1.txt",
//        "TextFiles/output2.txt",
//        "TextFiles/output3.txt",
//        "TextFiles/output4.txt",
//    };
//    auto timer1 = high_resolution_clock::now();
//    vector<thread> threads;
//
//    for (size_t i = 0; i < input_files.size(); ++i) {
//        read_and_write(input_files[i], output_files[i]);
//    }
//
//    auto timer2 = high_resolution_clock::now();
//
//    auto ms_int = duration_cast<milliseconds>(timer2 - timer1);
//    duration<double, std::milli> ms_double = timer2 - timer1;
//    std::cout << ms_int.count() << "ms\n";
//    std::cout << ms_double.count() << "ms\n";
//    return 0;
//}