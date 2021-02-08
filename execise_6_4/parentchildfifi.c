#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 256
#define FIFO_PERM (S_IRUSR | S_IWUSR)

int dofifochild(const char *fifoname, const char *idstring);
int dofifoparent(const char *fifoname);

int main(int argc, char *argv[])
{
    pid_t child_pid;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s pipename\n", argv[0]);
    }

    if (mkfifo(argv[1], FIFO_PERM) == -1)
    {
        if (errno != EEXIST)
        {
            fprintf(stderr, "[%ld]: failed to create named pipe %s:%s\n", (long)getpid(), argv[1], strerror(errno));
            return 1;
        }
    }
    if ((child_pid = fork()) == -1)
    {
        perror("failed to fork");
        return 1;
    }
    if (child_pid == 0)
        return dofifochild(argv[1], "this was written by the child");
    else
        return dofifoparent(argv[1]);
}