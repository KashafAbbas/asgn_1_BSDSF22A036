// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"

int main() {
    char *input;
    char **args;

    setup_signal_handler();  // Prevent zombie processes

    while (1) {
        display_prompt();
        input = read_input();

        if (feof(stdin)) {
            printf("\nExiting PUCITshell\n");
            break;
        }

        // Check if the command starts with '!' to repeat a previous command
        if (input[0] == '!' && isdigit(input[1])) {
            int history_index = atoi(&input[1]);  // Convert the number after '!' to an integer
            char *history_command = get_history(history_index);
            if (history_command != NULL) {
                free(input);  // Free the old input
                input = strdup(history_command);  // Replace input with the retrieved history command
                printf("%s\n", input);  // Print the repeated command
            } else {
                free(input);
                continue;  // If no command found in history, continue to next loop iteration
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
