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
    char * color;
    char * name;
	int action;
};

struct node {
	struct node * prev;
	struct node * next;
	struct card * card;
};

//void createDeck(struct card* deck);

struct card * makeCard(char * color, char * name, int action);

void createNodeDeck(struct node * first);
