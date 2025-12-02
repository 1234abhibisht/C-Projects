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
    if (!f)
    {
        printf("Failed to open file\n");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *str = (char *)malloc(size + 1);
    if (!str)
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

        char frequencyWord[30];
        printf("Enter a word whose frequency you want to count : ");
        fgets(frequencyWord, sizeof(frequencyWord), stdin);
        frequencyWord[strcspn(frequencyWord, "\n")] = '\0';

        wordFrequency(str, frequencyWord);
        rewind(f);
        break;
    }

    case 2:
    {
        printf("\nContent inside your file : %s\n\n", str);

        char findWord[30];
        printf("Enter a word you want to find inside the file : ");
        fgets(findWord, sizeof(findWord), stdin);
        findWord[strcspn(findWord, "\n")] = '\0';

        wordFind(findWord, f);
        rewind(f);
        break;
    }

    case 3:
    {
        printf("\nContent inside your file : %s\n\n", str);

        char wordOld[30], wordNew[30];
        printf("Enter a word which you want to replace in file : ");
        fgets(wordOld, sizeof(wordOld), stdin);
        wordOld[strcspn(wordOld, "\n")] = '\0';

        printf("Enter a new word : ");
        fgets(wordNew, sizeof(wordNew), stdin);
        wordNew[strcspn(wordNew, "\n")] = '\0';

        replaceWords(str, wordOld, wordNew, fileName);
        printf("Your file has been updated\n\n");
        rewind(f);
        break;
    }

    case 4:
    {
        printf("\nContent inside your file : %s\n\n", str);

        lineCharCount(f);
        rewind(f);
        break;
    }

    case 5:
        printf("Thank you for using this program!\n");
        exit(0);

    default:
        printf("Wrong Option Entered, failed to run\n");
        exit(1);
    }

    fclose(f);
    free(str);
    return 0;
}
