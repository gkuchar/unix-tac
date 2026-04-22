# hftac — Block-Based Backward File Reader

A C++ implementation of the Unix `tac` utility, exploring tradeoffs between naive and block-based I/O strategies using low-level POSIX system calls. Built for an Operating Systems course at TCU.

## Overview

Two implementations of reverse-line file printing, benchmarked against the system `tac`:

- **`hftac-naive`** — loads the entire file into memory via `std::ifstream`, reverses a line vector.
- **`hftac`** — reads the file backward in fixed-size blocks using `open()`, `lseek()`, `read()`, `close()`. Handles line reconstruction across block boundaries. Supports a configurable `--block-size n` flag.

## Benchmark Results

Tested on files of increasing size. Runtime measured via `/usr/bin/time`.

| Implementation         | 10 KB | 1 MB  | 50 MB   |
|------------------------|-------|-------|---------|
| `hftac-naive`          | 0 ms  | 10 ms | 290 ms  |
| `hftac` (n = 4096)     | 0 ms  | 20 ms | 1020 ms |
| `hftac` (n = 1024)     | 0 ms  | 20 ms | 1070 ms |
| `hftac` (n = 65536)    | 0 ms  | 20 ms | 1400 ms |
| `hftac` (n = 64)       | 0 ms  | 50 ms | 2340 ms |
| system `tac`           | 0 ms  | 0 ms  | 80 ms   |

## Key Finding: Output Syscalls Dominate

The block-based implementation is *slower* than the naive one, despite being the "optimized" version. Root cause: `hftac` calls `write()` once per line, resulting in O(lines) kernel-mode transitions. The naive implementation uses `std::cout`, which batches writes through an internal userspace buffer.

**Takeaway:** For this workload, output buffering matters more than input strategy. The system `tac` outperforms both because it relies on stdio's internal output buffering, reducing `write()` calls to O(file_size / buffer_size).

## Block Size Sensitivity

Block size exhibits a clear sweet spot at 4096 bytes (the typical page size):
- **Too small (n=64)** — syscall overhead from excessive `lseek()` + `read()` calls compounds with the existing per-line `write()` cost.
- **Too large (n=65536)** — cache inefficiency from operating on oversized chunks.

## Complexity Analysis

| Implementation | Time | Space |
|----------------|------|-------|
| `hftac-naive`  | O(N) lines | O(N) lines (full file in memory) |
| `hftac`        | O(N) bytes | O(N) bytes worst case (single-line file) |

## Proposed Optimization

Introducing a fixed-size output buffer between the `flush` vector and `write()` would reduce syscalls from O(lines) to O(file_size / output_buffer_size), independent of input block size. This is the standard pattern used by stdio and the system `tac`.

## Build & Run

```bash
make
./hftac <input_file>
./hftac --block-size 8192 <input_file>
./hftac-naive <input_file>
```

## Tech

C++20, POSIX I/O (`<fcntl.h>`, `<unistd.h>`), GNU Make.