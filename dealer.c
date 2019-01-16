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
int length(struct node * first){
	int count=0;
	struct node * temp=first->next;
	while(temp){
		count++;
		temp=temp->next;
	} 
	return count;
}
int indexOf(struct node * deck,char * card){
	int index=0;
	while(deck->next){
		if(!cardcmp(deck,card)){
			return index;
		}
		index++;
		deck=deck->next;
	}
	return -1;
}
struct node * play(struct node * deck,int index, struct node * pile){
	struct node * first;
	if(index==0){
		first=deck->next;
		deck=NULL;
	}
	else{
		first=deck;
		int i=0;
		for(;i<index-1;i++){
			deck=deck->next;
		}	
		struct node * temp= malloc(sizeof(struct node *));
		temp->card=makeCard(deck->next->card->color,deck->next->card->name,0);
		pile=temp;
		deck->next=deck->next->next;
	}
	return first;

}
int cardcmp(struct node * card, char * info ){
	char * color=calloc(sizeof(char),10);
	char * number=calloc(sizeof(char),2);
	char * str=calloc(sizeof(char),20);
	strcpy(str,info);
    char *token = strtok(str, " ");
	int i=0;
    while (token != NULL) 
    { 		
		if(i ==0){
			color=token;
		}
		if(i==1){
			number=token;
		}
        token = strtok(NULL, " "); 
		i++;
    }
	return strcmp(card->card->color,color) * strcmp(card->card->name,number);
}
/*
struct node * shuffle(struct node * first){ //first should be white test card
	int cards = length(first);
	srand(time(NULL));
	int index = 0;
	struct node * curr = first->next; //tracks current card in deck
	struct node * new = calloc(sizeof(struct node),1);
	new->prev = NULL;
	new->next = NULL;
	new->card = makeCard("white","test",0); //new shuffled deck
	curr->prev = NULL;
	first->next = curr->next; 
	struct node * end = new; //tracks current end of new shuffled deck
	for (int i = 107; i > 0; --i){
		index = rand() % i;
		for (int j = 0; j < index; ++j){ //navigate to index
			curr = curr->next;
		} 
		struct node * temp = curr->next;
		curr->prev->next = *temp; 
		curr->next->prev = curr->prev; //detaches current
		end->next = *curr;
		curr->prev = *end; //attaches current to end of shuffled deck
		curr = first->next;
	}
	return new;
}*/

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
			temp->card = makeCard(colors[i], "R", 1);
          	curr = temp;
			cardnum++;
          	
			temp = calloc(sizeof(struct node),1);
			temp->prev = curr;
			temp->next = NULL;
			curr->next = temp;
		/*	temp->card.color=colors[i];
          	temp->card.name="DrawTwo";
          	temp->card.action=1;*/
			temp->card = makeCard(colors[i], "+2", 1);
			curr = temp;
          	cardnum++;

			temp = calloc(sizeof(struct node),1);
			temp->prev = curr;
			temp->next = NULL;
			curr->next = temp;
		/*	temp->card.color=colors[i];
          	temp->card.action=1;
          	temp->card.name="Skip";*/
			temp->card = makeCard(colors[i], "X", 1);
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
		temp->card = makeCard("", "W", 1);
		curr = temp;
        cardnum++;

		temp = calloc(sizeof(struct node),1);
		temp->prev = curr;
		temp->next = NULL;
		curr->next = temp;
	/*	temp->card.color="";
        temp->card.name="Wild 4";
        temp->card.action=1;*/
		temp->card = makeCard("", "W4", 1);
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
void draw(struct node * first, struct node * hand){
		struct node * curr;
	if(strcmp(first->card->color,"white")){
		curr = first->next;
	}
	else{
		curr =first;
	}
	struct node * temp= malloc(sizeof(struct node *));
	temp->card=makeCard(curr->card->color,curr->card->name,0);
	temp->next=curr->next;
	curr->next=NULL;
	curr=first->next;
	*first=*temp;
	struct node * end= hand;
	while(end->next){
		end=end->next;
	}
	end->next=curr;
	curr->prev=end;
}
char * handToString(struct node * hand){
	struct node * temp=hand;
	char * handstr=malloc(1000);
	char * color;
	while(temp){
		char * cardface=malloc(1000);
		if(strlen(temp->card->name)>1){
			sprintf(cardface,"########\n#      #\n#  %s  #\n#      #\n########\n",temp->card->name);
		}
		else{
			sprintf(cardface,"########\n#      #\n#   %s  #\n#      #\n########\n",temp->card->name);
		}
		if(!strcmp(temp->card->color,"red")){
			color=RED;
		}
		else if(!strcmp(temp->card->color,"green")){
			color=GRN;
		}
		else if(!strcmp(temp->card->color,"yellow")){
			color=YEL;
		}
		else if(!strcmp(temp->card->color,"blue")){
			color=BLU;
		}
		else{
			color=WHT;
		}
		strcat(handstr,color);
		strcat(handstr,cardface);
		temp=temp->next;
	}
	return handstr;
}

int main() {
  struct node * deck = createNodeDeck();
  struct node * pile=malloc(sizeof(struct node));
  *pile=*deck->next;
  deck=deck->next;
  pile->next=NULL;
	struct node ** hands=calloc(sizeof(struct node *),2);
	for(int i=0;i<13;i++){
		hands[i]=createHand(deck);
	}
  printf("%d\n",cardcmp(hands[0],"blue 1"));	
  //signal(SIGINT,sighandler);
  int to_client[2];
  int from_client[2];
  int i=0;
  while(1){
	char * response=calloc(sizeof(char),1000);
	sprintf(response,"\nDiscard Pile:\n%s\n",handToString(pile));
    while(i<2){
      from_client[i] = server_handshake( to_client,i, handToString(hands[i]),response);
      i++;
    }
    i=0;
	char * data=calloc(BUFFER_SIZE,sizeof(char));
	free(response);
    while(read(from_client[i],data,BUFFER_SIZE)){
	  response=calloc(sizeof(char),1000);	
	  sprintf(response,"Discard Pile:\n%s\n",handToString(pile));
	  write(to_client[i],response,strlen(response));
	  free(response);
	  if(indexOf(hands[i],data)>=0){
		printf("The player played %s",data);
		play(hands[i],indexOf(hands[i],data),pile);
		fflush(stdout);
		if(strcmp(data,"W")){
			i++;
		}
		else{
			response="Pick a color";
			write(to_client[i],response,strlen(response));
		}
		free(data);
		data=calloc(BUFFER_SIZE,sizeof(char)); 
		if(i==2){
			i=0;
		}
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
