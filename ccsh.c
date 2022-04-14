#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// word count function from project 2
int getWordCount(char *str) {

    int prev_in_word = 0;
    int wc = 0;

    // loops through all charaters in str
    while (*str)
    {
        // checks if character is whitespace
        if (*str == ' ' || *str == '\t' || *str == '\n')
            prev_in_word = 0;

        // otherwise checks if prev character was whitespace
        else if (prev_in_word == 0)
        {
            prev_in_word = 1;
            wc++;
        }

        str++;
    }

    return wc;
}


void batchMode() {

    printf("batch mode under construction \n");

}


void interactiveMode() {

    // TODO: figure out how to clear terminal screen

    size_t bufsize = 256;
    char *command = (char *)malloc(bufsize * sizeof(char));

    while (1) {

        // gets next line
        printf("ccsh> ");
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
        if (strcmp(args[0], "exit") == 0) {
            break;
        }



        // TODO: 1. check for built in commands using if, else if, else (commands: exit, cd, path)
        //       2. figure out how to get args[0] = program path
        //       3. fork()
        //       4. inside child: execv(path, args);
        //       4. inside parent: wait(NULL);



        // // taken from hw3 example
        // int child_pid = fork();
        //
        // if (child_pid != 0) { // parent runs
        //     printf("<%d>: In parent after fork, child pid <%d>\n", getpid(), child_pid);
        //     wait(NULL);
        //     printf("<%d>: In parent after wait\n", getpid());
        // }
        //
        // else { // child runs
        //
        //     printf("<%d>: In child after fork\n", getpid());
        //
        //     // Copy the arguments
        //
        //     char *child_args[argc];
        //
        //     TODO // swap to what ever the commands are rather than current args
        //     for (int i = 1; i < argc; i++)
        //         child_args[i-1] = argv[i];
        //     child_args[argc-1] = NULL;
        //
        //
        //     int rc = execvp(child_args[0], child_args);
        //
        //     if (rc != 0)
        //         printf("Error in exec: rc <%d>, errno: %d - %s\n", rc, errno, strerror(errno));
        //
        //     printf("<%d>: In child after exec\n", getpid());
        //
        // }

        printf("your program was: %s\n", args[0]);

    }

    printf("you exited!\n");
    free(command);
}


int main(int argc, char *argv[]) {

    if (argc == 1) { interactiveMode(); }

    else if (argc == 2) { batchMode(); }

    else { exit(1); }

    exit(0);
}
