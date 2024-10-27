#include <stdio.h>      // Standard I/O functions
#include <stdlib.h>     // Standard library functions, like malloc
#include <unistd.h>     // UNIX standard functions, like fork and exec
#include <string.h>     // String handling functions, like strtok
#include <sys/wait.h>   // For using wait function

// Function to display the custom prompt for the shell
void display_prompt() {
    printf("PUCITshell:- ");
}

// Function to read a line of input from the user
char* read_input() {
    char *input = NULL;
    size_t len = 0;
    // getline allocates memory as needed to read user input
    getline(&input, &len, stdin);
    return input;
}

// Function to parse user input into command and arguments
char** parse_input(char *input) {
    int bufsize = 64, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char*));  // Allocate memory for command and arguments
    char *token;

    // Tokenize the input based on space or newline character
    token = strtok(input, " \n");
    while (token != NULL) {
        tokens[pos++] = token;
        // Reallocate memory if the buffer size is exceeded
        if (pos >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
        }
        token = strtok(NULL, " \n");
    }
    tokens[pos] = NULL;  // Null-terminate the array of arguments
    return tokens;
}

// Function to fork a new process and execute the command
void execute_command(char **args) {
    pid_t pid = fork();  // Create a new process
    if (pid == 0) {
        // Child process executes the command
        if (execvp(args[0], args) == -1) {  // Execute command
            perror("PUCITshell");           // Display error if command fails
        }
        exit(EXIT_FAILURE);                 // Exit child process if execvp fails
    } else if (pid < 0) {
        // Forking error handling
        perror("PUCITshell");
    } else {
        // Parent process waits for the child to finish
        wait(NULL);
    }
}

// Main function that runs the shell loop
int main() {
    char *input;
    char **args;

    // Infinite loop to continuously display prompt, read input, and execute commands
    while (1) {
        display_prompt();               // Show shell prompt
        input = read_input();           // Get user input

        // Check if end-of-file (CTRL+D) is reached
        if (feof(stdin)) {
            printf("\nExiting PUCITshell\n");
            break;
        }

        args = parse_input(input);      // Parse input into command and arguments
        if (args[0] != NULL) {          // If input is not empty, execute command
            execute_command(args);
        }

        free(input);                    // Free memory allocated for input
        free(args);                     // Free memory allocated for arguments
    }

    return 0;  // Exit the program
}
