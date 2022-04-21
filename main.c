#include "helpers.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


char *paths[500];
int numOfPaths=0;

void batchMode() {

    printf("batch mode under construction \n");

}


void interactiveMode() {

    // TODO: figure out how to clear terminal screen

    size_t bufsize = 256;
    char *command = (char *)malloc(bufsize * sizeof(char));

    paths[0] = "/bin"; //NEW
    numOfPaths = 1;





    while (1) {

        // gets next line
        printf("\033[1;35m"); // makes text purple!!
        printf("ccsh> ");
        printf("\033[0m");
        getline(&command, &bufsize, stdin);



        // constructs args[]
        int argc = getWordCount(command);
        char *args[argc + 1];

        char *arg = strtok (command, " \t\n");
        for (int i = 0; i < argc; i++) {
            args[i] = arg;
            arg = strtok (NULL, " \t\n");
        }

        args[argc] = NULL;



        // check for built in commands
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        else if (strcmp(args[0], "cd") == 0) {

            char dirpath[1000];

            if (argc <= 1 || chdir(args[1]) != 0) {
                errorOccurred();
            }

            else {
                printf("cwd: %s\n", getcwd(dirpath, 1000));
            }

        }

        else if (strcmp(args[0], "path") == 0) {


            // its being weird and mean :(
            
            for (int i = 0; i < numOfPaths; i++) {
                printf("%s\n", paths[i]);
            }



            numOfPaths = argc - 1;
            for (int i = 0; i < numOfPaths; i++) {
                paths[i] = args[i + 1];
            }



            printf("new path: \n");
            for (int i = 0; i < numOfPaths; i++) {
                printf("%s\n", paths[i]);
            }


        }

        else {

            int child_pid = fork();

            // parent runs
            if (child_pid != 0) {
                wait(NULL);
            }

            // child runs
            else {

                execCommand(args, paths, numOfPaths);

                break;

            }

        }

    }

    free(command);
}


int main(int argc, char *argv[]) {

    if (argc == 1) {
        interactiveMode();
    }

    else if (argc == 2) {
        batchMode();
    }

    else {
        exit(1);
    }

    exit(0);
}
