#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

void parseInput(char userInput[], char *command, char *argument, pid_t pid);

int main(int argc, char *argv[]){

    // file pointer
    FILE *file;

    // stores user input
    char userInput[64];

    // stores the number of arguments entered
    int nargs = argc-1;

    // stores arguments from parsing
    char *argumentsArr[64];

    // stores comamnd during parsing
    char *command;

    // stores argument from parsing
    char *argument;

    // stores process ID 
    pid_t pid;

    // check to see if batch file is provided
    if (nargs == 1){
        // go into batch mode

        // parse through all given batch files and read them
        file = fopen(argv[1], "r");

        // return if file does not exist
        if (file == NULL){
            perror("File does not exist");
            return 1;
        }

        // parse through user commands
        // execute commands
        // continue loop

    } else if (nargs == 0){
        // go into interact mode

        // give user ossh> prompt
        printf("ossh> ");

        // waits for the user to enter input and stores it in userInput
        fgets(userInput, sizeof(userInput), stdin);

        // parse through user input
        // get the first command separated by ;
        command = strtok(userInput, ";");

        // continue while there are commands
        while (command != NULL) {

            // reset argument index to 0
            int argIndex = 0;

            // get the first argument separated by whitespace
            argument = strtok(command, " \t\n");

            // get all arguments for this command
            while (argument != NULL) {
                // add the argument to the argument array
                argumentsArr[argIndex] = argument;
                // iterate the argument index
                argIndex++;

                // get the next argument separated by whitespace
                argument = strtok(NULL, " \t\n");
            }

            // mark the end of the argument array
            argumentsArr[argIndex] = NULL;

            // fork child process
            pid = fork();

            if (pid < 0) {
                perror("Fork failed");
            }
            else if (pid == 0) {
                // child process
                // execute the command
                execvp(argumentsArr[0], argumentsArr);
            }
            else {
                // parent process
                // wait for child
                wait(NULL);
            }

            // get the next command separated by ;
            command = strtok(NULL, ";");
        }

        if (argument == "quit"){
            return 0;
        }
    } else {
        perror("Incorrect number of inputs given");
    }

    return 0;
}

void parseInput(char userInput[], char *command, char *argument, pid_t pid){
    // need to add refactored code here
}