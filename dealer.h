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
#include "card.h"

struct card {
    char * color;
    int action;
    char * name;
};


void createDeck(struct card* deck);

void createNodeDeck(struct node first);
