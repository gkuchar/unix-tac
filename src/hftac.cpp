// hftac.cpp
//
// Student TODO:
//   Implement a block-based reverse-line printer using low-level POSIX I/O.
//
// Required behavior:
//   ./hftac <input_file>
//   ./hftac --block-size n <input_file>
//
// Requirements:
//   - use open(), read(), lseek(), and close()
//   - read the file backward in fixed-size blocks
//   - detect '\n' characters and reconstruct lines in reverse order
//   - correctly handle lines that span multiple blocks
//   - default block size is 4096 bytes
//   - support an optional flag: --block-size n
//
// Suggested strategy:
//   1. Parse the command line.
//      - default block size = 4096
//      - if --block-size n is present, validate n and use it
//      - determine the input file name
//   2. Open the file and determine its size.
//   3. Move backward from the end in fixed-size blocks.
//   4. Scan each block from right to left looking for '\n'.
//   5. Keep a buffer for the partial line that crosses a block boundary.
//   6. Print complete lines as soon as you reconstruct them.
//
// Constraints:
//   - assume input is a regular file
//   - do not read the whole file into memory
//   - match the output of the system `tac`
//   - your program should work with different block sizes


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

    std::cerr << "TODO: implement hftac in src/hftac.cpp\n";
    std::cerr << "Required usage: ./hftac [--block-size n] <input_file>\n";
    
    return 1; // return non-zero to indicate failure until you implement your program
}