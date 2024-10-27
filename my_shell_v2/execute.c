// execute.c(This file contains the functions for command execution, input/output redirection, and pipes.)


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

// Function to execute a command with optional redirection
void execute_command(char **args) {
    int in_redirect = 0, out_redirect = 0;
    char *infile = NULL, *outfile = NULL;
    int i = 0;

    // Check for redirection operators
    while (args[i] != NULL) {
        if (strcmp(args[i], "<") == 0) {
            in_redirect = 1;
            infile = args[i + 1];
            args[i] = NULL;
        } else if (strcmp(args[i], ">") == 0) {
            out_redirect = 1;
            outfile = args[i + 1];
            args[i] = NULL;
        }
        i++;
    }

    pid_t pid = fork();
    if (pid == 0) {
        if (in_redirect) {
            int in_fd = open(infile, O_RDONLY);
            if (in_fd < 0) {
                perror("Failed to open input file");
                exit(EXIT_FAILURE);
            }
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }

        if (out_redirect) {
            int out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_fd < 0) {
                perror("Failed to open output file");
                exit(EXIT_FAILURE);
            }
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        if (execvp(args[0], args) == -1) {
            perror("PUCITshell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("PUCITshell");
    } else {
        wait(NULL);
    }
}

// Function to execute two commands connected by a pipe
void execute_pipe(char **args1, char **args2) {
    int pipefd[2];
    pid_t p1, p2;

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return;
    }

    p1 = fork();
    if (p1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        
        if (execvp(args1[0], args1) == -1) {
            perror("PUCITshell");
            exit(EXIT_FAILURE);
        }
    } else if (p1 < 0) {
        perror("Fork failed");
        return;
    }

    p2 = fork();
    if (p2 == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);

        if (execvp(args2[0], args2) == -1) {
            perror("PUCITshell");
            exit(EXIT_FAILURE);
        }
    } else if (p2 < 0) {
        perror("Fork failed");
        return;
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
}
