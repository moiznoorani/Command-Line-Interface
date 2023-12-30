#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#define PATH_LENGTH 256
using namespace std;

const int MAX_WORDS = 100; // Maximum number of words
const int MAX_WORD_LENGTH = 50; // Maximum length of each word

/**
 * Parses a line of input into an array of words.
 * 
 * Pre-conditions:
 * - words is a 2 dimensional array of words input
 * - length is an empty integer passed to store the number of words parsed.
 *
 * Post-conditions:
 * - words array contains the parsed words as C strings.
 * - length contains the count of the parsed words.
 * - Function reads user input until a newline character is encountered.
 * - Words are separated by whitespace. Extra whitespaces are ignored.
 */
void parse(char words[MAX_WORDS][MAX_WORD_LENGTH], int& length) {
    char ch;
    int wordIndex = 0;
    int charIndex = 0;

    cout << "Enter a command (type 'quit' to exit): ";

    while (true) {
        cin.get(ch);

        // Break on newline
        if (ch == '\n') {
            if (charIndex != 0) {
                words[wordIndex][charIndex] = '\0'; // Null-terminate the current word
                wordIndex++;
            }
            break;
        }

        // Handle whitespace
        if (isspace(ch)) {
            if (charIndex != 0) { // End of a word
                words[wordIndex][charIndex] = '\0'; // Null-terminate the current word
                wordIndex++;
                charIndex = 0;
            }
        } else {
            // Append character to the current word
            words[wordIndex][charIndex++] = ch;
        }
    }

    length = wordIndex; // Set the length
}

/**
 * Displays help guidelines for the user to know which commands to use.
 *
 * Pre-conditions:
 * - None
 *
 * Post-conditions:
 * - Displays the valid commands along with their descriptions to the console.
 * - Each command and its description is printed on a new line.
 * - The list of commands includes:
 *   - "run executable-file"
 *   - "list"
 *   - "list directory"
 *   - "copy old-filename new-filename"
 *   - "show file filename" // Added command
 *   - "help"
 *   - "quit"
 * - The text is followed by a newline character after each command and description.
 */
void displayhelp() {
    cout << "The valid commands are:" << endl;
    cout << "run executable-file" << endl;
    cout << "list" << endl;
    cout << "list directory" << endl;
    cout << "copy old-filename new-filename" << endl;
    cout << "show file filename" << endl;
    cout << "cd directory" << endl;
    cout << "help" << endl;
    cout << "quit" << endl;
    
}

/**
 * Displays the content of a file.
 *
 * Pre-conditions:
 * - filename is a valid C string containing the name of the file to display.
 *
 * Post-conditions:
 * - Displays the content of the specified file to the console.
 * - If the file cannot be opened, an error message is displayed.
 */
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

/**
 * Copies the content of one file to another.
 *
 * Pre-conditions:
 * - The function is called with valid file paths for both `oldfile` and `newfile`.
 * - The `oldfile` exists and is readable.
 * - The `newfile` can be created or overwritten.
 *
 * Post-conditions:
 * - If the files are opened successfully:
 *   - The content of the `oldfile` is copied to the `newfile`.
 *   - The `infile` and `outfile` streams are closed.
 * - If the files cannot be opened:
 *   - An error message is displayed on the console: "Unable to open files."
 */
