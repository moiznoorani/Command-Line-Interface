// main.cpp
#include <iostream>
#include <cstring>
#include "commands.h"

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

using namespace std;

void parse(char words[MAX_WORDS][MAX_WORD_LENGTH], int& length) {
    char ch;
    int wordIndex = 0;
    int charIndex = 0;

    cout << "Enter a command (type 'quit' to exit): ";

    while (true) {
        cin.get(ch);

        if (ch == '\n') {
            if (charIndex != 0) {
                words[wordIndex][charIndex] = '\0';
                wordIndex++;
            }
            break;
        }

        if (isspace(ch)) {
            if (charIndex != 0) {
                words[wordIndex][charIndex] = '\0';
                wordIndex++;
                charIndex = 0;
            }
        } else {
            words[wordIndex][charIndex++] = ch;
        }
    }

    length = wordIndex;
}

int main() {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int length = 0;

    while (true) {
        parse(words, length);

        if (length == 0) continue;

        if (strcmp(words[0], "quit") == 0) break;

        if (strcmp(words[0], "help") == 0) {
            displayHelp();
        } else if (strcmp(words[0], "show") == 0 && length > 2 && strcmp(words[1], "file") == 0) {
            showFile(words[2]);
        } else if (strcmp(words[0], "copy") == 0 && length > 2) {
            copyFile(words[1], words[2]);
        } else if (strcmp(words[0], "cd") == 0 && length > 1) {
            changeDirectory(words[1]);
        } else if (strcmp(words[0], "list") == 0) {
            if (length > 1)
                listFiles(words[1]);
            else
                listFiles(".");
        } else if (strcmp(words[0], "run") == 0 && length > 1) {
            runProgram(words[1]);
        } else if (strcmp(words[0], "mkdir") == 0 && length > 1) {
            makeDirectory(words[1]);
        } else if (strcmp(words[0], "pwd") == 0) {
            printWorkingDirectory();
        } else if (strcmp(words[0], "clear") == 0) {
            clearTerminal();
        } else {
            cout << "Unrecognized command. Type 'help' for a list of commands." << endl;
        }

        cout << endl;
    }

    return 0;
}
