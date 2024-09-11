#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100

int execute_command(char *args[]);
int handle_builtin(char *args[]);

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    int should_run = 1;

    while (should_run) {
        char current_path[MAX_INPUT_SIZE];
        getcwd(current_path, sizeof(current_path));

        std::cout << "ash " << current_path << " > ";
        std::cout.flush();

        if (!std::cin.getline(input, sizeof(input))) {
            break; 
        }

        int arg_count = 0;
        char *token = strtok(input, " \t\n");
        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;

            if (arg_count >= MAX_ARGS) {
                std::cerr << "Too many arguments." << std::endl;
                break;
            }

            token = strtok(NULL, " \t\n");
        }
        args[arg_count] = NULL;

        if (arg_count > 0) {
            if (strcmp(args[0], "exit") == 0) {
                should_run = 0;
            } else if (strcmp(args[0], "cd") == 0) {
                if (arg_count != 2) {
                    std::cerr << "Usage: cd <directory>" << std::endl;
                } else {
                    if (chdir(args[1]) != 0) {
                        perror("cd");
                    }
                }
            } else {
                execute_command(args);
            }
        }
    }

    return 0;
}



int execute_command(char *args[]) {
    int i = 0;
    while (arguments[i] != NULL) {
        if (strcmp(args[i], ">") == 0) {
            args[i] = NULL; 
            FILE *output_file = fopen(arguments[i + 1], "w");
            if (!output_file) {
                perror("Output file");
                return 1;
            }
            int file_descriptor = fileno(output_file);
            dup2(file_descriptor, STDOUT_FILENO);
            fclose(output_file);
            break;
        }
        i++;
    }
    pid_t child_pid = fork();
}

int main() {
    while (should_run) {
        if (arg_count > 0) {
            if (execute_command(args) == 0) {
            } else {

            }
        }
    }

    return 0;
}
