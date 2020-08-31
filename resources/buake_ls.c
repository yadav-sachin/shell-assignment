#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include "text_colors.h"

int main(int argc, char *argv[])
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (argc > 1)
        d = opendir(argv[1]);
    if (d)
    {
        while ( (dir = readdir(d)) )
        {
            int ftype = dir->d_type;

            if (ftype == 4)
                text_color_blue();

            printf("%s\n", dir->d_name);
            text_color_reset();
        }
        closedir(d);
    }
    else {
        text_color_red();
        printf("cannot access '%s': No such directory\n", argv[1]);
        text_color_reset();
        return 1;
    }
    return 0;
}