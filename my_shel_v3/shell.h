// shell.h
#ifndef SHELL_H
#define SHELL_H

void display_prompt();
char* read_input();
char** parse_input(char *input);
void execute_command(char **args, int background);
void setup_signal_handler();

#endif
