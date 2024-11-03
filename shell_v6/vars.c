// vars.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

// Array to store variables
struct var variables[MAX_VARS];
int var_count = 0;

// Function to set a variable
void set_variable(char *name, char *value, int global) {
    char *new_var = malloc(strlen(name) + strlen(value) + 2);
    sprintf(new_var, "%s=%s", name, value);

    for (int i = 0; i < var_count; i++) {
        if (strncmp(variables[i].str, name, strlen(name)) == 0 &&
            variables[i].str[strlen(name)] == '=') {
            free(variables[i].str);
            variables[i].str = new_var;
            variables[i].global = global;
            if (global) putenv(new_var); // Set in environment
            return;
        }
    }

    if (var_count < MAX_VARS) {
        variables[var_count].str = new_var;
        variables[var_count].global = global;
        if (global) putenv(new_var);
        var_count++;
    } else {
        fprintf(stderr, "Maximum number of variables reached.\n");
        free(new_var);
    }
}

// Function to get the value of a variable
char* get_variable(char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strncmp(variables[i].str, name, strlen(name)) == 0 &&
            variables[i].str[strlen(name)] == '=') {
            return variables[i].str + strlen(name) + 1;  // Return value part
        }
    }
    // If not found in local variables, check environment variables
    return getenv(name);
}

// Function to list all variables
void list_variables() {
    for (int i = 0; i < var_count; i++) {
        printf("%s\n", variables[i].str);
    }
}
void unset_variable(char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strncmp(variables[i].str, name, strlen(name)) == 0 &&
            variables[i].str[strlen(name)] == '=') {
            free(variables[i].str); // Free the variable's memory

            // Shift all subsequent variables up one position
            for (int j = i; j < var_count - 1; j++) {
                variables[j] = variables[j + 1];
            }
            var_count--; // Reduce count of variables
            return;
        }
    }
    fprintf(stderr, "Variable %s not found\n", name);
}
