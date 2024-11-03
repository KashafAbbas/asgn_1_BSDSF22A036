// shell.h
#ifndef SHELL_H
#define SHELL_H

#define HISTORY_SIZE 10  // Limit history to 10 commands
#define MAX_JOBS 10      // Maximum number of background jobs

// Job structure for background processes
typedef struct {
    pid_t pid;
    char command[256];
} Job;

extern Job jobs[MAX_JOBS];     // Declare jobs array globally
extern int job_count;          // Declare job count globally

void display_prompt();
char* read_input();
char** parse_input(char *input);
void execute_command(char **args, int background);
void setup_signal_handler();
void add_to_history(const char *command);
char* get_history(int index);
void show_history();

// Built-in command functions
int cd_command(char **args);
void exit_command();
void jobs_command();
int kill_command(int job_id);
void help_command();

// Check if a command is built-in
int is_builtin(char **args);  // Declare is_builtin here

#endif
