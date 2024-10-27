// shell.h(This file will contain function declarations and any required macros.)


#ifndef SHELL_H
#define SHELL_H

void display_prompt();
char* read_input();
char** parse_input(char *input);
void execute_command(char **args);
void execute_pipe(char **args1, char **args2);

#endif
