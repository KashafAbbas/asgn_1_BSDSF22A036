// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

        // Check if the command is a variable assignment
        char *equals = strchr(input, '=');
        if (equals != NULL) {
            *equals = '\0';  // Split name and value
            char *name = input;
            char *value = equals + 1;
            set_variable(name, value, 0);  // 0 for local variable
            free(input);
            continue;
        }

        // Parse input and replace variables
        args = parse_input(input);
        for (int i = 0; args[i] != NULL; i++) {
            if (args[i][0] == '$') {  // Detect variable usage with $
                char *var_name = args[i] + 1;  // Remove '$' prefix
                char *var_value = get_variable(var_name);
                if (var_value != NULL) {
                    args[i] = strdup(var_value);  // Replace variable with value
                } else {
                    fprintf(stderr, "Variable %s not found\n", var_name);
                }
            }
        }

        if (args[0] != NULL) {
            add_to_history(input);
            execute_command(args, 0);  // Assume foreground execution for simplicity
        }

        free(input);
        free(args);
    }

    return 0;
}
