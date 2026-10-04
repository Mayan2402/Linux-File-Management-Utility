# 🗂️ Linux File Management Utility

A command-line based file management utility developed in **C++17 for Linux/Ubuntu**.

This project demonstrates Linux system programming concepts by performing file and directory operations using **Linux/POSIX system calls, file descriptors, permissions, file metadata, and low-level file handling**.

---

## 📌 Project Overview

The **Linux File Management Utility** provides a simple menu-driven interface for managing files and directories from the Linux terminal.

Instead of depending only on high-level C++ file-handling libraries, the project demonstrates how Linux system calls such as `open()`, `read()`, `write()`, `lseek()`, `stat()`, `chmod()`, and `access()` can be used to interact directly with the operating system.

The project is designed to provide practical understanding of:

- Linux file management
- POSIX system calls
- File descriptors
- File permissions
- Directory management
- File metadata
- File positioning
- Recursive file searching
- Linux process file descriptors
- C++ Object-Oriented Programming

---

# ✨ Features

The application provides the following operations:

| Option | Feature | Description |
|-------:|---------|-------------|
| 1 | List Files | Display files and directories |
| 2 | Create File | Create a new file |
| 3 | Read File | Read and display file contents |
| 4 | Write File | Write content to a file |
| 5 | Append to File | Add content to an existing file |
| 6 | Create Directory | Create a new directory |
| 7 | Remove Directory | Remove an existing directory |
| 8 | Delete File | Delete a file |
| 9 | Copy File | Copy data from one file to another |
| 10 | Move File | Move a file to another location |
| 11 | Rename File | Rename an existing file |
| 12 | Search File | Search for a file |
| 13 | File Information | Display file metadata |
| 14 | Change Permissions | Modify file permissions |
| 15 | Check Permissions | Check read, write and execute permissions |
| 16 | lseek Demonstration | Demonstrate file positioning |
| 17 | File Descriptor Monitoring | Display file descriptors associated with the process |
| 18 | Exit | Exit the application |

---

# 🛠Technologies Used

### Programming Language
- **C++17**

### Operating System
- **Linux / Ubuntu**

### Development Tools
- GNU G++
- Make
- Git
- GitHub
- GNU Nano / VS Code

### System Programming
- POSIX System Calls
- File Descriptors
- Linux File System

---

#  Linux/POSIX System Calls

The project demonstrates important Linux system calls including:

```text
open()
read()
write()
close()
lseek()
stat()
chmod()
access()
mkdir()
rmdir()
unlink()
rename()
