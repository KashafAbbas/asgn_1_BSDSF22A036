// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main() {
    char *input;
    char **args;

    // Set up the signal handler to prevent zombie processes
    setup_signal_handler();

    // Main loop to read commands
    while (1) {
        display_prompt();
        input = read_input();

        if (feof(stdin)) {
            printf("\nExiting PUCITshell\n");
            break;
        }

        // Handle history commands
        if (strcmp(input, "history\n") == 0) {
            show_history();
            free(input);
            continue;
        } else if (input[0] == '!' && input[1] != '\0') {
            int index = atoi(&input[1]);  // Convert "number" to int
            char *command = get_history(index);
            if (command != NULL) {
                free(input);
                input = strdup(command);  // Repeat command
                printf("%s\n", input);    // Show the repeated command
            } else {
                free(input);
                continue;
            }
        }

        // Check if the command ends with '&' for background execution
        int background = 0;
        char *ampersand = strchr(input, '&');
        if (ampersand != NULL) {
            background = 1;
            *ampersand = '\0';  // Remove '&' from the command
        }

        args = parse_input(input);
        if (args[0] != NULL) {
            add_to_history(input);  // Add command to history
            execute_command(args, background);
        }

        free(input);
        free(args);
    }

    return 0;
}
