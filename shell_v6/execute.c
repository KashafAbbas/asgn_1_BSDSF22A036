// execute.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include "shell.h"

// Signal handler to prevent zombie processes
void handle_sigchld(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

// Setup the SIGCHLD signal handler
void setup_signal_handler() {
    struct sigaction sa;
    sa.sa_handler = &handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);
}

// Execute a command with optional background execution
void execute_command(char **args, int background) {
    if (is_builtin(args)) return;  // Run if it's a built-in command

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("PUCITshell");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("PUCITshell");
    } else {
        if (!background) {
            waitpid(pid, NULL, 0);  // Wait for foreground process
        } else {
            printf("[Process %d running in background]\n", pid);
        }
    }
}
