# 🚀 NovaShell: A Custom Unix-like Shell

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%28POSIX%29-lightgrey.svg)
![Status](https://img.shields.io/badge/Status-In%20Development-yellow.svg)

## 📌 Project Description
NovaShell is a minimalist, custom command-line interpreter (CLI) built entirely from scratch in C++. This project is a deep dive into Operating System internals, designed to understand how standard shells like `bash` or `zsh` interact with the Linux kernel. 

The primary goal is to master the POSIX API, process management, and the core **Read-Parse-Execute** architectural loop of a system shell.

## 🎯 Core Objectives & Learning Outcomes
*   **Process Management:** Utilizing system calls like `fork()`, `execvp()`, and `waitpid()` to spawn and manage child processes.
*   **String Parsing:** Developing a robust tokenizer to handle user inputs, commands, and arguments efficiently.
*   **System Calls:** Interacting directly with the Linux kernel without relying on heavy external libraries.
*   **Memory Management:** Writing memory-safe and optimized C++ code suitable for a system-level environment.

## ⚙️ Planned Features (Roadmap)
- [x] **Level 1:** Core REPL loop (Read-Eval-Print Loop) and basic input parsing (Tokenizer).
- [ ] **Level 2:** Execution of standard external binaries (e.g., `ls`, `pwd`, `mkdir`).
- [ ] **Level 3:** Implementation of Built-in commands (e.g., `cd`, `exit`, `help`).
- [ ] **Level 4:** Advanced mechanics like background process execution (`&`), custom prompt aesthetics, and signal handling (`Ctrl+C` interruption prevention).

## 🛠️ Tech Stack
*   **Language:** C++ (Modern C++ principles)
*   **Environment:** Linux (Arch Linux preferred), POSIX API
*   **Compiler:** GCC / G++

## 🚀 How to Build and Run
*(Instructions will be updated as the project progresses)*
```bash
# Compile the source code
g++ main.cpp -o novashell

# Execute the shell
./novashell
