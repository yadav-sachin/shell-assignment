#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include "text_colors.h"

const int MAX_LINE = 1256;

int does_match(char *line, char *pattern)
{
    int N = strlen(line), M = strlen(pattern);
    for (int i = 0; i < N; ++i)
    {
        int j = 0;
        int c = i;
        for (j; j < M; ++j)
        {
            if (line[c] != pattern[j])
                break;
            ++c;
        }
        if (j == M)
            return 1;
    }
    return 0;
}

void print_if_match(char *file_name, char *line, char *pattern)
{
    if (does_match(line, pattern))
    {
        text_color_magenta();
        if (strlen(file_name))
            printf("%s: ", file_name);
        text_color_reset();
        int N = strlen(line), M = strlen(pattern);
        char ch;
        for (int i = 0; i < N; ++i)
        {
            int j = 0;
            int c = i;
            for (j; j < M; ++j)
            {
                if (line[c] != pattern[j])
                    break;
                ++c;
            }
            if (j == M)
            {
                text_color_blue();
                printf("%s", pattern);
                text_color_reset();
                i += j - 1;
            }
            else
                printf("%c", line[i]);
        }
    }
}

void searchFile(char *file_name, char *pattern)
{
    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL)
        return;
    char line[MAX_LINE];

    while (fptr && fgets(line, MAX_LINE, fptr))
    {
        print_if_match(file_name, line, pattern);
    }
    fclose(fptr);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        text_color_yellow();
        printf("Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.\n");
        text_color_reset();
    }
    else if (argc == 2)
    {
        char line[MAX_LINE];
        while (1)
        {
            fgets(line, MAX_LINE, stdin);
            print_if_match("", line, argv[1]);
        }
    }
    else
    {
        for (int i = 2; i < argc; ++i)
            searchFile(argv[i], argv[1]);
    }
    return 0;
}