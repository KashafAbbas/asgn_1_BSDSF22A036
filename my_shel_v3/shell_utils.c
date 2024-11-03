// shell_utils.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

// Display a custom shell prompt
void display_prompt() {
    printf("PUCITshell:- ");
}

// Read a line of input from the user
char* read_input() {
    char *input = NULL;
    size_t len = 0;
    getline(&input, &len, stdin);
    return input;
}

// Parse input string into command and arguments
char** parse_input(char *input) {
    int bufsize = 64, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    token = strtok(input, " \n");
    while (token != NULL) {
        tokens[pos++] = token;
        if (pos >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
        }
        token = strtok(NULL, " \n");
    }
    tokens[pos] = NULL;
    return tokens;
}
