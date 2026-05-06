# NovaShell: Development Log - Phase 1
**Date:** May 7, 2026
**Author:** Tuhin

## Overview
Initiated the development of **NovaShell**, a custom command-line interpreter built in modern C++. The primary objective of Phase 1 was to establish a robust REPL (Read-Eval-Print Loop) architecture, implement input tokenization, and lay the groundwork for process execution using POSIX system calls.

## Architectural Implementation

### 1. Environment Configuration
- Migrated the workspace strictly to the native Linux file system (Ubuntu via WSL2) to resolve cross-OS I/O bottlenecks and permission conflicts.


### 2. Input Parsing (The Tokenizer Module)
- Designed a tokenization engine utilizing `<sstream>` to parse raw user input.
- Converted the input stream into a dynamically sized `std::vector<std::string>`, specifically optimizing the stream extraction (`>>` operator) to safely ignore redundant contiguous whitespaces and avoid null tokens.

### 3. Modular Codebase Design
- Separated concerns by breaking down the logic into multiple files:
  - `main.cpp`: Application entry point.
  - `engine.h`: Function declarations and module blueprints.
  - `engine.cpp`: Core logic implementation containing the REPL loop, string parser, and process executor.

## System Calls & Concurrency

Successfully integrated POSIX OS concepts to manage command execution without terminating the primary shell instance:
- **Process Spawning:** Utilized the `fork()` system call to duplicate the shell environment into a dedicated Child process for secure command execution.
- **Process Synchronization:** Implemented `wait(NULL)` within the Parent process to enforce synchronous execution, preventing output interleaving (race conditions) on `stdout`.
- **Resource Management:** Enforced explicit `exit(0)` commands within the Child scope to prevent recursive REPL loops and eliminate zombie/orphan processes.

## Technical Challenges Mitigated
1. **Concurrency Artifacts:** Fixed an issue where the shell prompt rendered prematurely due to parallel execution. Solved by pausing the parent's execution loop until the child process emitted a termination signal.
2. **Keystroke Traps (Raw Mode):** Encountered ANSI escape sequence interference (e.g., Up-Arrow mapping to `^[[A`) handled incorrectly by standard `std::getline`. Documented for future resolution via the GNU `readline` library.

## Next Phase Objectives
- Transition from simple process printing to actual binary execution.
- Implement the `execvp()` system call, requiring the conversion of C++ `std::string` vectors into C-style null-terminated arrays (`char*[]`) to interface with the Linux kernel.
-