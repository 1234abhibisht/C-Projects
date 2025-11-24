#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void replaceWords(char *oldStr, char *wordOld, char *wordNew, char *fileName)
{
    int oldWordLen = strlen(wordOld);
    int newWordLen = strlen(wordNew);

    int count = 0;
    char *ptr1 = oldStr;

    while ((ptr1 = strstr(ptr1, wordOld)) != NULL)
    {
        count++;
        ptr1 += oldWordLen;
    }

    char *newStr = (char *)malloc(strlen(oldStr) + (newWordLen - oldWordLen) * count + 1);
    if (newStr == NULL)
    {
        printf("Failed to allocate memory\n");
        return;
    }

    char *ptr2 = oldStr;
    char *str2 = newStr;

    while ((ptr1 = strstr(ptr2, wordOld)) != NULL)
    {
        int gap = ptr1 - ptr2;
        memcpy(str2, ptr2, gap);
        str2 += gap;

        memcpy(str2, wordNew, newWordLen);
        str2 += newWordLen;

        ptr2 = ptr1 + oldWordLen;
    }

    strcpy(str2, ptr2);

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    fwrite(newStr, 1, strlen(newStr), temp);
    fclose(temp);

    remove(fileName);
    rename("temp.txt", fileName);

    free(newStr);
}
