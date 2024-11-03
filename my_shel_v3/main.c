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

        // Check if the command ends with '&' for background execution
        int background = 0;
        char *ampersand = strchr(input, '&');
        if (ampersand != NULL) {
            background = 1;
            *ampersand = '\0';  // Replace '&' with null terminator to remove it from the command
        }

        args = parse_input(input);
        if (args[0] != NULL) {
            execute_command(args, background);
        }

        free(input);
        free(args);
    }

    return 0;
}
