#include <stdio.h>
#include <stdlib.h>


void batchMode() {

    printf("Congrats you reached batch mode! \n");

}


void interactiveMode() {

    printf("Congrats you reached interactive mode! \n");
    
    // while (command != "exit") {
    //     printf("ccsh>");
    //     command = getline();
    //
    //
    //     // taken from hw3 example
    //     int child_pid = fork();
    //
    //     // If the parent, just wait for the child
    //
    //     if (child_pid != 0) { // parent runs
    //         printf("<%d>: In parent after fork, child pid <%d>\n", getpid(), child_pid);
    //         wait(NULL);
    //         printf("<%d>: In parent after wait\n", getpid());
    //     }
    //
    //     else { // child runs
    //
    //         printf("<%d>: In child after fork\n", getpid());
    //
    //         // Copy the arguments
    //
    //         char *child_args[argc];
    //
    //         TODO // swap to what ever the commands are rather than current args
    //         for (int i = 1; i < argc; i++)
    //             child_args[i-1] = argv[i];
    //         child_args[argc-1] = NULL;
    //
    //
    //         int rc = execvp(child_args[0], child_args);
    //
    //         if (rc != 0)
    //             printf("Error in exec: rc <%d>, errno: %d - %s\n", rc, errno, strerror(errno));
    //
    //         printf("<%d>: In child after exec\n", getpid());
    //
    //     }
    // }
}

int main(int argc, char *argv[]) {

    if (argc == 1) { interactiveMode(); }

    else if (argc == 2) { batchMode(); }

    else {
        exit(1);
    }

    exit(0);
}
