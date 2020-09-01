#include <stdio.h>
#include <libgen.h>

int main()
{
    char str[250];
    scanf("%s", str);
    char *file_name = basename(str);
    printf("%s", file_name);
    return 0;
}