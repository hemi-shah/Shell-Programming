#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void parseInput(char userInput[], char *command, char *argument, pid_t pid)

int main(int argc, char *argv[]){

    // file pointer
    FILE *file;

    // stores user input
    char userInput[64];

    // stores the number of arguments entered
    int nargs = argc-1;

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
        for (int i = 0; i < sizeof(userInput); i++){
            // get command separated by ; from user input
            command = strtok(userInput, ";");
            // get argument separated by space from user input
            argument = strtok(command, " ");

            // fork child process
            pid = fork();

            // parent process waits for child process to finish
            wait(NULL);

            // execute command
            execvp(argument);

            if (argument == "quit"){
                return 0;
            }
        }
    } else {
        perror("Incorrect number of inputs given");
    }

    return 0;
}

void parseInput(userInput, command, argument, pid){

}