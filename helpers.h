#ifndef HELPERS_DOT_H
#define HELPERS_DOT_H


void errorOccurred();

void clearScreen();

int getWordCount(char *str);

int getCmdCount(char *str);

void execCommand(char** args, char *paths[500], int numOfPaths);


#endif
