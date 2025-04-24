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
## 📂 Project Structure

File | Description
main.c | Entry point, main loop for reading and executing commands
prompt.c | Handles the shell prompt and command input
executor.c | Contains logic for command execution (fork, execve, etc.)
builtins.c | Implements built-in commands like exit and env
path.c | Manages environment variables and command path resolution
utils.c | Helper functions for strings and memory management
errors.c | Error printing and handling
free.c | Frees memory allocations

## ⚙️  Functions Used


Here are the core functions implemented across the files:

_getline – read a line of input
parse_command – tokenize input into arguments
execute_command – fork and execute input command
_getenv – custom getenv function to retrieve environment variables
check_path – search and resolve the correct path of commands
is_builtin – check if command is a builtin
exit_shell – exit shell built-in
print_env – env built-in
free_args, free_env – memory management utilities
_strdup, _strcmp, _strcat, _strlen – string handling

## 📊 Flowchart Shell

![Shell Flowchart](https://github.com/muniira-03/holbertonschool-simple_shell/blob/main/flowchart.png?raw=true)

##👥 Authors
 - @muniira-03
 - @ShAlabbadi


