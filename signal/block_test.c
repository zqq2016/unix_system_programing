
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int block_test(int argc, char *argv[])
{
    int i;
    sigset_t intmask;
    int repeactfactor;
    double y = 0.0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage:%s repeactfator\n", argv[0]);
        return 1;
    }
    repeactfactor = atoi(argv[1]);
    if ((sigemptyset(&intmask) == -1) || (sigaddset(&intmask, SIGINT) == -1))
    {
        perror("failed to initialize the signal mask");
        return 1;
    }

    for (; ;)
    {
        if (sigprocmask(SIG_BLOCK, &intmask, NULL) == -1)
            break;
        fprintf(stderr, "SIGINT signal blocked\n");
        for (i = 0; i < repeactfactor; i++)
        {
            y += sin((double)y);
        }
        fprintf(stderr, "Blocked calculation is finished y = %f\n", y);
        
        if (sigprocmask(SIG_UNBLOCK, &intmask, NULL) == -1)
            break;
        fprintf(stderr, "SIGINT signal unblocked\n");
        for (i = 0; i < repeactfactor; i++)
        {
            y += sin((double)y);
        }
        fprintf(stderr, "UNBlocked calculation is finished y = %f\n", y);
    }
    perror("failed to change signal mask");
    return 1;
}