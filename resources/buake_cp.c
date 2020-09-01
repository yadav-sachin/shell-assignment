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

int copyFile(char *source, char *destination)
{
    FILE *src_file, *dest_file;
    printf("%s %s\n", source, destination);
    int read_count, write_count;
    src_file = fopen(source, "r");
    if ( src_file == NULL)
    {
        text_color_red();
        printf("Cannot open %s\n", source);
        text_color_reset();
        return 1;
    }
    dest_file = fopen(destination, "w");
    if ( dest_file == NULL)
    {
        text_color_red();
        printf("Cannot create %s\n", destination);
        text_color_reset();
        return 1;
    }
    char buff[BUFF_SIZE];
    do {
        read_count = fread(buff, 1, BUFF_SIZE, src_file);
        if (read_count > 0)
            write_count = fwrite(buff, 1, read_count, dest_file);
        else write_count = 0;
    } while ( (read_count > 0) && (read_count == write_count));
    fclose(src_file);
    fclose(dest_file);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        text_color_red();
        printf("cp: missing file operand\n");
        text_color_yellow();
        printf("Try 'cp --help' for more information.\n");
        text_color_reset();
        return 1;
    }
    else if (argc == 2)
    {
        text_color_red();
        printf("cp: missing destination file operand after '%s' \n", argv[1]);
        text_color_yellow();
        printf("Try 'cp --help' for more information.\n");
        text_color_reset();
        return 1;
    }
    else {
        for (int i = 1; i < (argc - 1); ++i)
        {
            char *src = argv[i], *dest = argv[argc-1];
            printf("%d %s", i, src);
            int dest_len = strlen(dest);
            if ( access(src, R_OK) != -1)
            {
                struct stat src_stat, dest_stat;
                stat(src, &src_stat);
                if ( S_ISREG(src_stat.st_mode) )    //source is a file
                {
                    if (dest[dest_len - 1] == '/')  //destination specifies a folder
                    {
                        char *file_name = basename(src);
                        char dest_temp[256];
                        strcpy(dest_temp, dest);
                        copyFile(src, strcat(dest_temp, file_name));
                    }
                    else {                          // destination specifies a file
                        char *file_name = basename(src);
                        copyFile(src, dest);
                    }
                }
                else                                //source is a Directory
                {
                    text_color_red();
                    printf("cp: -r not specified; omitting directory '%s'\n", src);
                    text_color_reset();
                }
            }
            else {
                text_color_red();
                printf("cp: cannot stat '%s': No such file or directory\n", src);
                text_color_reset();
            }
        }
    }
    return 0;
}