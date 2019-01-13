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
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define WHT  "\x1B[37m"

struct card {
    char color[20];
    char name[5];
	int action;
};

struct node {
	struct node * prev;
	struct node * next;
	struct card * card;
};

//void createDeck(struct card* deck);

struct card * makeCard(char * color, char * name, int action);

struct node * makeNode(struct node * prev, struct node * next, struct card * card);

//void createNodeDeck(struct node * first);

struct node * createNodeDeck();
