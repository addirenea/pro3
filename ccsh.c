#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void batchMode() {

    printf("batch mode under construction \n");

}


void interactiveMode() {

    size_t bufsize = 256;
    size_t command_len;

    char *command = (char *)malloc(bufsize * sizeof(char));


    // gets next line and removes newline character at end of string
    printf("ccsh> ");
    command_len = getline(&command, &bufsize, stdin);
    if ((command)[command_len - 1] == '\n')
    {
        (command)[command_len - 1] = '\0';
        command_len--;
    }

    // main while loop for shell
    while (strcmp(command, "exit") != 0) {

        // TODO: 1. check for special commands using if, else if, else (special commands: cd, path)
        //       2. figure out how to get args[0] = program path
        //       3. fork()
        //       4. inside child: execv(path, args);
        //       4. inside parent: wait(NULL);
        //       5. prompt for new command
        //       6. separate command into *args[] using strsep()

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

        printf("your command was: %s\n", command);


        // gets next line and removes newline character at end of string
        printf("ccsh> ");
        command_len = getline(&command, &bufsize, stdin);
        if ((command)[command_len - 1] == '\n')
        {
            (command)[command_len - 1] = '\0';
            command_len--;
        }
    }

    printf("you exited!\n");
    free(command);
}

int main(int argc, char *argv[]) {

    if (argc == 1) { interactiveMode(); }

    else if (argc == 2) { batchMode(); }

    else {
        exit(1);
    }

    exit(0);
}
