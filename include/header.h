#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
void wordFrequenc(char *freqStr, char frequencyWord[]);
void wordFind(char findWord[], FILE *f2);
void replaceWords(char *oldStr, char *wordOld, char *wordNew, char *fileName);
void lineCharCount(FILE *f4);

#endif


