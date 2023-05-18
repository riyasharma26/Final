#include <iostream>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

using namespace std;

class simple_shell {
public:
    void parse_command(char* cmd, char** cmdTokens) {
        //tokenize the command string into arguments
        char *token = strtok(cmd, " \n");
        int i = 0;
        while (token != NULL) {
            cmdTokens[i] = token;
            token = strtok(NULL, " \n");
            i++;
        }
        cmdTokens[i] = NULL;
    }

    void exec_command(char** argv) {
        //check if the command is a built-in command
        cout<<*argv<<endl;
        if (strcmp(argv[0], "cd") == 0) {
            if (argv[1] != NULL) {
                if (chdir(argv[1]) != 0) {
                    perror("cd failed");
                }
            } else {
                //change to the home directory if no argument is provided
                const char* home_dir = getenv("HOME");
                if (home_dir != NULL) {
                    if (chdir(home_dir) != 0) {
                        perror("cd failed");
                    }
                } else {
                    cout << "cd: No home directory found" << endl;
                }
            }
        } else if (strcmp(argv[0], "echo") == 0) {
            //print the arguments following "echo" command
            for (int i = 1; argv[i] != NULL; i++) {
                cout << argv[i] << " ";
            }
            cout << endl;
        } else if (strcmp(argv[0], "exit") == 0) {
            // Terminate the shell
            //exec_commmand(parscommand(second part));
            exit(0);
        } else if (strcmp(argv[0], "hello") == 0) {
            string name; 
            cout << "Hi, what is your name?" << endl;
            getline(cin, name);
            cout<< "Hi, " << name << "! Welcome to my shell." << endl;
            exit(0);
        } 
        else if (strcmp(argv[0], "marco") == 0) {
            cout<< "polo." << endl;
            exit(0);
        } else {
            //execute the command using execvp
            int pid = fork();
            if (pid == -1) {
                perror("fork failed");
                exit(0);
            } else if (pid == 0) {
                execvp(argv[0], argv);
                perror("execvp failed");
                exit(0);
            } else {
                wait(NULL);
            }
        }
    }

    bool isQuit(char* cmd) {
        //check if the command is equal to "quit"
        if (strcmp(cmd, "quit") == 0) {
            return true;
        }
        return false;
    }
};

int main() {
    simple_shell shell;
    char cmd[100];

    while (true) {
        cout << "tsh> ";
        cin.getline(cmd, sizeof(cmd));

        //check for quit command
        if (shell.isQuit(cmd)) {
            break;
        }

        //tokenize the command
        char* cmdTokens[20];
        shell.parse_command(cmd, cmdTokens);

        //execute the command
        shell.exec_command(cmdTokens);
    }

    return 0;
}