#ifndef HELPERS_DOT_H
#define HELPERS_DOT_H


void errorOccurred();

int getWordCount(char *str);

int getCmdCount(char *str);

void execCommand(char** args, char paths[][1024], int pathsc);


#endif
