// main.c(The main file will handle user input, check for pipes, and call appropriate functions.)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main() {
    char *input;
    char **args;

    while (1) {
        display_prompt();
        input = read_input();

        if (feof(stdin)) {
            printf("\nExiting PUCITshell\n");
            break;
        }

        // Check for pipes in the input
        if (strstr(input, "|") != NULL) {
            char *cmd1 = strtok(input, "|");
            char *cmd2 = strtok(NULL, "|");

            char **args1 = parse_input(cmd1);
            char **args2 = parse_input(cmd2);

            execute_pipe(args1, args2);

            free(args1);
            free(args2);
        } else {
            args = parse_input(input);
            if (args[0] != NULL) {
                execute_command(args);
            }
            free(args);
        }

        free(input);
    }

    return 0;
}
