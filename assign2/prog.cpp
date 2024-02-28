
/**
 * Assignment 2: Simple UNIX Shell
 * @file prog.cpp
 * @author Ben Foltz-Miranda
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your
 * implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

#define MAX_LINE 80  // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[]) {
    // Get first token (command)
    char *token = strtok(command, " \n");

    if (token == nullptr) {
        // No command provided
        return -1;
    }

    int i = 0; // Index of the argument
    while (token != nullptr) {
        token[strcspn(token, "\n")] = '\0';  // Remove newline character from the token

        // Allocate memory for the argument and copy the token into it
        try {
            args[i] = new char[strlen(token) + 1];
        } catch (const std::bad_alloc& e) {
            cout << "Memory allocation failed: " << e.what() << endl;
            return -1;
        }
        strcpy(args[i], token); // Copy the token into the argument array

        i++;
        token = strtok(nullptr, " "); // Get the next argument
    }
    args[i] = nullptr;  // Set the last argument to NULL

    return i; // Return the number of arguments
}

/**
 * @brief Convert the array of arguments to a single string
 *
 * @param args The array of arguments
 * @return The string of arguments
 */
string argsToString(char *args[]) {
    string str;
    for (int i = 0; args[i] != nullptr; i++) {
        if (i != 0) {
            str += " "; // Add a space between arguments
        }
        str += args[i]; // Add the argument to the string
    }
    return str;
}

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your
 * implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[]) {
    char command[MAX_LINE];  // the command that was entered
    char *args[MAX_LINE / 2 + 1];  // hold parsed out command line arguments
    int should_run = 1; /* flag to determine when to exit program */

    vector<string> history;  // Store the history of commands
    bool contains_ampersand;  // Whether the command contains an ampersand

    while (should_run) {
        printf("osh>");
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);
        // Parse the input command
        int num_args = parse_command(command, args);

        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) parent will invoke wait() unless command included &
         */

        if (num_args == -1) {
            cout << "No command" << endl;
            continue;
        } else if (num_args > 0) {
            // Check if the command is "exit"
            if (strcmp(args[0], "exit") == 0) {
                cout << "Exiting..." << endl;
                should_run = 0;
                continue;
            }

            // If the command is "!!", get the last command from the history
            if (strcmp(args[0], "!!") == 0) {
                if (history.empty()) {
                    cout << "No command history found" << endl;
                    continue;
                }
                // Get the last command from the history
                string last_command = history.back();
                // Print the last command
                cout << last_command << endl;
                // Convert the last command to a C-style string
                char *cstr = new char[last_command.length() + 1];
                strcpy(cstr, last_command.c_str());
                // Parse the last command
                num_args = parse_command(cstr, args);
                // Free the C-style string
                delete[] cstr;
            }

            history.push_back(argsToString(args));  // Add the command to the history

            // If the command is "history", print the history of commands
            if (strcmp(args[0], "history") == 0) {
                cout << "History of commands:" << endl;
                for (int i = 0; i < history.size(); i++) {
                    cout << i + 1 << ": " << history[i] << endl;
                }
                continue;
            }

            // Check for background execution (contains ampersand)
            if (strcmp(args[num_args - 1], "&") == 0) { // if last argument is &
                contains_ampersand = true;
                args[num_args - 1] = nullptr; // Remove the ampersand from the arguments list
                num_args--; // Decrement the number of arguments
            } else if (args[num_args - 1][strlen(args[num_args - 1]) - 1] == '&') { // if last character of last argument is &
                contains_ampersand = true;
                args[num_args - 1][strlen(args[num_args - 1]) - 1] = '\0'; // Remove the ampersand from the arguments list
            } else {
                contains_ampersand = false;
            }

            pid_t pid = fork();
            if (pid < 0) {
                cout << "Fork failed" << endl;
                return 1;
            } else if (pid == 0) {
//                cout << "Child process" << endl;

                // Check for output redirection
                for (int i = 0; args[i] != nullptr; i++) {
                    if (strcmp(args[i], ">") == 0) {
                        args[i] = nullptr; // Remove the operator from the arguments list

                        // Open the file for writing
                        int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        dup2(fd, 1); // Redirect stdout to the file
                        close(fd); // Close the original file descriptor

                        args[i + 1] = nullptr; // Remove the file name from the arguments list
                        break;
                    }
                }

                // Loop through the arguments to check for input redirection
                for (int i = 0; args[i] != nullptr; i++) {
                    if (strcmp(args[i], "<") == 0) {
                        args[i] = nullptr; // Remove the operator from the arguments list
                        int fd = open(args[i + 1], O_RDONLY);
                        dup2(fd, STDIN_FILENO); // Redirect stdin to the file
                        close(fd); // Close the original file descriptor
                        args[i + 1] = nullptr; // Remove the file name from the arguments list
                        break;
                    }
                }

                if (execvp(args[0], args) == -1) {
                    cout << "Command not found" << endl;
                    return 1;
                }
            } else {
//                cout << "Parent process" << endl;

                if (!contains_ampersand) {
                    waitpid(pid, nullptr, 0);
                } else {
                    continue;
                }
            }
        }
    }
    return 0;
}
