#include "helpers.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    // more than one file
    if (argc > 2) {
        exit(1);
    }

    else {

        // initalize path variable
        int pathsc = 1;
        char paths[512][1024];
        char *starting_path = "/bin";
        strcpy(*paths, starting_path);

        int needToWait = 0; // flag for forked processes

        size_t bufsize = 1024;
        char *input = (char *)malloc(bufsize * sizeof(char));

        FILE *fp;
        if (argc == 2) {
            fp = fopen(argv[1], "r");
        }

        int line_rc;

        while (1) {

            if (argc == 1) { // interactive mode
                printf("\033[1;35m");
                printf("ccsh> ");
                printf("\033[0m");
                line_rc = getline(&input, &bufsize, stdin);
            }

            else { // batch mode
                line_rc = getline(&input, &bufsize, fp);
            }


            if (strcmp(input, "\n") != 0) { // prevent segfault when user enters nothing

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
                    int arg_ct = getWordCount(commands[i]);
                    char *args[arg_ct + 1];

                    char *arg = strtok (commands[i], " \t\n");
                    for (int i = 0; i < arg_ct; i++) {

                        args[i] = arg;
                        arg = strtok (NULL, " \t\n");

                    }

                    args[arg_ct] = NULL;


                    // check for built in commands
                    if (strcmp(args[0], "exit") == 0 || line_rc == -1) {

                        free(input);
                        exit(0);

                    }

                    else if (strcmp(args[0], "cd") == 0) {

                        char dirpath[1000];

                        if (arg_ct <= 1 || chdir(args[1]) != 0) {
                            errorOccurred();
                        }

                        else {
                            printf("cwd: %s\n", getcwd(dirpath, 1000));
                        }

                    }

                    else if (strcmp(args[0], "path") == 0) {

                        pathsc = arg_ct - 1;

                        for (int i = 0; i < pathsc; i++) {

                            strcpy(*(paths + i), args[i + 1]);

                        }

                    }

                    else if (strcmp(args[0], "seepath") == 0) {

                        for (int i = 0; i < pathsc; i++) {

                            printf("[%s]\n", paths[i]);

                        }

                    }

                    else {

                        needToWait = 1;
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
                if (needToWait == 1) {

                    pid_t wait_pid;
                    int status = 0;
                    while ((wait_pid = wait(&status)) > 0);
                    needToWait = 0;

                }
            }
        }

        free(input);
    }

    exit(0);
}
