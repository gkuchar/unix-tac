// hftac-naive.cpp
//
// Student TODO:
//   Implement a naive reverse-line printer.
//
// Required behavior:
//   ./hftac-naive <input_file>
//
// Suggested approach:
//   1. Open the file with std::ifstream
//   2. Read every line using std::getline
//   3. Store the lines in std::vector<std::string>
//   4. Print them in reverse order
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
#endif


//================================================================
// Function Prototypes
//================================================================


//================================================================
// Main Function
//================================================================
int main(int argc, char* argv[]) {
    (void)argc; // suppress unused parameter warning - you will need to use argc and argv to parse command line arguments
    (void)argv; // you can remove these lines once you start using argv and argc

    std::cerr << "TODO: implement hftac-naive in src/hftac-naive.cpp\n";
    return 1; // return non-zero to indicate failure until you implement your program
}