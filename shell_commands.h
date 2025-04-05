// shell_commands.h
#ifndef SHELL_COMMANDS_H
#define SHELL_COMMANDS_H

void displayHelp();
void showFile(const char* filename);
void copyFile(const char* oldfile, const char* newfile);
void changeDirectory(const char* newDir);
void listFiles(const char* directoryPath);
int runProgram(const char* programName);
void makeDirectory(const char* dirname);
void printWorkingDirectory();
void clearTerminal();

#endif // SHELL_COMMANDS_H
