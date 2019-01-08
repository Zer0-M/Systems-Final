#include <stdio.h>
#include <stdlib.h>


struct node{
    card * prev;
    card * next;
    struct card * card;
};


struct node * addNext(struct node * this, struct card * card);
    struct node * new;
    this.next = new;
    new.prev = this;
    new.next = NULL;
    new.card = card;
    return new;
}








