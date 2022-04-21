#include "helpers.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void errorOccurred() {

    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));

}


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



void execCommand(char** args, char *paths[500], int numOfPaths) {

    // loops through all path starts in paths[]
    for (int i = 0; i < numOfPaths; i++) {

        // contruct full path
        char path[strlen(paths[i]) + 1 + strlen(args[0])];
        strcpy(path, paths[i]);
        strcat(path, "/");
        strcat(path, args[0]);

        // executes and returns if file found
        if (access(path, X_OK) == 0) {

            int rc = execv(path, args);
            if (rc != 0) { errorOccurred(); }
            return;
        }
    }

    // only reaches here when file not found
    errorOccurred();
    return;
}
