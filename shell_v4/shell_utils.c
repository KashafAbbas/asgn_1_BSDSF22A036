// shell_utils.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

// Array to store the last 10 commands
static char *history[HISTORY_SIZE];
static int history_count = 0;  // Total number of commands entered

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

// Add a command to history, overwrite oldest if necessary
void add_to_history(const char *command) {
    // Ensure only non-empty commands are added
    if (strlen(command) > 1) {
        if (history_count >= HISTORY_SIZE) {
            free(history[0]);  // Free memory of oldest command
            // Shift all commands one position left
            for (int i = 1; i < HISTORY_SIZE; i++) {
                history[i - 1] = history[i];
            }
            history[HISTORY_SIZE - 1] = strdup(command);
        } else {
            history[history_count++] = strdup(command);
        }
    }
}

// Retrieve a command from history by index (1-based)
char* get_history(int index) {
    if (index < 1 || index > history_count) {
        printf("No command at that index\n");
        return NULL;
    }
    return history[index - 1];
}

// Show all commands in history
void show_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d %s\n", i + 1, history[i]);
    }
}
