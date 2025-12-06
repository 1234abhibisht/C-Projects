#include "header.h"

void wordFrequency(char *freqStr, char frequencyWord[])
{
    int frequencyCount = 0;
    while ((freqStr = strstr(freqStr, frequencyWord)) != NULL)
    {
        frequencyCount++;
        freqStr += strlen(frequencyWord);
    }

    printf("\n%s appears %d times\n\n", frequencyWord, frequencyCount);
    return;
}

void wordFind(char findWord[], FILE *f2)
{
    char linebuffer[1000];
    int linecount = 0;
    int found = 0;

    printf("\n");

    while (fgets(linebuffer, sizeof(linebuffer), f2))
    {
        linecount++;
        if (strstr(linebuffer, findWord))
        {
            printf("Word found in line %d\n", linecount);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Word not found in file\n");
    }

    printf("\n");
    return;
}

void replaceWords(char *oldStr, char *wordOld, char *wordNew, char *fileName)
{
    int oldWordLen = strlen(wordOld);
    int newWordLen = strlen(wordNew);
    int count = 0;

    char *ptr1 = oldStr;
    if (strstr(ptr1, wordOld) == NULL)
    {
        printf("-----Word not found in file-----\n");
        return;
    }
    while ((ptr1 = strstr(ptr1, wordOld)) != NULL)
    {
        count++;
        ptr1 += oldWordLen;
    }

    char *newStr = (char *)malloc(strlen(oldStr) + (newWordLen - oldWordLen) * count + 1);
    if (!newStr)
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
    if (!temp)
    {
        printf("Failed to open temporary file\n");
        free(newStr);
        return;
    }

    fwrite(newStr, 1, strlen(newStr), temp);
    fclose(temp);

    remove(fileName);
    rename("temp.txt", fileName);

    free(newStr);
    return;
}

void lineCharCount(FILE *f4)
{
    int ch, charac = 0, line = 1;

    while ((ch = fgetc(f4)) != EOF)
    {
        charac++;
        if (ch == '\n')
            line++;
    }

    printf("Total characters: %d\n\n", charac);
    printf("Total lines: %d\n\n", line);
}
