#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <libgen.h>
#include "text_colors.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        text_color_red();
        printf("mkdir: missing operand\n");
        text_color_yellow();
        printf("Try 'mkdir --help' for more information.\n");
        text_color_reset();
        return 1;
    }
    else
    {
        for (int i = 1; i < argc; ++i)
        {
            char *dirname = argv[i];
            if (access(dirname, R_OK) != -1)
            {
                text_color_red();
                printf("mkdir: cannot create directory '%s': File exists\n", dirname);
                text_color_reset();
            }
            else
            {
                int status;
                status = mkdir(dirname, 0700);
                if (status)
                {
                    text_color_red();
                    printf("mkdir: error creating directory '%s'\n", dirname);
                    text_color_reset();
                }
            }
        }
    }
    return 0;
}