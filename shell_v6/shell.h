// shell.h
#ifndef SHELL_H
#define SHELL_H

#define HISTORY_SIZE 10      // Limit history to 10 commands
#define MAX_JOBS 10          // Maximum number of background jobs
#define MAX_VARS 100         // Maximum number of variables

// Struct to store variables
struct var {
    char *str;               // "name=value" format
    int global;              // 1 for global (environment), 0 for local
};

// Global array and counter for storing variables
extern struct var variables[MAX_VARS];
extern int var_count;

struct Job {
    pid_t pid;              // Process ID of the job
    char *command;          // Command line that started the job
};

// Update the job array and count variables
extern struct Job jobs[MAX_JOBS];
extern int job_count;

void display_prompt();
char* read_input();
char** parse_input(char *input);
void execute_command(char **args, int background);
void setup_signal_handler();
void add_to_history(const char *command);
char* get_history(int index);
void show_history();
int is_builtin(char **args);

// Variable functions
void set_variable(char *name, char *value, int global);
char* get_variable(char *name);
void list_variables();
void unset_variable(char *name);  // Add this line to declare unset_variable
#endif
