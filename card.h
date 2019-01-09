#include <stdio.h>
#include <stdlib.h>
#include "dealer.h"


struct node{
	node prev;
	node next;
	struct card card;
}

struct node addNext(struct node this, struct card card);
