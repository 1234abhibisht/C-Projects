#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

enum Menu {
    frequency = 1,
    find = 2,
    replace = 3,
    linechar = 4,
    end = 5
};

void wordFrequency(char *freqStr, char frequencyWord[]);
void wordFind(char findWord[], FILE *f2);
void replaceWords(char *oldStr, char *wordOld, char *wordNew, char *fileName);
void lineCharCount(FILE *f4);

#endif



