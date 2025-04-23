# Simple Shell

Welcome to our **Simple Shell** project 👋  
This project is part of the low-level programming curriculum at Holberton School.  
The goal is to build our own simple UNIX command-line interpreter (shell) that mimics some functionalities of `/bin/sh`.

---

## 📚 Description

This shell reads commands from the standard input and executes them just like a regular shell.  
It supports both **interactive** and **non-interactive** modes. It handles execution of simple commands using system calls like `fork`, `execve`, `wait`, and more.  
It also supports a few **built-in commands** such as `exit`, `env`, and handles `$PATH` lookups.

---

## 🔧 How to Use

- Compilation
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
Interactive Mode
- Interactvie Mode 
    ./hsh
- Non-Interactvie Mode 
    echo "ls -l" | ./hsh
