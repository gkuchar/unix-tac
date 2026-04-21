// hftac-naive.cpp
//
//
// Required behavior:
//   ./hftac-naive <input_file>
//
//
// Notes:
//   - Match the output of the system `tac` command.
//   - Pay attention to whether the original file ends with a newline.


//================================================================
// Includes and defines
//================================================================
#if defined (__cpp_modules) && defined (USE_MODULES) // this is new for C++20
import std;
#else // if modules are not supported, include the necessary headers here
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#endif


//================================================================
// Function Prototypes
//================================================================
std::vector<std::string> lines;

//================================================================
// Main Function
//================================================================
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./hftac-naive <input_file>";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    file.seekg(0, std::ios::end);
    bool isEmpty = (file.tellg() == 0);
    if (isEmpty) {
        file.close();
        return 0;
    }
    file.seekg(-1, std::ios::end);
    char last;
    file.get(last);
    bool trailingNewline = (last == '\n');
    file.seekg(0, std::ios::beg);
    
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    for(int i = (int)lines.size() - 1; i > -1; i--) {
        if (i != 0) {
            std::cout << lines.at(i) << "\n";
        }
        else {
            line = lines.at(0);
            std::cout << line;
            if (trailingNewline) {
                std::cout << "\n";
            }
        }
    }

    file.close();


    return 0;
}