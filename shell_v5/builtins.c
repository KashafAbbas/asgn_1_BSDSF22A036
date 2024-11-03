// builtins.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

// Define jobs array and job count only here
Job jobs[MAX_JOBS];
int job_count = 0;

// Change directory command
int cd_command(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "PUCITshell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("PUCITshell");
        }
    }
    return 1;  // 1 indicates success for built-in
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

// Kill a background job by job ID
int kill_command(int job_id) {
    if (job_id < 1 || job_id > job_count) {
        fprintf(stderr, "Invalid job ID\n");
        return -1;
    }

    pid_t pid = jobs[job_id - 1].pid;
    if (kill(pid, SIGKILL) == 0) {
        printf("Killed job [%d] %d\n", job_id, pid);
        // Remove job from list
        for (int i = job_id - 1; i < job_count - 1; i++) {
            jobs[i] = jobs[i + 1];
        }
        job_count--;
        return 1;
    } else {
        perror("PUCITshell");
        return -1;
    }
}

// Display help for built-in commands
void help_command() {
    printf("Available built-in commands:\n");
    printf("cd <directory> - Change the current directory\n");
    printf("exit           - Exit the shell\n");
    printf("jobs           - List all background jobs\n");
    printf("kill <job_id>  - Terminate a background job by job ID\n");
    printf("help           - Display this help message\n");
}

// Check if a command is built-in
int is_builtin(char **args) {
    if (strcmp(args[0], "cd") == 0) return cd_command(args);
    if (strcmp(args[0], "exit") == 0) { exit_command(); return 1; }
    if (strcmp(args[0], "jobs") == 0) { jobs_command(); return 1; }
    if (strcmp(args[0], "kill") == 0 && args[1] != NULL) {
        int job_id = atoi(args[1]);
        return kill_command(job_id);
    }
    if (strcmp(args[0], "help") == 0) { help_command(); return 1; }
    if (strcmp(args[0], "history") == 0) { show_history(); return 1; }  // Add history command
    return 0;  // Return 0 if not a built-in
}
