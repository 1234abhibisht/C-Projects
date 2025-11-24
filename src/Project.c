#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void countOldWord(char *str, char *wordOld)
// {
//     int count = 0;
//     char* ptr = str;
//     while((ptr = strstr(ptr,wordOld)) != NULL) {
//             count++;
//             ptr = ptr + strlen(wordOld);
//     }
//     printf("%d", count);
// }

int main()
{
    printf("Enter your string : ");

    /* Dynamically allocating memeory for string */
    /* ---------------------------------------------------------------- */
    int strSize = 5;
    int elements = 0;
    char *str = (char *)malloc(strSize);

    if (str == NULL)
    {
        printf("Failed to allocate memory");
        exit(1);
    }

    int st;
    while ((st = getchar()) != EOF && st != '\n')
    {
        if (strSize == elements)
        {
            strSize *= 2;
            str = realloc(str, strSize);
            if (str == NULL)
            {
                printf("Failed to reallocate memory");
                exit(1);
            }
        }
        str[elements] = st;
        elements++;
    }
    str[elements] = '\0';
    // int length = strlen(str);
    // printf("%d",length);
    free(str);
    str = NULL;
    /* -----------------------------------------------------------------------*/

    /* Dynamically allocating memory to take input of the word we want to replace in our file */

    /* -----------------------------------------------------------------------*/

    printf("Enter a word which you want to check : ");
    int wordSizeOld = 5;
    int charactersOld = 0;
    char *wordOld = (char *)malloc(wordSizeOld);
    int chOld;
    while ((chOld = getchar()) != EOF && chOld != '\n')
    {
        if (wordSizeOld == charactersOld)
        {
            wordSizeOld *= 2;
            wordOld = realloc(wordOld, wordSizeOld);
        }
        wordOld[charactersOld] = chOld;
        charactersOld++;
    }
    wordOld[charactersOld] = '\0';

    // int lenOld = strlen(wordOld);
    // printf("%d\n",lenOld);
    free(wordOld);
    wordOld = NULL;
    /* ------------------------------------------------------------------------ */

    /* Dynamically allocating memory to take input pf the word from which we want to replace old words in our file */

    /* -----------------------------------------------------------------------*/

    // printf("Enter a word which you want to check : ");
    // int wordSizeNew = 5;
    // int charactersNew = 0;
    // char *wordNew = (char *)malloc(wordSizeNew);
    // int chNew;
    // while ((chNew = getchar()) != EOF && chNew != '\n' && chNew != ' ')
    // {
    //     if (wordSizeNew == charactersNew)
    //     {
    //         wordSizeNew *= 2;
    //         wordNew = realloc(wordNew, wordSizeNew);
    //     }
    //     wordNew[charactersNew] = chNew;
    //     charactersNew++;
    // }
    // wordNew[charactersNew] = '\0';

    // int lenNew = strlen(wordNew);
    // // printf("%d\n",lenNew);
    // free(wordNew);
    // wordNew = NULL;
    /* -----------------------------------------------------------------------*/

    countOldWord(str, wordOld);

    return 0;
}
