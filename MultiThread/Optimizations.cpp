#include <future>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

constexpr size_t BUFFER_1MB = 1048576;

std::future<void> read_and_write_async(const string& input_file, const string& output_file) {
    return async(launch::async, [input_file, output_file]() {
        ifstream in_file(input_file, ios::binary);
        ofstream out_file(output_file, ios::binary);

        char* buffer = new char[BUFFER_1MB];

        while (in_file.read(buffer, BUFFER_1MB)) {
            size_t bytes_read = in_file.gcount();
            out_file.write(buffer, bytes_read);
        }

        delete[] buffer;
        });
}

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
    vector<future<void>> futures;

    for (size_t i = 0; i < input_files.size(); ++i) {
        futures.push_back(read_and_write_async(input_files[i], output_files[i]));
    }

    for (auto& future : futures) {
        future.wait();
    }

    auto timer2 = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(timer2 - timer1);
    duration<double, std::milli> ms_double = timer2 - timer1;
    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
    return 0;
}
