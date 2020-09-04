#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include "../headers/text_colors.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        text_color_red();
        printf("mv: missing file operand\n");
        text_color_yellow();
        printf("Try 'mv --help' for more information.\n");
        text_color_reset();
        return 1;
    }
    else if (argc == 2)
    {
        text_color_red();
        printf("mv: missing destination file operand after '%s' \n", argv[1]);
        text_color_yellow();
        printf("Try 'mv --help' for more information.\n");
        text_color_reset();
        return 1;
    }
    else {
        if ( access( argv[1], W_OK) != -1)
        {
            int status = rename(argv[1], argv[2]);
            if (rename < 0)
            {
                text_color_red();
                printf("mv: The operation failed\n");
            }
            else
            {
                text_color_green();
                printf("mv: operation completed successfully\n");
            }
            text_color_reset();
        }
        else {
            text_color_red();
            printf("mv: cannot stat '%s': No such file or directory\n", argv[1]);
            text_color_reset();
            return 1;
        }
    }
    return 0;
}