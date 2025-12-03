#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum Menu {
    create = 1,
    read = 2,
    frequency = 3,
    find = 4,
    replace = 5,
    linechar = 6,
    end = 7
};

void wordFrequency(char *freqStr, char frequencyWord[]);
void wordFind(char findWord[], FILE *f2);
void replaceWords(char *oldStr, char *wordOld, char *wordNew, char *fileName);
void lineCharCount(FILE *f4);

#endif



