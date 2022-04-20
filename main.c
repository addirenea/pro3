#include "helpers.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


void batchMode() {

    printf("batch mode under construction \n");

}


void interactiveMode() {

    // TODO: figure out how to clear terminal screen

    // TODO: 1. check for built in commands using if, else if, else (commands: exit, cd, path)
    //       2. figure out how to get args[0] = program path
    //       3. fork()
    //       4. inside child: execv(path, args);
    //       4. inside parent: wait(NULL);

    size_t bufsize = 256;
    char *command = (char *)malloc(bufsize * sizeof(char));

    while (1) {

        // gets next line
        printf("\033[1;35m"); // makes text purple!!
        printf("ccsh> ");
        printf("\033[0m");
        getline(&command, &bufsize, stdin);


        // constructs args[]
        int argc = getWordCount(command);
        char *args[argc];

        char *arg = strtok (command, " \t\n");
        for (int i = 0; i < argc; i++) {
            args[i] = arg;
            arg = strtok (NULL, " \t\n");
        }


        // check for built in commands
        if (strcmp(args[0], "exit") == 0) { break; }

        else if (strcmp(args[0], "cd") == 0) {

            // if (argc != 1) {
            //     errorOccurred();
            // } else {
            //     if (chdir(args[1]) == -1) { errorOccurred(); }
            // };

            printf("built in: cd\n");

        }

        else if (strcmp(args[0], "path") == 0) {

            printf("built in: path\n");

        }

        else {

            int child_pid = fork();

            if (child_pid != 0) { wait(NULL); } // parent runs

            else { // child runs

                // COMMENT: dont think we need this commented block of code

                // printf("<%d>: In child after fork\n", getpid());

                // Copy the arguments

                // char *child_args[argc];
                //
                // TODO // swap to what ever the commands are rather than current args
                // for (int i = 1; i < argc; i++)
                //     child_args[i-1] = argv[i];
                // child_args[argc-1] = NULL;


                // printf("<%d>: In child after exec\n", getpid());

                printf("inside child - your program was: %s\n", args[0]);

                // int rc = execvp(args[0], args);

                // if (rc != 0) { errorOccurred(); }

                break;

            }

        }

    }

    free(command);
}


int main(int argc, char *argv[]) {

    if (argc == 1) { interactiveMode(); }

    else if (argc == 2) { batchMode(); }

    else { exit(1); }

    exit(0);
}
