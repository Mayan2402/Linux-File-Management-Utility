# Linux File Management Utility

## Project Description

Linux File Management Utility is a menu-driven C++ application developed for Linux/Ubuntu.

It allows users to perform common file and directory operations through a simple menu.

The project also demonstrates Linux system programming concepts such as file descriptors, file permissions, `lseek()`, `stat()`, `chmod()` and `access()`.

## Objectives

- Perform basic file operations.
- Perform directory operations.
- Search files recursively.
- Display file information.
- Change and check file permissions.
- Demonstrate file descriptors.
- Demonstrate `lseek()`.
- Understand Linux/POSIX system programming.
- Use C++ and Makefile for development.

## Features

1. List Files
2. Create File
3. Read File
4. Write File
5. Append to File
6. Create Directory
7. Remove Directory
8. Delete File
9. Copy File
10. Move File
11. Rename File
12. Search File
13. File Information
14. Change Permissions
15. Check Permissions
16. lseek Demonstration
17. File Descriptor Monitoring
18. Exit

## Technologies Used

- C++17
- Linux / Ubuntu
- g++
- Linux/POSIX System Calls
- Makefile
- Git/GitHub

## System Calls / APIs Used

- `open()`
- `read()`
- `write()`
- `close()`
- `lseek()`
- `stat()`
- `chmod()`
- `access()`

## Project Structure

```text
LinuxFileManager/
│
├── src/
│   ├── main.cpp
│   ├── file_operations.cpp
│   └── file_operations.h
│
├── Makefile
├── README.md
├── docs/
├── screenshots/
└── tests/
