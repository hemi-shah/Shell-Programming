#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int parseInput(char userInput[]);

int main(int argc, char *argv[]){

    // file pointer
    FILE *file;

    // stores user input
    char userInput[64];

    // stores the number of arguments entered
    int nargs = argc-1;

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

        // parse through user input
        while (fgets(userInput, sizeof(userInput), file) != NULL){

            // echo the command from the batch file
            printf("%s", userInput);

            // parse through user input
            if (parseInput(userInput) == 0){
                break;
            }
        }
    } else if (nargs == 0){
        // go into interact mode

        // parse through user input
        while (1) {

            // give user ossh> prompt
            printf("ossh> ");

            // waits for the user to enter input
            fgets(userInput, sizeof(userInput), stdin);

            // parse through user input
            if (parseInput(userInput) == 0) {
                break;
            }
        }
    } else {
        perror("Incorrect number of inputs given");
    }

    return 0;
}

int parseInput(char userInput[]){

    // stores commands from parsing
    char *commands[64];

    // stores arguments from parsing
    char *argumentsArr[64];

    // stores command during parsing
    char *command;

    // stores argument from parsing
    char *argument;

    // stores process ID
    pid_t pid;

    // stores the number of commands
    int commandIndex = 0;

    // get the first command separated by ;
    command = strtok(userInput, ";");

    // get all commands separated by ;
    while (command != NULL){

        // add the command to the command array
        commands[commandIndex] = command;

        // iterate the command index
        commandIndex++;

        // get the next command separated by ;
        command = strtok(NULL, ";");
    }

    // parse through all commands
    for (int i = 0; i < commandIndex; i++){

        // reset argument index to 0
        int argIndex = 0;

        // get the first argument separated by whitespace
        argument = strtok(commands[i], " \t\n");

        // get all arguments for this command
        while (argument != NULL){

            // add the argument to the argument array
            argumentsArr[argIndex] = argument;

            // iterate the argument index
            argIndex++;

            // get the next argument separated by whitespace
            argument = strtok(NULL, " \t\n");
        }

        // mark the end of the argument array
        argumentsArr[argIndex] = NULL;

        // check if the command is quit
        if (strcmp(argumentsArr[0], "quit") == 0){
            return 0;
        }

        // fork child process
        pid = fork();

        if (pid < 0){
            // fork failed
            perror("Fork failed");
            return 0;
        }
        else if (pid == 0){
            // child process

            // execute the command
            execvp(argumentsArr[0], argumentsArr);

            // execvp only returns if the command could not be executed
            perror("Command could not be executed");
            exit(1);
        }
        else {
            // parent process

            // wait for child process to finish
            wait(NULL);
        }
    }

    // return 1 to continue shell
    return 1;
}