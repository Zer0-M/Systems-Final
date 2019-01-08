#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

struct card {
    char* color;
    int action;
    union cardname{
        int number;
        char* name;
    } face;
};


void createDeck(struct card* deck);
