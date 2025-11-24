#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replaceWords(char *oldStr, char *wordOld, char *wordNew, char *fileName);
void findWordInFile(FILE *f, const char *word);
void countCharAndLines(FILE *f);

#endif

