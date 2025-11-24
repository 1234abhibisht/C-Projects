#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void updateFile(char *newStr, char *fileName)
{

    /* create a new temp file */
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        printf("Failed to open file");
        exit(1);
    }

    /* copy newStr to temp file */
    fwrite(newStr, 1, strlen(newStr), temp);

    fclose(temp);

    /* remove old file */
    remove(fileName);

    /* rename temp file to the old file name */
    rename("temp.txt", fileName);
    return;
}

void replaceWords(char *oldStr, char *wordOld, char *wordNew, char *fileName)
{

    int oldWordLen = strlen(wordOld);
    int newWordLen = strlen(wordNew);

    /* count how many times wordOld repeat in oldStr */
    int count = 0;
    char *ptr1 = oldStr;
    while ((ptr1 = strstr(ptr1, wordOld)) != NULL)
    {
        count++;
        ptr1 += oldWordLen;
        /* now ptr1 will point to the first character of old word */
    }

    /* now create a new string and replace old word with new word in that string */
    char *newStr = (char *)malloc(strlen(oldStr) + (newWordLen - oldWordLen) * count + 1);
    if (newStr == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    char *ptr2 = oldStr;
    char *str2 = newStr;
    while ((ptr1 = strstr(ptr2, wordOld)) != NULL) /* this loop will check whether we have the old word */
    {

        /* copy words before old word to new string */
        int gap = ptr1 - ptr2; /* number of characters before old word */
        memcpy(str2, ptr2, gap);
        str2 += gap;

        /* copy new word to new string */
        memcpy(str2, wordNew, newWordLen);
        str2 += newWordLen;

        ptr2 = ptr1 + oldWordLen;
    }
    /* copy remaining words in new string */
    strcpy(str2, ptr2);
    /* we have copied words from old string to new string replacing old word, so '\0' will automaticlly be copied */

    /* call the fuction to copy content of new string to a file */
    updateFile(newStr, fileName);

    free(newStr);
    newStr = NULL;
    str2 = NULL;

    return;
}

int main()
{

    /* Menu */
    printf("--------------------------------------------------------------------\n");
    printf("Welcome to the -----------------TEXT FILE MANAGER-------------------\n");
    printf("--------------------------------------------------------------------\n");

    /* Input file name */
    char fileName[20];
    printf("Enter your file name : ");
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strcspn(fileName, "\n")] = '\0';

    FILE *f = fopen(fileName, "r");
    if (f == NULL)
    {
        printf("Failed to open a file\n");
        exit(1);
    }

    /* now finding size of file which is opened */

    fseek(f, 0, SEEK_END); /* moves cursor to the end */
    long size = ftell(f);  /* tells total size of file (memory taken by all character in file)*/
    rewind(f);             /* moves cursor to the start of file again */

    /* dynamically create a string and copy content of file to the string */

    char *oldStr = (char *)malloc(size + 1); /* +1 for '\0' */
    if (oldStr == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    /* copy content of file to string */
    fread(oldStr, 1, size, f);
    oldStr[size] = '\0'; /* as string contain '\0' at end but file do not, so manually adding '\0' to the end of string */

    /* for example we have 28 characters in a file, each character takes 1 byte, so total 28 bytes
    of memory will be taken by file.
    In string 1 extra byte should be there for '\0', the index for 28 characters will be from
    0 to 27 and 28th index will be for '\0' */

    //    printf("%s\n",Oldstr);
    // printf("%d\n",OldStringSize);

    fclose(f);

    printf("Content iside your file : %s\n", oldStr);

    /* Dynamically allocating memory to take input of the word we want to replace in our file */

    printf("Enter a word which you want to replace in file : ");
    int wordSizeOld = 5;
    int charactersOld = 0;
    char *wordOld = (char *)malloc(wordSizeOld);
    if (wordOld == NULL)
    {
        printf("Failed to allocate memory");
        exit(1);
    }
    int chOld;
    while ((chOld = getchar()) != EOF && chOld != '\n')
    {
        if (wordSizeOld == charactersOld)
        {
            wordSizeOld *= 2;
            wordOld = realloc(wordOld, wordSizeOld);
            if (wordOld == NULL)
            {
                printf("Failed to reallocate memory");
                exit(1);
            }
        }
        wordOld[charactersOld] = chOld;
        charactersOld++;
    }
    wordOld[charactersOld] = '\0';

    /* Dynamically allocating memory to take input of the word from which we want to replace old words in our file */

    printf("Enter a new word by which you want to replace old word : ");
    int wordSizeNew = 5;
    int charactersNew = 0;
    char *wordNew = (char *)malloc(wordSizeNew);
    if (wordNew == NULL)
    {
        printf("Failed to allocate memory");
        exit(1);
    }
    int chNew;
    while ((chNew = getchar()) != EOF && chNew != '\n' && chNew != ' ')
    {
        if (wordSizeNew == charactersNew)
        {
            wordSizeNew *= 2;
            wordNew = realloc(wordNew, wordSizeNew);
            if (wordNew == NULL)
            {
                printf("Failed to reallocate memory");
                exit(1);
            }
        }
        wordNew[charactersNew] = chNew;
        charactersNew++;
    }
    wordNew[charactersNew] = '\0';

    /* call the function to replace old word with new word */
    replaceWords(oldStr, wordOld, wordNew, fileName);

    free(wordOld);
    wordOld = NULL;

    free(wordNew);
    wordNew = NULL;

    free(oldStr);
    oldStr = NULL;
    return 0;
}
