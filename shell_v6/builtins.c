// builtins.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

// Define jobs array and job count
struct Job jobs[MAX_JOBS];  // Make sure this is defined as per the struct
int job_count = 0;          // Initialize job count to zero

// Change directory command
int cd_command(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "PUCITshell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("PUCITshell");
        }
    }
    return 1;  // Success for built-in
}

// Exit the shell
void exit_command() {
    printf("Exiting PUCITshell\n");
    exit(0);
}

// List background jobs
void jobs_command() {
    for (int i = 0; i < job_count; i++) {
        printf("[%d] %d %s\n", i + 1, jobs[i].pid, jobs[i].command);
    }
}

// Display help for built-in commands
void help_command() {
    printf("Available built-in commands:\n");
    printf("cd <directory> - Change the current directory\n");
    printf("exit           - Exit the shell\n");
    printf("jobs           - List all background jobs\n");
    printf("help           - Display this help message\n");
}

// Check if a command is built-in
int is_builtin(char **args) {
    if (strcmp(args[0], "cd") == 0) return cd_command(args);
    if (strcmp(args[0], "exit") == 0) { exit_command(); return 1; }
    if (strcmp(args[0], "jobs") == 0) { jobs_command(); return 1; }
    if (strcmp(args[0], "help") == 0) { help_command(); return 1; }
    if (strcmp(args[0], "export") == 0) { 
        if (args[1] != NULL) {
            char *name = strtok(args[1], "=");
            char *value = strtok(NULL, "=");
            set_variable(name, value, 1); // Set as global
        }
        return 1;
    }
    if (strcmp(args[0], "unset") == 0) {
        if (args[1] != NULL) {
            unset_variable(args[1]);
        }
        return 1;
    }
    if (strcmp(args[0], "list_variables") == 0) { 
        list_variables();
        return 1;
    }
    return 0;  // Not a built-in
}
