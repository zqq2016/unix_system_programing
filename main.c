#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>

typedef int(*exec_entry)(int argc, char *argv[]);
int main(int argc, char *argv[])
{

    void *p_dlhandle;
    exec_entry entry;
    char *error_info;
    if (argc < 2)
    {
        printf("Usage: %s exec_name [param,]\n", argv[0]);
        return 0;
    }

    p_dlhandle = dlopen(NULL, RTLD_LAZY|RTLD_GLOBAL);
    if (p_dlhandle == NULL)
    {
        printf("dlopen failed\n");
        return 0;
    }
    dlerror();
    entry = dlsym(p_dlhandle, argv[1]);
    error_info = dlerror();
    if (error_info != NULL)
    {
        printf("find \"%s\" failed:%s\n", argv[1], error_info);
        return 0;
    }

    entry(argc-1, argv + 1);
}