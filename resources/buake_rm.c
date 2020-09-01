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

const int BUFF_SIZE = 9024;

int remove_recursive(char *target)
{
    struct stat target_stat;
    stat(target, &target_stat);
    if (S_ISDIR(target_stat.st_mode))
    {
        DIR *d = opendir(target);
        if (d)
        {
            struct dirent *dir;
            while ((dir = readdir(d)))
            {
                if (strcmp(dir->d_name, ".") == 0)
                    continue;
                if (strcmp(dir->d_name, "..") == 0)
                    continue;
                int new_path_len = strlen(target) + strlen(dir->d_name) + 2;
                char *new_path = malloc(new_path_len);
                snprintf(new_path, new_path_len, "%s/%s", target, dir->d_name);
                remove_recursive(new_path);
            }
            closedir(d);
        }
        rmdir(target);
    }
    else
    {
        int status = remove(target);
        if (status != 0)
        {
            text_color_red();
            printf("rm: cannot remove '%s'\n", target);
            text_color_reset();
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        text_color_red();
        printf("rm: missing file operand\n");
        text_color_yellow();
        printf("Try 'rm --help' for more information.\n");
        text_color_reset();
        return 1;
    }
    else
    {
        int is_recursive = 0;
        for (int i = 1; i < argc; ++i)
        {
            if (strcmp(argv[i], "-r") == 0)
            {
                is_recursive = 1;
                break;
            }
        }
        for (int i = 1; i < argc; ++i)
        {
            char *target = argv[i];
            if (target[0] == '-')
                continue;
            if (access(target, W_OK) != -1)
            {
                struct stat target_stat;
                stat(target, &target_stat);
                if (S_ISDIR(target_stat.st_mode) && (is_recursive == 0)) //target is a directory without -r flag : not to remove in this case
                {
                    text_color_red();
                    printf("rm: cannot remove '%s': Is a directory\n", target);
                    text_color_reset();
                }
                else 
                {
                    remove_recursive(target);
                }
            }
            else
            {
                text_color_red();
                printf("rm: cannot remove '%s': No such file or directory\n", target);
                text_color_reset();
            }
        }
    }
    return 0;
}