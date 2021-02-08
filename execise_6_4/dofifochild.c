#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 256
#define FIFO_MODES O_WRONLY

int dofifochild(const char *fifoname, const char *idstring)
{
    char buf[BUFSIZ];
    int fd;
    int rval;
    ssize_t strsize;

    fprintf(stderr, "[%ld]: (child) about to open fifo %s...\n", (long)getpid(), fifoname);
    while (((fd = open(fifoname, FIFO_MODES)) == -1) && errno == EINTR);
    if (fd == -1)
    {
        fprintf(stderr, "[%ld]: failed to open named pipe %s for read:%s\n", (long)getpid(), fifoname, strerror(errno));
        return 1;
    }
    rval = snprintf(buf, BUFSIZ, "[%ld]:%s\n", (long)getpid(), idstring);
    strsize = strlen(buf) - 1;
    fprintf(stderr, "[%ld]:about f5 write...\n", (long)getpid());
    rval = write(fd, buf, strsize);
    if (rval != strsize)
    {
        fprintf(stderr, "[%ld]: failed to write to pipe: %s\n", (long)getpid(), fifoname);
        return 1;
    }
    fprintf(stderr, "[%ld]: finishing...\n", (long)getpid());
    return 0;
}