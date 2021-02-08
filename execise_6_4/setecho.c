#include <errno.h>
#include <termios.h>
#include <unistd.h>

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

int setecho(int fd, int onflag)
{
    int error;
    struct termios term;
    if (tcgetattr(fd, &term) == -1)
        return -1;
    if (onflag)
        term.c_lflag |= ECHOFLAGS;
    else 
        term.c_lflag &= ~ECHOFLAGS;
    
    while((error = tcsetattr(fd, TCSAFLUSH, &term)) == -1 && errno == EINTR);
    return error;
}
