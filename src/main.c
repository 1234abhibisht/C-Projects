#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    printf("--------------------------------------------------------------------\n");
    printf("Welcome to the -----------------TEXT FILE MANAGER-------------------\n");
    printf("--------------------------------------------------------------------\n\n");

    char fileName[20];
    printf("Enter your file name : ");
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strcspn(fileName, "\n")] = '\0';

    FILE *f = fopen(fileName, "r");
    if (f == NULL)
    {
        printf("Failed to open file\n");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *str = (char *)malloc(size + 1);
    if (str == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    fread(str, 1, size, f);
    str[size] = '\0';
    rewind(f);

    int response;
    printf("\n----------------------------------------------------------\n");
    printf("Select the tool which you want to use\n");
    printf("1 - Particular Word Counting Tool\n");
    printf("2 - Word Finding Tool\n");
    printf("3 - Replace Word with New Word Tool\n");
    printf("4 - Total Character And Line Counting Tool\n");
    printf("5 - End the Program\n");
    printf("----------------------------------------------------------\n\n");
    printf("Enter your response : ");
    scanf("%d", &response);
    getchar();

    switch (response)
    {
    case 1:
    {
        printf("\nContent inside your file : %s\n\n", str);

        char *freqStr = str;
        char frequencyWord[30];
        printf("Enter a word whose frequency you want to count : ");
        fgets(frequencyWord, sizeof(frequencyWord), stdin);
        frequencyWord[strcspn(frequencyWord, "\n")] = '\0';

        int frequencyCount = 0;
        while ((freqStr = strstr(freqStr, frequencyWord)) != NULL)
        {
            frequencyCount++;
            freqStr += strlen(frequencyWord);
        }

        printf("\n%s appears %d times\n", frequencyWord, frequencyCount);
        break;
    }

    case 2:
    {
        printf("\nContent inside your file : %s\n\n", str);

        char findWord[30];
        printf("Enter a word you want to find inside the file : ");
        fgets(findWord, sizeof(findWord), stdin);
        findWord[strcspn(findWord, "\n")] = '\0';

        rewind(f);

        char linebuffer[1000];
        int linecount = 0;
        int found = 0;

        while (fgets(linebuffer, sizeof(linebuffer), f))
        {
            linecount++;
            if (strstr(linebuffer, findWord))
            {
                printf("Word found in line %d\n", linecount);
                found = 1;
            }
        }

        if (!found)
            printf("Word not found in file\n");

        break;
    }

    case 3:
    {
        printf("\nContent inside your file : %s\n\n", str);

        char wordOld[30];
        printf("Enter a word which you want to replace in file : ");
        fgets(wordOld, sizeof(wordOld), stdin);
        wordOld[strcspn(wordOld, "\n")] = '\0';

        printf("\nEnter a new word : ");
        char wordNew[30];
        fgets(wordNew, sizeof(wordNew), stdin);
        wordNew[strcspn(wordNew, "\n")] = '\0';

        replaceWords(str, wordOld, wordNew, fileName);
        printf("Your file has been updated\n");
        break;
    }

    case 4:
    {
        printf("\nContent inside your file : %s\n\n", str);
        rewind(f);

        int ch, charac = 0, line = 0;

        while ((ch = fgetc(f)) != EOF)
        {
            charac++;
            if (ch == '\n')
                line++;
        }

        if (line == 0 && charac > 0)
            line = 1;

        printf("\nTotal characters: %d\n", charac);
        printf("Total lines: %d\n", line);
        break;
    }

    case 5:
        printf("Thank you for using this program!\n");
        exit(0);
    }

    fclose(f);
    free(str);
    return 0;
}
