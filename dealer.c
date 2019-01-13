#include "pipe_networking.h"
#include "dealer.h"

/*
void createDeck(struct card * deck){
    char colors[4][20] = {"red","green","blue","yellow"};
    int cardnum=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<10;j++){
          for(int num=0;(j>=1||num<1)&&num<2;num++){
            deck[cardnum].color=colors[i];
            deck[cardnum].face.number=j;
            deck[cardnum].action=0;
            cardnum++;
          }
        }
        for(int j=0;j<2;j++){
          deck[cardnum].color=colors[i];
          deck[cardnum].face.name="Reverse";
          deck[cardnum].action=1;
          cardnum++;
          deck[cardnum].color=colors[i];
          deck[cardnum].face.name="DrawTwo";
          deck[cardnum].action=1;
          cardnum++;
          deck[cardnum].color=colors[i];
          deck[cardnum].action=1;
          deck[cardnum].face.name="Skip";
          cardnum++;
        }
    }
    for(int i=0;i<4;i++){
        deck[cardnum].color="";
        deck[cardnum].face.name="Wild";
        deck[cardnum].action=1;
        cardnum++;
        deck[cardnum].color="";
        deck[cardnum].face.name="Wild 4";
        deck[cardnum].action=1;
        cardnum++;
    }
}
*/

struct card * makeCard(char * color, char * name, int action){
	struct card * temp = calloc(sizeof(struct card),1);
	strcpy(temp->color,color);
	strcpy(temp->name,name);
	temp->action=action;
	return temp;
}

struct node * makeNode(struct node * prev, struct node * next, struct card * card){
	struct node * temp = calloc(sizeof(struct node),1);
	temp->prev = prev;
	temp->next = next;
	prev->next = temp;
	temp->card = card;
	return temp;
}

struct node * createNodeDeck(){
	struct node * first = calloc(sizeof(struct node),1);
	first->prev = NULL;
	first->next = NULL;
	first->card = makeCard("white","test",0);
	struct node * curr = first;
	char colors[4][20] = {"red","green","blue","yellow"};
	char names[10][5] = {"0","1","2","3","4","5","6","7","8","9"};
    int cardnum=0;
    struct node * temp;
    for(int i=0;i<4;i++){
        for(int j=0;j<10;j++){
		    for(int num=0;(j>=1||num<1)&&num<2;num++){
				temp = makeNode(curr, NULL, makeCard(colors[i],names[j],0));
			/*	temp = calloc(sizeof(struct node),1);
				temp->prev = curr;
				temp->next = NULL;
				curr->next = temp;
           *	temp->card.color=colors[i];
            	temp->card.name=names[j];
            	temp->card.action=0;*
				temp->card = makeCard(colors[i], names[j], 0);
			*///	printf("printing %s %s, %s %s, %d\n", temp->card->color, colors[i], temp->card->name, names[j], temp->card->action);
				curr = temp;
          		cardnum++;
			//	printf("%s, %s\n",temp->card->color, temp->card->name);
            }
        }
        for(int j=0;j<2;j++){
        	temp = calloc(sizeof(struct node),1);
			temp->prev = curr;
			temp->next = NULL;
			curr->next = temp;
		/*	temp->card.color=colors[i];
        	temp->card.name="Reverse";
          	temp->card.action=1;*/
			temp->card = makeCard(colors[i], "Reverse", 1);
          	curr = temp;
			cardnum++;
          	
			temp = calloc(sizeof(struct node),1);
			temp->prev = curr;
			temp->next = NULL;
			curr->next = temp;
		/*	temp->card.color=colors[i];
          	temp->card.name="DrawTwo";
          	temp->card.action=1;*/
			temp->card = makeCard(colors[i], "DrawTwo", 1);
			curr = temp;
          	cardnum++;

			temp = calloc(sizeof(struct node),1);
			temp->prev = curr;
			temp->next = NULL;
			curr->next = temp;
		/*	temp->card.color=colors[i];
          	temp->card.action=1;
          	temp->card.name="Skip";*/
			temp->card = makeCard(colors[i], "Skip", 1);
			curr = temp;
          	cardnum++;
        }
    }
    for(int i=0;i<4;i++){
		temp = calloc(sizeof(struct node),1);
		temp->prev = curr;
		temp->next = NULL;
		curr->next = temp;
	/*	temp->card.color="";
        temp->card.name="Wild";
        temp->card.action=1;*/
		temp->card = makeCard("", "Wild", 1);
		curr = temp;
        cardnum++;

		temp = calloc(sizeof(struct node),1);
		temp->prev = curr;
		temp->next = NULL;
		curr->next = temp;
	/*	temp->card.color="";
        temp->card.name="Wild 4";
        temp->card.action=1;*/
		temp->card = makeCard("", "Wild 4", 1);
		curr = temp;
        cardnum++;
    }
	return first;
}
struct node * createHand(struct node * first){
	struct node * curr;
	if(strcmp(first->card->color,"white")){
		curr = first->next;
	}
	else{
		curr =first;
	}
	for(int i=0;i<7;i++){
		curr=curr->next;
	}
	struct node * temp= malloc(sizeof(struct node *));
	temp->card=makeCard(curr->card->color,curr->card->name,0);
	temp->next=curr->next;
	curr->next=NULL;
	curr=first->next;
	*first=*temp;
	return curr;
}
char * handToString(struct node * hand){
	struct node * temp=hand;
	char * handstr=malloc(1000);
	while(temp){
		strcat(handstr,temp->card->color);
		strcat(handstr," ");
		strcat(handstr,temp->card->name);
		strcat(handstr," ");
		temp=temp->next;
	}
	return handstr;
}

int main() {
  struct node * deck = createNodeDeck();
	struct node ** hands=calloc(sizeof(struct node *),2);
	for(int i=0;i<3;i++){
		hands[i]=createHand(deck);
	}	
	printf("%s\n",handToString(hands[0]));
  //signal(SIGINT,sighandler);
  int to_client[2];
  int from_client[2];
  int i=0;
  while(1){
    while(i<2){
      from_client[i] = server_handshake( to_client,i, handToString(hands[i]));
      i++;
    }
    i=0;
    char * data=calloc(BUFFER_SIZE,sizeof(char));
    while(read(from_client[i],data,BUFFER_SIZE)){
      printf("The player played %s",data);
      fflush(stdout);
      char * response=data;
      write(to_client[i],response,strlen(response));
      free(data);    
      i++;
      if(i==2){
        i=0;
      }
    }
  }
}


/*int main(){
//	struct node * first = calloc(sizeof(struct node),1);
//	struct node * curr;
	struct node * first = createNodeDeck();
	struct node * curr = first->next;
	while (curr->next){
	//	curr = curr->next;
		printf("%s %s\n",curr->card->color,curr->card->name);
		curr = curr->next;
	}
}*/
