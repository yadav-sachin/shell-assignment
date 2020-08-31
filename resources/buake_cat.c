#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include "text_colors.h"

const int MAX_LINE = 1256;

void searchFile(char *file_name, char *pattern)
{
    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL)
    {
        printf("cat: %s: No such file or directory\n", file_name);
        return ;
    }
    char line[MAX_LINE];

    while (fptr && fgets(line, MAX_LINE, fptr))
    {
        printf("%s", line);
    }
    fclose(fptr);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        char line[MAX_LINE];
        while (1)
        {
            fgets(line, MAX_LINE, stdin);
            printf("%s\n", line);
        }
    }
    else
    {
        for (int i = 1; i < argc; ++i)
            searchFile(argv[i], argv[1]);
        printf("\n");
    }
    return 0;
}