#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void read_and_write(const string& input_file, const string& output_file) {
    ifstream in_file(input_file);
    stringstream buffer;
    buffer << in_file.rdbuf();
    string file_content = buffer.str();

    ofstream out_file(output_file);
    out_file << file_content;
}
//Threaded VERSION:
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
//        threads.push_back(thread(read_and_write, input_files[i], output_files[i]));
//    }
//
//    for (auto& thread : threads) {
//        thread.join();
//    }
//    auto timer2 = high_resolution_clock::now();
//    
//    auto ms_int = duration_cast<milliseconds>(timer2 - timer1);
//    duration<double, std::milli> ms_double = timer2 - timer1;
//    std::cout << ms_int.count() << "ms\n";
//    std::cout << ms_double.count() << "ms\n";
//    return 0;
//}

//SEQUENTIAL VERSION: 
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

    for (size_t i = 0; i < input_files.size(); ++i) {
        read_and_write(input_files[i], output_files[i]);
    }

    auto timer2 = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(timer2 - timer1);
    duration<double, std::milli> ms_double = timer2 - timer1;
    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
    return 0;
}