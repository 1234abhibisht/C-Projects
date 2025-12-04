#include "header.h"

int main()
{
    printf("--------------------------------------------------------------------\n");
    printf("Welcome to the -----------------TEXT FILE MANAGER-------------------\n");
    printf("--------------------------------------------------------------------\n");

    printf("-----Select the tool which you want to use-----\n");
    printf("\n----------------------------------------------------------\n");
    printf("1 - Create a new file\n");
    printf("2 - Read existing file\n");
    printf("3 - Particular Word Counting Tool in existing file\n");
    printf("4 - Word Finding Tool in existing file\n");
    printf("5 - Replace Word with New Word Tool in existing file\n");
    printf("6 - Total Character And Line Counting Tool in existing file\n");
    printf("7 - End the Program\n");
    printf("----------------------------------------------------------\n\n");

    printf("Enter your response : ");
    enum Menu response;
    scanf("%d", (int *)&response);
    getchar(); // clear newline

    switch (response)
    {
    case create:
    {
        printf("------You have selected to create a new file------\n");

        /* create a new file */
        printf("Enter your file name : \n");
        char fileCreate[40];
        fgets(fileCreate, sizeof(fileCreate), stdin);
        fileCreate[strcspn(fileCreate, "\n")] = '\0';

        printf("Enter content for your file : \n");

        /* Taking input of contents for file using dynamic string */
        int sizeInitial = 5;
        int elementsInitial = 0;
        char *content = (char *)malloc(sizeInitial);
        if (!content)
        {
            printf("Failed to allocate memory\n");
            exit(1);
        }
        int c;
        while ((c = getchar()) != EOF && c != '\n')
        {
            if (sizeInitial == elementsInitial)
            {
                sizeInitial *= 2;
                content = realloc(content, sizeInitial);
            }
            content[elementsInitial] = c;
            elementsInitial++;
        }
        // content[elementsInitial] = '\0';

        FILE *createf = fopen(fileCreate, "w");
        if (!createf)
        {
            perror("fopen");
            exit(1);
        }

        /* write content from string to the file created */
        fwrite(content, 1, strlen(content), createf);
        rewind(createf);

        fclose(createf);
        free(content);
        content = NULL;

        printf("------Your file has been created------\n");

        break;
    }

    case read:
    {
        printf("------You have selected to read a file------\n");

        /* read a file */
        printf("Enter your file name : \n");
        char fileRead[40];
        fgets(fileRead, sizeof(fileRead), stdin);
        fileRead[strcspn(fileRead, "\n")] = '\0';

        FILE *readf = fopen(fileRead, "r");
        if (!readf)
        {
            perror("fopen");
            exit(1);
        }

        /* finding size of file */
        fseek(readf, 0, SEEK_END);
        long sizeRead = ftell(readf);
        rewind(readf);

        /* create a dynamic string of size same as size of file */
        char *strRead = (char *)malloc(sizeRead + 1); /* +1 for '\0' */

        /* read content of file */
        fread(strRead, 1, sizeRead, readf);
        strRead[sizeRead] = '\0';
        rewind(readf);

        printf("-------Content inside your file is-------\n");
        printf("%s\n", strRead);

        fclose(readf);
        free(strRead);
        strRead = NULL;

        break;
    }

    case frequency:
    {
        printf("------You have selected to check frequency of word------\n");

        /* read a file */
        printf("Enter your file name : \n");
        char fileFreq[40];
        fgets(fileFreq, sizeof(fileFreq), stdin);
        fileFreq[strcspn(fileFreq, "\n")] = '\0';

        FILE *freqf = fopen(fileFreq, "r");
        if (!freqf)
        {
            perror("fopen");
            exit(1);
        }

        /* finding size of file */
        fseek(freqf, 0, SEEK_END);
        long sizeFreq = ftell(freqf);
        rewind(freqf);

        /* create a dynamic string of size same as size of file */
        char *freqStr = (char *)malloc(sizeFreq + 1); /* +1 for '\0' */

        /* read content of file */
        fread(freqStr, 1, sizeFreq, freqf);
        freqStr[sizeFreq] = '\0';
        rewind(freqf);

        /* Taking input of word whose frequency we have to find */
        char frequencyWord[30];
        printf("Enter the word whose frequency you want to find : \n");
        fgets(frequencyWord, sizeof(frequencyWord), stdin);
        frequencyWord[strcspn(frequencyWord, "\n")] = '\0';

        /* passing to the function to find frequency of word */
        wordFrequency(freqStr, frequencyWord);

        fclose(freqf);
        free(freqStr);
        freqStr = NULL;
        break;
    }

    case find:
    {
        printf("------You have selected to find word in file------\n");

        /* read a file */
        printf("Enter your file name : \n");
        char fileFind[40];
        fgets(fileFind, sizeof(fileFind), stdin);
        fileFind[strcspn(fileFind, "\n")] = '\0';

        FILE *findf = fopen(fileFind, "r");
        if (!findf)
        {
            perror("fopen");
            exit(1);
        }

        /* finding size of file */
        fseek(findf, 0, SEEK_END);
        long sizeFind = ftell(findf);
        rewind(findf);

        /* Taking input of word which we want to find in file */
        char findWord[30];
        printf("Enter the word which you want to find : \n");
        fgets(findWord, sizeof(findWord), stdin);
        findWord[strcspn(findWord, "\n")] = '\0';

        /* passing to the function to find word in file*/
        wordFind(findWord, findf);

        fclose(findf);
        break;
    }

    case replace:
    {
        printf("------You have selected to replace word in file------\n");

        /* read a file */
        printf("Enter your file name : \n");
        char fileRep[40];
        fgets(fileRep, sizeof(fileRep), stdin);
        fileRep[strcspn(fileRep, "\n")] = '\0';

        FILE *repf = fopen(fileRep, "r");
        if (!repf)
        {
            perror("fopen");
            exit(1);
        }

        /* finding size of file */
        fseek(repf, 0, SEEK_END);
        long sizeRep = ftell(repf);
        rewind(repf);

        /* create a dynamic string of size same as size of file */
        char *repStr = (char *)malloc(sizeRep + 1); /* +1 for '\0' */

        /* read content of file */
        fread(repStr, 1, sizeRep, repf);
        repStr[sizeRep] = '\0';
        rewind(repf);

        /* Taking input of word which we want to replace in file */
        char WordOld[30];
        printf("Enter the word which you want to replace : \n");
        fgets(WordOld, sizeof(WordOld), stdin);
        WordOld[strcspn(WordOld, "\n")] = '\0';

        /* Taking input of word from which we want to replace old word in file */
        char WordNew[30];
        printf("Enter the word from which you want to replace old wor : \n");
        fgets(WordNew, sizeof(WordNew), stdin);
        WordNew[strcspn(WordNew, "\n")] = '\0';

        /* passing to the function to find word in file*/
        replaceWords(repStr, WordOld, WordNew, fileRep);

        fclose(repf);
        free(repStr);
        repStr = NULL;

        printf("------Your file has been updated------\n");
        break;
    }

    case linechar:
    {
        printf("------You have selected to find word in file------\n");

        /* read a file */
        printf("Enter your file name : \n");
        char fileCh[40];
        fgets(fileCh, sizeof(fileCh), stdin);
        fileCh[strcspn(fileCh, "\n")] = '\0';

        FILE *chf = fopen(fileCh, "r");
        if (!chf)
        {
            perror("fopen");
            exit(1);
        }

        /* finding size of file */
        fseek(chf, 0, SEEK_END);
        long sizeCh = ftell(chf);
        rewind(chf);

        /* passing to the function to find word in file*/
        lineCharCount(chf);

        fclose(chf);
        break;
    }

    case end:
    {
        printf("-----Thank you for using this program!-----\n");
        exit(0);
    }

    default:
    {
        printf("Wrong Option Entered, failed to run\n");
        exit(1);
    }

        printf("-----Thank you for using this program!-----\n");
        return 0;
    }
}
