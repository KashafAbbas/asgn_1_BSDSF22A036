// shell.h
#ifndef SHELL_H
#define SHELL_H

#define HISTORY_SIZE 10  // Limit history to 10 commands

void display_prompt();
char* read_input();
char** parse_input(char *input);
void execute_command(char **args, int background);
void setup_signal_handler();
void add_to_history(const char *command);
char* get_history(int index);
void show_history();

#endif
