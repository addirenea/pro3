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

    char *paths[500];
    paths[0] = "/bin";
    int pathsc = 1;

    // clearScreen();

    size_t bufsize = 512;
    char *input = (char *)malloc(bufsize * sizeof(char));


    while (1) {

        // gets next line of input
        printf("\033[1;35m");
        printf("ccsh> ");
        printf("\033[0m");
        getline(&input, &bufsize, stdin);
        // IDEA: i think that for batch mode we would just need to tweak here
        // where is says stdin for getline


        // split input into seperate command prompts
        int cmdc = getCmdCount(input);
        char *commands[cmdc];

        char *tmp_cmd = strtok (input, "&");
        for (int i = 0; i < cmdc; i++) {

            commands[i] = tmp_cmd;
            tmp_cmd = strtok (NULL, "&");

        }


        // for each command...
        pid_t child_pid;

        for (int i = 0; i < cmdc; i++) {

            // construct args[]
            int argc = getWordCount(commands[i]);
            char *args[argc + 1];

            char *arg = strtok (commands[i], " \t\n");
            for (int i = 0; i < argc; i++) {

                args[i] = arg;
                arg = strtok (NULL, " \t\n");

            }

            args[argc] = NULL;



            // check for built in commands
            if (strcmp(args[0], "exit") == 0) {

                exit(0);

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

            // PATH UNDER CONSTRUCTION
            else if (strcmp(args[0], "path") == 0) {

                pathsc = argc - 1;

                for (int i = 0; i < pathsc; i++) {

                    // printf("replacing [%s] at i = %d with [%s]\n", paths[i], i, args[i+1]);
                    printf("top of for loop, i = %d\n", i);

                    char temp[strlen(args[i + 1])];
                    strcpy(temp, args[i + 1]);

                    printf("after init, [%s]\n", temp);
                    // strcpy(paths[i], temp);
                    paths[i] = temp;

                    printf("after copy\n");
                    printf("at i = %d, [%s]\n", i, paths[i]);


                }



                printf("new path: \n");
                for (int i = 0; i < pathsc; i++) {
                    printf("[%s]\n", paths[i]);
                }
                paths[pathsc] = NULL;


            }

            // FOR TESTING PURPOSES, REMOVE BEFORE SUBMISSION
            else if (strcmp(args[0], "seepath") == 0) {

                for (int i = 0; i < pathsc; i++) {

                    printf("[%s]\n", paths[i]);

                }

            }

            else {

                child_pid = fork();

                // child runs command
                if (child_pid == 0) {

                    execCommand(args, paths, pathsc);

                }

                // error forking
                else if (child_pid < 0) {

                    errorOccurred();

                }

            }

        }

        // parent waits for all children processes to finish
        pid_t wait_pid;
        int status = 0;
        while ((wait_pid = wait(&status)) > 0);

    }

    free(input);

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