void copyFile(const char* oldfile, const char* newfile) {
    // Check if the source file exists and is readable
    ifstream infile(oldfile);
    if (!infile.is_open()) {
        cout << "Error: Unable to open source file '" << oldfile << "'" << endl;
        return;
    }

    // Check if the destination file exists and ask for confirmation to overwrite
    ifstream testfile(newfile);
    if (testfile.is_open()) {
        cout << "Destination file '" << newfile << "' already exists. Do you want to overwrite it? (yes/no): ";
        char response[5];
        cin.getline(response, 5);
        if (strcmp(response, "no") == 0) {
            cout << "Copy operation aborted." << endl;
            return;
        }
    }

    // Open the destination file for writing
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


/**
 * Changes the current working directory to the specified directory.
 *
 * Pre-conditions:
 * - newDir is a valid C string containing the path of the directory to change to.
 * - The length of newDir does not exceed PATH_LENGTH.
 *
 * Post-conditions:
 * - If the current working directory can be successfully obtained:
 *   - The current working directory before the change is printed to the console.
 * - If the directory change is successful:
 *   - The working directory is changed to newDir.
 *   - The path of the new working directory is printed to the console.
 * - If the directory change fails:
 *   - An error message is printed to the standard error stream (perror).
 * - If the new working directory can be successfully obtained:
 *   - The path of the current working directory after the change is printed to the console.
 */
void changeDirectory(const char* newDir) {
    char oldDir[PATH_LENGTH + 1];

    if (getcwd(oldDir, PATH_LENGTH) == NULL) {
        perror("Unable to get current directory");
    }

    cout << "Current directory: " << oldDir << endl;

    if (chdir(newDir) == -1) {
        perror("Unable to change directories");
    }

    cout << "Changed to directory: " << newDir << endl;

    char currentDir[PATH_LENGTH + 1];
    if (getcwd(currentDir, PATH_LENGTH) == NULL) {
        perror("Unable to get current directory");
    }

    cout << "Current directory: " << currentDir << endl;

}


/**
 * Lists the files in the specified directory.
 *
 * Pre-conditions:
 * - directoryPath is a valid C string containing the path of the directory to list.
 *
 * Post-conditions:
 * - If the directory at directoryPath can be opened successfully:
 *   - The names of all files in the directory are printed to the console, each on a new line.
 *   - The directory stream is closed.
 * - If the directory cannot be opened:
 *   - An error message is printed to the standard error stream (cerr).
 */
void listFiles(const char* directoryPath) {
    DIR* dir = opendir(directoryPath);

    if (dir == nullptr) {
        cerr << "Error opening directory" << std::endl;
        return;
    }

    struct dirent* entry;

    while ((entry = readdir(dir)) != nullptr) {
        cout << entry->d_name << std::endl;
    }

    closedir(dir);
}

/**
 * Run a specified program
 * 
 * Preconditions:
 * - programName must be a valid, null-terminated string.
 * - programName should represent a valid executable path on the system.
 *
 * Postconditions:
 * - If the function succeeds:
 *   - A new process is created.
 *   - The specified program is executed in the child process.
 *   - The parent process waits until the child process finishes.
 *   - Returns EXIT_SUCCESS.
 * - If the function fails:
 *   - An error message is printed to standard error.
 *   - No new process is created or the created process did not execute the specified program.
 *   - Returns EXIT_SUCCESS if the failure is in the child process after a successful fork.
 *   - Exits with EXIT_FAILURE if the fork fails.
 */
int runProgram(const char* programName) {
    pid_t p = fork(); // p is non-zero in the parent process and 0 in the child
    if (p == -1) {    // fork() returns -1 if it cannot create a process
        perror("Fork failed.");
        exit(EXIT_FAILURE);
    }

    if (p) {
        if (wait(NULL) == -1) // wait returns the child pid or -1 if error
            perror("Wait interrupted.");
    } else {
        cout<< programName<< endl;
        execl(programName, programName, NULL);
        perror("Execution failed");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}


int main() {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int length = 0;

    while (true) {
        parse(words, length);

        // Check if the first word is "quit"
        if (length > 0 && strcmp(words[0], "quit") == 0) {
            break;
        }

        // Check if the first word is "help"
        if (length > 0 && strcmp(words[0], "help") == 0) {
            displayhelp();
            continue; 
        }

        // Check if the first word is "show" and the second word is "file"
        if (length > 1 && strcmp(words[0], "show") == 0 && strcmp(words[1], "file") == 0) {
            // Check if there is a third word (filename) and display the file content
            if (length > 2) {
                showFile(words[2]);
            } else {
                cout << "Error: Missing filename for 'show file' command" << endl;
            }
            continue; 
        }

        // check if the first word is "copy"
        if (length > 0 && strcmp(words[0], "copy")== 0){
            // pass the 2nd and 3rd name which should be old file and new file to function copy file.
            copyFile(words[1], words[2]);
            continue;
        }
        // check if the first word is "cd"
        if (length >0 && strcmp(words[0], "cd")==0){
            // pass the name of the directory or the second word to a function changedirectory
            changeDirectory(words[1]);
            continue;
        }
        // Check if the command is "list" 
        if (length > 0 && strcmp(words[0], "list") == 0) {
        
            if (length > 1) {
            // If additional arguments are present, call listFiles and pass directory
            listFiles(words[1]);
            } 
            else {
            // If no additional arguments are present, call listFiles without specifying a directory
            listFiles(".");
            }
            continue; 
        }

        if (length > 0 && strcmp(words[0], "run")==0){
            runProgram(words[1]);
            continue;
        }



        // Output the contents of the array and its length
        cout << "Array length: " << length << endl;
        for (int i = 0; i < length; ++i) {
            cout << words[i] << endl;
        }
        cout << endl;
    }

    return 0;
}
