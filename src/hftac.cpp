// hftac.cpp
// 
// Required behavior:
//   ./hftac <input_file>
//   ./hftac --block-size n <input_file>


//================================================================
// Includes and defines
//================================================================
#if defined (__cpp_modules) && defined (USE_MODULES) // this is new for C++20
import std;
#else // if modules are not supported, include the necessary headers here
#include <iostream>
#include <fcntl.h>      // open(), O_RDONLY
#include <unistd.h>     // read(), write(), close(), lseek()
#include <algorithm> // reverse
#include <vector>
#include <cstring>
#endif


//================================================================
// Function Prototypes
//================================================================
int block_size = 4096;
int size_specified = 0;
int check_block_arg(char* arg);
int reverse_print(std::vector<char> &v);

//================================================================
// Auxillary Function
//================================================================
int check_block_arg(char* arg) {
    for (int i = 0; i < (int)strlen(arg); i++) {
        if (!isdigit(arg[i])) {
            return 1;
        }
    }
    return 0;
}

int reverse_print(std::vector<char> &v) {
    if (!v.empty()) {
        std::reverse(v.begin(), v.end());
        int bytes_written = write(1, v.data(), v.size());
        return bytes_written;
    }
    return 0;
}


//================================================================
// Main Function
//================================================================
int main(int argc, char* argv[]) {

    if (argc < 2 || argc == 3 || argc > 4) {
        std::cerr << "Required usage:\n./hftac [--block-size n] <input_file>\nor\n./hftac <input_file>\n";
        return 1;
    }

    if (argc == 4) {
        if ((check_block_arg(argv[2])|| atoi(argv[2]) < 1)) {
            std::cerr << "Block size argument must be a positive integer\n";
            return 1;
        }
        else {
            block_size = atoi(argv[2]);
            size_specified = 1;
        }
    }

    const char* filename = size_specified ? argv[3] : argv[1];
    int file_fd = open(filename, O_RDONLY);
    if (file_fd == -1) {
        std::cerr << "Error opening file: " << filename << "\n";
        return 1;
    }

    off_t curr = lseek(file_fd, 0, SEEK_END);

    if ((int)curr == 0) {
        return 0;
    }
    
    std::vector<char> buf(block_size);
    std::vector<char> flush;
    int bytes_read;

    while ((int)curr > 0) {
        if (curr < block_size) {block_size = curr; }

        curr -= block_size;
        curr = lseek(file_fd, curr, SEEK_SET);
        bytes_read = read(file_fd, buf.data(), block_size);
        if (bytes_read == -1) {
            std::cerr << "Error reading into buffer\n";
            close(file_fd);
            return 1;
        }

        for (int i = bytes_read - 1; i >= 0; i--) {
            if (buf[i] == '\n') {
                if (reverse_print(flush) == -1) {
                    std::cerr << "Error writing into std out\n";
                    close(file_fd);
                    return 1;
                }
                flush.clear();
                flush.push_back('\n');
            } else {
                flush.push_back(buf[i]);
            }
        }
    }
    reverse_print(flush);

    if (close(file_fd) == -1) {
        std::cerr << "Error closing file:" << filename << "\n";
        return 1;
    }

    return 0;
}