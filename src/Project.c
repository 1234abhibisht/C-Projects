#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        return;
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

    /* create a new temp file */
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        printf("Failed to open file");
        return;
    }

    /* copy newStr to temp file */
    fwrite(newStr, 1, strlen(newStr), temp);

    fclose(temp);

    /* remove old file */
    remove(fileName);

    /* rename temp file to the old file name */
    rename("temp.txt", fileName);

    free(newStr);
    newStr = NULL;
    return;
}

int main()
{

    /* Menu */
    printf("--------------------------------------------------------------------\n");
    printf("Welcome to the -----------------TEXT FILE MANAGER-------------------\n");
    printf("--------------------------------------------------------------------\n");
    printf("\n");

    char fileName[20];
    printf("Enter your file name : ");
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strcspn(fileName, "\n")] = '\0';

    /* open file */
    FILE *f = fopen(fileName, "r");
    if (f == NULL)
    {
        printf("Failed to open a file\n");
        exit(1);
    }

    /* now finding size of file which is opened */

    fseek(f, 0, SEEK_END); /* moves FILE pointer f to the end of file */
    long size = ftell(f);  /* tells total size of file (memory taken by all character in file)*/
    rewind(f);             /* moves FILE pointer f to the start of file again */

    /* dynamically create a string and copy content of file to the string */

    char *str = (char *)malloc(size + 1); /* +1 for '\0' */
    if (str == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    /* copy content of file to string */
    fread(str, 1, size, f);
    str[size] = '\0'; /* as string contain '\0' at end but file do not, so manually adding '\0' to the end of string */
    /* after fread FILE Pointer f is at end of file, to bring in back at starting of file */
    rewind(f);

    /* for example we have 28 characters in a file, each character takes 1 byte, so total 28 bytes
    of memory will be taken by file.
    In string 1 extra byte should be there for '\0', the index for 28 characters will be from
    0 to 27 and 28th index will be for '\0' */

    int response;

    while (1)
    {
        printf("\n");
        printf("----------------------------------------------------------\n");
        printf("Select the tool which you want to use\n");
        printf("1 - Particular Word Counting Tool\n");
        printf("2 - Word Finding Tool\n");
        printf("3 - Replace Word with New Word Tool\n");
        printf("4 - Total Character And Line Counting Tool\n");
        printf("5 - End the Program\n");
        printf("----------------------------------------------------------\n");
        printf("\n");
        printf("Enter your response : ");
        scanf("%d", &response);
        getchar();

        switch (response)
        {
        case 1:
            printf("\n");
            printf("Content inside your file : %s\n", str);
            printf("\n");

            char *freqStr = str;
            char frequencyWord[30];
            printf("Enter a word whose frequency you want to count : ");
            fgets(frequencyWord, sizeof(frequencyWord), stdin);
            frequencyWord[strcspn(frequencyWord, "\n")] = '\0';

            int frequecnyCount = 0;
            while ((freqStr = strstr(freqStr, frequencyWord)) != NULL)
            {
                frequecnyCount++;
                freqStr += strlen(frequencyWord);
            }

            printf("\n");
            printf("%s appears %d times\n", frequencyWord, frequecnyCount);
            break;

        case 2:
            /* str string has content of file inside it */

            printf("\n");
            printf("Content inside your file : %s\n", str);
            printf("\n");

            char findWord[30];
            printf("Enter a word you want to find inside the file : ");
            fgets(findWord, sizeof(findWord), stdin);
            findWord[strcspn(findWord, "\n")] = '\0';

            /* find word inside file */

            char linebuffer[1000];
            int linecount = 0;
            int flag = 0;

            printf("\n");
            while (fgets(linebuffer, sizeof(linebuffer), f))
            {
                linecount++;
                if (strstr(linebuffer, frequencyWord) != NULL)
                {
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                printf("Word found in line %d\n", linecount);
            }
            else
            {
                printf("Word not found in file\n");
            }

            break;

        case 3:
            printf("\n");
            printf("Content inside your file : %s\n", str);
            printf("\n");

            /* Taking input for old word */
            char wordOld[30];
            printf("Enter a word which you want to replace in file : ");
            fgets(wordOld, sizeof(wordOld), stdin);
            wordOld[strcspn(wordOld, "\n")] = '\0';

            printf("\n");

            /* Taking input for new word */
            char wordNew[30];
            printf("Enter a new word by which you want to replace old word : ");
            fgets(wordNew, sizeof(wordNew), stdin);
            wordNew[strcspn(wordNew, "\n")] = '\0';

            /* call the function to replace old word with new word */
            replaceWords(str, wordOld, wordNew, fileName);

            // printf("\n");
            printf("Your file has been updated\n");
            break;

        case 4: /* file is still open */
            printf("\n");
            printf("Content inside your file : %s\n", str);
            printf("\n");

            int ch, charac = 0, line = 0;
            while ((ch = fgetc(f)) != EOF)
            {
                charac++;
                if (ch == '\n')
                {
                    line++;
                }
            }
            /* if file has only one line, no new line */
            if (line == 0 && charac > 0)
            {
                line = 1;
            }
            printf("\n");
            printf("Total characters in file are %d\n", charac);
            printf("\n");
            printf("Total lines in file are %d\n", line);

            break;

        case 5:
            printf("\n");
            printf("Thank you for using this program !\n");
            exit(0);
        }
    }

    fclose(f);
    free(str);
    str = NULL;
    return 0;
}
