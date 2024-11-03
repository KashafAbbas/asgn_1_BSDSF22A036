# UNIX Shell Project

### Author
- **Name**: Kashaf Abbas
- **GitHub Username**: KashafAbbas

### Project Overview
This project is a custom UNIX shell implemented as part of the assignment for the Operating Systems course. It includes features for command execution, process handling, and variable management. The shell also supports additional functionalities like built-in commands, input/output redirection, piping, and user-defined variables.

---

## Code Status
The shell has been fully implemented through six versions, each introducing new features to progressively build the functionality. Below are the details of the implementation status:

- **Version 01**: Basic shell prompt and command execution.
- **Version 02**: Added basic parsing to handle arguments with commands.
- **Version 03**: Enabled background process handling using the `&` symbol.
- **Version 04**: Added command history to allow users to repeat previous commands using `!number`.
- **Version 05**: Implemented built-in commands (`cd`, `exit`, `jobs`, `kill`, `help`).
- **Version 06**: Introduced support for user-defined (local) variables and environment variables.

**Code Status**: The code is functional and passes all intended use cases, though some bugs and limitations remain.

---

## Features Implemented

### Core Features
1. **Prompt and Command Execution**: Basic command-line interface with prompt and command execution.
2. **Argument Parsing**: Commands with multiple arguments are parsed and executed correctly.
3. **Background Process Management**: Commands followed by `&` run as background processes.
4. **Command History**: Stores up to 10 previous commands, accessible with `!number`.
5. **Built-In Commands**:
   - `cd`: Change the current working directory.
   - `exit`: Exit the shell.
   - `jobs`: List all background processes.
   - `kill`: Terminate a specific background job.
   - `help`: Display available built-in commands.
6. **User-Defined Variables**: Support for setting, retrieving, and listing local variables using `name=value` syntax.
7. **Environment Variables**: Access and modify environment variables.

### Additional Features
- **Input Redirection**: Allows commands to read input from a file using `<`.
- **Output Redirection**: Allows commands to write output to a file using `>`.
- **Piping**: Supports connecting the output of one command to the input of another using `|`.

---

## Known Bugs & Limitations
1. **Variable Deletion**: Currently, there is no mechanism to unset or delete user-defined variables.
2. **Error Handling**: Error messages may not always be specific, especially for syntax errors in complex commands.
3. **Multiple Redirections**: The shell does not support multiple input or output redirections in a single command (e.g., `command < input > output`).
4. **Multiple Piping**: Limited support for multiple pipes in a single command (e.g., `command1 | command2 | command3` may not work as expected).

---

## Acknowledgments

This project was completed using resources from the course materials, online forums, and documentation. The following sources provided guidance and inspiration:

- [GeeksforGeeks](https://www.geeksforgeeks.org): Helped with basic shell implementation techniques and understanding of processes.
- [GNU C Library Documentation](https://www.gnu.org/software/libc/manual/): Provided in-depth details on UNIX system calls.
- [Stack Overflow](https://stackoverflow.com): Assisted with troubleshooting specific errors related to process management and variable handling.
- **Operating Systems Course** – Special thanks to **Arif@PUCIT** and course TAs for their guidance and support throughout the assignment.

---

## Usage Instructions

Clone the repository, navigate to the project directory, and compile each version as follows:

```bash
cd my_shell
gcc main.c shell_utils.c execute.c builtins.c vars.c -o myshell
./myshell

