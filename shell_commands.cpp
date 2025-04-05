// commands.cpp
#include "commands.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <sys/wait.h>

#define PATH_LENGTH 256

using namespace std;

void displayHelp() {
    cout << "The valid commands are:" << endl;
    cout << "run executable-file" << endl;
    cout << "list" << endl;
    cout << "list directory" << endl;
    cout << "copy old-filename new-filename" << endl;
    cout << "show file filename" << endl;
    cout << "cd directory" << endl;
    cout << "mkdir directory-name" << endl;
    cout << "pwd" << endl;
    cout << "clear" << endl;
    cout << "help" << endl;
    cout << "quit" << endl;
}

void showFile(const char* filename) {
    ifstream file(filename);
    if (file.is_open()) {
        cout << "Contents of file '" << filename << "':" << endl;
        char ch;
        while (file.get(ch)) {
            cout << ch;
        }
        cout << endl;
        file.close();
    } else {
        cout << "Error: Unable to open file '" << filename << "'" << endl;
    }
}

void copyFile(const char* oldfile, const char* newfile) {
    ifstream infile(oldfile);
    if (!infile.is_open()) {
        cout << "Error: Unable to open source file '" << oldfile << "'" << endl;
        return;
    }

    ifstream testfile(newfile);
    if (testfile.is_open()) {
        cout << "Destination file '" << newfile << "' already exists. Overwrite? (yes/no): ";
        string response;
        getline(cin, response);
        if (response != "yes") {
            cout << "Copy aborted." << endl;
            return;
        }
    }

    ofstream outfile(newfile);
    if (!outfile) {
        cout << "Error: Unable to open destination file '" << newfile << "'" << endl;
        return;
    }

    char ch;
    while (infile.get(ch)) {
        outfile.put(ch);
    }

    cout << "File copied successfully." << endl;
    infile.close();
    outfile.close();
}

void changeDirectory(const char* newDir) {
    char oldDir[PATH_LENGTH + 1];
    if (getcwd(oldDir, PATH_LENGTH) == NULL) {
        perror("Unable to get current directory");
    } else {
        cout << "Current directory: " << oldDir << endl;
    }

    if (chdir(newDir) == -1) {
        perror("Unable to change directories");
    } else {
        char currentDir[PATH_LENGTH + 1];
        if (getcwd(currentDir, PATH_LENGTH) != NULL) {
            cout << "Changed to directory: " << currentDir << endl;
        } else {
            perror("Unable to get current directory");
        }
    }
}

void listFiles(const char* directoryPath) {
    DIR* dir = opendir(directoryPath);
    if (dir == nullptr) {
        cerr << "Error opening directory" << endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        cout << entry->d_name << endl;
    }
    closedir(dir);
}

int runProgram(const char* programName) {
    pid_t p = fork();
    if (p == -1) {
        perror("Fork failed.");
        exit(EXIT_FAILURE);
    }

    if (p) {
        if (wait(NULL) == -1)
            perror("Wait interrupted.");
    } else {
        execl(programName, programName, NULL);
        perror("Execution failed");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

void makeDirectory(const char* dirname) {
    if (mkdir(dirname, 0755) == 0) {
        cout << "Directory created: " << dirname << endl;
    } else {
        perror("mkdir failed");
    }
}

void printWorkingDirectory() {
    char cwd[PATH_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cout << cwd << endl;
    } else {
        perror("getcwd() error");
    }
}

void clearTerminal() {
    cout << "\033[2J\033[1;1H"; // ANSI escape code
}
