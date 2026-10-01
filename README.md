# Shell-Programming
Operating Systems: CPSC 380 - Programming Assignment 1

## Author
Name: Julia Nguyen
Collaborator: Hemi Shah

## Design Overview
This project implements a simple command-line shell called ossh. The shell allows users to enter commands and execute them using child processes. Supporting both interactive mode, where commands are entered directly into the terminal, and batch mode, where commands are read from a file. 

The program uses fgets() to read user input and strtok() to separate multiple commands and command arguments via a parsing helper function. Commands separated by ";" can be executed in sequence. The shell creates a child process using fork() and uses execvp() to execute each command. The parent process uses wait() to wait for the child process to finish before continuing.

The shell also checks for invalid input, empty commands, too many commands or arguments, failed processes, and the quit command. Arrays are limited to 1024 elements to prevent the program from going past its allocated space. 

## How to Compile
    gcc ossh.c -o ossh

## How to Run
    ./ossh                  (interactive mode)
    ./ossh batchfile.txt    (batch mode)

## Known Bugs or Problems
- Lines longer than 1023 characters are split into multiple inputs.