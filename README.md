This is the extension of the simple shell project!
#Original Shell
In the original shell project, this is what was achieved:
The parse_command function tokenizes the command string into individual arguments, storing them in the cmdTokens array.
The exec_command function forks a child process to execute the command specified by the user. If the fork fails, an error message is displayed. In the child process, the command is executed using execvp. If execvp fails, another error message is displayed. In the parent process, the program waits for the child process to complete before proceeding.
The isQuit function checks if the command is "quit" by comparing the command string with the string "quit". It returns true if they match, indicating the termination of the shell; otherwise, it returns false.
The code utilizes system calls such as fork, execvp, and wait to manage processes and execute commands within the shell.
The shell can accept commands from the user, execute them with their specified arguments, and provide a prompt for the next command.
If the user enters the command "quit," the shell terminates.

#Extension of Shell
In the extension shell project, this is what was achieved:
Class and Object: The code introduces a simple_shell class to encapsulate the functionality of the shell. An instance of the class is created in the main function.
Parsing and Execution: The parse_command function tokenizes the command string into individual arguments, which are stored in the cmdTokens array. The exec_command function is responsible for executing the parsed command.
Built-in Commands: The exec_command function checks if the command is a built-in command by comparing the first argument (argv[0]) with a set of predefined commands (cd, echo, exit, hello, marco). Each built-in command is handled separately:
cd: Changes the current working directory to the specified directory or to the home directory if no argument is provided.
echo: Prints the arguments following the echo command.
exit: Terminates the shell.
hello: Prompts the user for their name and greets them.
marco: Prints "polo."
Forking and Executing External Commands: If the command is not a built-in command, the code forks a new process using fork() and executes the command using execvp(). The parent process waits for the child process to complete using wait(NULL).
Input and Quit Handling: The code uses cin.getline() to read the user input command into the cmd array. It checks if the command is equal to "quit" using the isQuit function and exits the shell if true.
