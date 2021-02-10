#include <unistd.h>
#include <stdio.h>

int setecho(int fd, int onflag);

int test(int argc, char *argv[])
{
    printf("argc:%d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("[%d]:%s\n", i, argv[i]);
    }
    setecho(STDIN_FILENO, 1);
    return 0;
}