#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 256
#define FIFO_MODES O_RDONLY

int dofifoparent(const char *fifoname)
{
    char buf[BUFSIZ];
    int fd;
    int rval;
    fprintf(stderr, "[%ld]: (parent) about to open fifo %s...\n", (long)getpid(), fifoname);
    sleep(10);
    while(((fd = open(fifoname, FIFO_MODES)) == -1) && errno == EINTR);
    if (fd == -1)
    {
        fprintf(stderr, "[%ld]: failed to open named pipe %s for read:%s\n", (long)getpid(), fifoname, strerror(errno));
        return 1;
    }
    fprintf(stderr, "[%ld]:about to read...\n", (long)getpid());
    rval = read(fd, buf, BUFSIZ);
    if (rval == -1)
    {
        fprintf(stderr, "[%ld]:failed to read from pipe: %s\n", (long)getpid(), fifoname);
        return 1;
    }

    fprintf(stderr, "[%ld]:read %.*s\n", (long)getpid(), rval, buf);
    return 0;
}