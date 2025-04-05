# 🖥️ C++ Command Shell

A lightweight command-line shell written in C++ that supports basic Unix-like commands and demonstrates process control, file operations, and directory management.

---

## 🔧 Features

- `run <executable>` – Run an external executable program
- `list` or `list <directory>` – List contents of current or specified directory
- `cd <directory>` – Change the current working directory
- `copy <source> <destination>` – Copy contents of one file to another
- `show file <filename>` – Display contents of a file
- `mkdir <directory>` – Create a new directory
- `pwd` – Print the current working directory
- `clear` – Clear the terminal screen
- `help` – Show available commands
- `quit` – Exit the shell

---

## 📁 Project Structure

```
cppshell/
├── Makefile
├── README.md
├── main.cpp
├── shell_commands.cpp
└── shell_commands.h
```

---

## 🧪 How to Compile & Run

### 🔨 Compile
```bash
make
```

### 🚀 Run
```bash
make run
```

### 🧼 Clean Build Files
```bash
make clean
```

---

## 📷 Example Usage
```
Enter a command (type 'quit' to exit): pwd
/home/user/cppshell

Enter a command: list
Makefile
README.md
main.cpp
shell_commands.cpp
shell_commands.h

Enter a command: copy notes.txt backup.txt
File copied successfully.

Enter a command: run ./hello
Hello from external program!
```

## ✍️ Author
**Moiz Noorani**  
[GitHub Profile](https://github.com/moiznoorani)
