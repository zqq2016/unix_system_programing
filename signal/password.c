#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>
#include "restart.h"

int setecho(int fd, int onflag);

int