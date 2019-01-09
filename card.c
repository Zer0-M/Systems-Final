#include <stdio.h>
#include <stdlib.h>
#include "card.h"




struct node addNext(struct node this, struct card card);
    struct node new;
    this.next = new;
    new.prev = this;
    new.next = NULL;
    new.card = card;
    return new;
}








