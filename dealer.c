#include "dealer.h"
#include "networking.h"

struct card *makeCard(char *color, char *name, int action)
{
	struct card *temp = calloc(sizeof(struct card), 1);
	strcpy(temp->color, color);
	strcpy(temp->name, name);
	temp->action = action;
	return temp;
}

struct node *makeNode(struct node *prev, struct node *next, struct card *card)
{
	struct node *temp = calloc(sizeof(struct node), 1);
	temp->prev = prev;
	temp->next = next;
	prev->next = temp;
	temp->card = card;
	return temp;
}
int length(struct node *first)
{
	int count = 0;
	struct node *temp = first->next;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return count;
}
int indexOf(struct node *deck, char *card)
{
	int index = 0;
	while (deck->next)
	{
		if (!cardcmp(deck, card, 1))
		{
			return index;
		}
		index++;
		deck = deck->next;
	}
	return -1;
}
struct node *play(struct node *deck, int index, struct node *pile)
{
	struct node *first = malloc(sizeof(struct node));
	if (index == 0)
	{
		first = deck->next;
		deck = NULL;
	}
	else
	{
		first = deck;
		int i = 0;
		for (; i < index - 1; i++)
		{
			deck = deck->next;
		}
		pile = deck->next;
		pile->next=NULL;
		deck->next = deck->next->next;
	}
	return first;
}
int cardcmp(struct node *card, char *info, int exact)
{
	char *color = calloc(sizeof(char), 10);
	char *number = calloc(sizeof(char), 2);
	char *str = calloc(sizeof(char), 20);
	strcpy(str, info);
	char *token = strtok(str, " ");
	int i = 0;
	while (token != NULL)
	{
		if (i == 0)
		{
			color = token;
		}
		if (i == 1)
		{
			number = token;
		}
		token = strtok(NULL, " ");
		i++;
	}
	if (exact)
	{
		return strcmp(card->card->color, color) + strcmp(card->card->name, number);
	}
	return strcmp(card->card->color, color) * strcmp(card->card->name, number);
}
char * pileToString(struct node * pile){
	while(pile->next){
		pile=pile->next;
	}
	char *handstr = malloc(1000);
	char *color;
	char *cardface = malloc(1000);
	if (strlen(pile->card->name) > 1)
	{
		sprintf(cardface, "########\n#      #\n#  %s  #\n#      #\n########\n", pile->card->name);
	}
	else
	{
		sprintf(cardface, "########\n#      #\n#   %s  #\n#      #\n########\n", pile->card->name);
	}
	if (!strcmp(pile->card->color, "red"))
	{
		color = RED;
	}
	else if (!strcmp(pile->card->color, "green"))
	{
		color = GRN;
	}
	else if (!strcmp(pile->card->color, "yellow"))
	{
		color = YEL;
	}
	else if (!strcmp(pile->card->color, "blue"))
	{
		color = BLU;
	}
	else
	{
		color = WHT;
	}
	strcat(handstr, color);
	strcat(handstr, cardface);
	strcat(handstr,WHT);
	return handstr;
}

struct node *shuffle(struct node *first)
{
	struct node **arr = calloc(sizeof(struct node *), 110);
	arr[0] = first;
	srand(time(NULL));
	struct node *curr = first->next;
	while (curr)
	{
		int index = rand() % 108 + 1; //random index from 1 to 108
		while (arr[index])
		{
			index = rand() % 108 + 1; //repeat until empty area
		}
		arr[index] = curr;
		curr = curr->next;
	}
	for (int i = 1; i < 109; ++i)
	{ //0 is white, 1 to 108 are random, 109 is NULL
		arr[i]->next = arr[i + 1];
		arr[i]->prev = arr[i - 1];
	}
	arr[0]->next = arr[1];
	return first;
}

struct node *createNodeDeck()
{
	struct node *first = calloc(sizeof(struct node), 1);
	first->prev = NULL;
	first->next = NULL;
	first->card = makeCard("white", "test", 0);
	struct node *curr = first;
	char colors[4][20] = {"red", "green", "blue", "yellow"};
	char names[10][5] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	int cardnum = 0;
	struct node *temp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int num = 0; (j >= 1 || num < 1) && num < 2; num++)
			{
				temp = makeNode(curr, NULL, makeCard(colors[i], names[j], 0));
				curr = temp;
				cardnum++;
			}
		}
		for (int j = 0; j < 2; j++)
		{
			temp = calloc(sizeof(struct node), 1);
			temp->prev = curr;
			temp->next = NULL;
			curr->next = temp;
			temp->card = makeCard(colors[i], "R", 1);
			curr = temp;
			cardnum++;

			temp = calloc(sizeof(struct node), 1);
			temp->prev = curr;
			temp->next = NULL;
			curr->next = temp;
			temp->card = makeCard(colors[i], "+2", 1);
			curr = temp;
			cardnum++;

			temp = calloc(sizeof(struct node), 1);
			temp->prev = curr;
			temp->next = NULL;
			curr->next = temp;
			temp->card = makeCard(colors[i], "X", 1);
			curr = temp;
			cardnum++;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		temp = calloc(sizeof(struct node), 1);
		temp->prev = curr;
		temp->next = NULL;
		curr->next = temp;
		temp->card = makeCard("", "W", 1);
		curr = temp;
		cardnum++;

		temp = calloc(sizeof(struct node), 1);
		temp->prev = curr;
		temp->next = NULL;
		curr->next = temp;
		temp->card = makeCard("", "W4", 1);
		curr = temp;
		cardnum++;
	}
	return first;
}
struct node *createHand(struct node *first)
{
	struct node *curr;
	if (strcmp(first->card->color, "white"))
	{
		curr = first->next;
	}
	else
	{
		curr = first;
	}
	for (int i = 0; i < 7; i++)
	{
		curr = curr->next;
	}
	struct node *temp = malloc(sizeof(struct node *));
	temp->card = makeCard(curr->card->color, curr->card->name, 0);
	temp->next = curr->next;
	curr->next = NULL;
	curr = first->next;
	*first = *temp;
	return curr;
}
void draw(struct node *first, struct node *hand)
{
	struct node *curr;
	if (strcmp(first->card->color, "white"))
	{
		curr = first->next;
	}
	else
	{
		curr = first;
	}
	struct node *temp = malloc(sizeof(struct node *));
	temp->card = makeCard(curr->card->color, curr->card->name, 0);
	temp->next = curr->next;
	curr->next = NULL;
	curr = first->next;
	*first = *temp;
	struct node *end = hand;
	while (end->next)
	{
		end = end->next;
	}
	end->next = curr;
}
char *handToString(struct node *hand)
{
	int len = length(hand);
	struct node **arr = calloc(sizeof(struct node), len);
	/*temp = hand;
	while (hand->next)
	{
		hand = hand->next;
	}
	hand->next = temp;
	hand=temp;*/
	int index = 0;
	while (hand->next)
	{
		arr[index] = hand;
		hand = hand->next;
		index++;
	}
	char *handstr = malloc(1000);
	char *color;
	char *cardface;
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < len; i++)
		{
			if (!strcmp(arr[i]->card->color, "red"))
			{
				color = RED;
			}
			else if (!strcmp(arr[i]->card->color, "green"))
			{
				color = GRN;
			}
			else if (!strcmp(arr[i]->card->color, "yellow"))
			{
				color = YEL;
			}
			else if (!strcmp(arr[i]->card->color, "blue"))
			{
				color = BLU;
			}
			else
			{
				color = WHT;
			}
			strcat(handstr, color);
			if (j == 0 || j == 4)
			{
				if (i == 0)
				{
					strcat(handstr, "######## ");
				}
				else if (i == len - 1)
				{
					strcat(handstr, "########\n");
				}
				else
				{
					strcat(handstr, "######## ");
				}
			}
			else if (j == 1 || j == 3)
			{
				if (i == len - 1)
				{
					strcat(handstr, "#      #\n");
				}
				else
				{
					strcat(handstr, "#      # ");
				}
			}
			else if (j == 2)
			{
				cardface = malloc(100);
				if (i == len - 1)
				{
					if (strlen(arr[i]->card->name) < 2)
					{
						sprintf(cardface, "#   %s  #\n", arr[i]->card->name);
					}
					else
					{
						sprintf(cardface, "#  %s  #\n", arr[i]->card->name);
					}

					strcat(handstr, cardface);
				}
				else
				{
					if (strlen(arr[i]->card->name) < 2)
					{
						sprintf(cardface, "#   %s  # ", arr[i]->card->name);
					}
					else
					{
						sprintf(cardface, "#  %s  # ", arr[i]->card->name);
					}

					strcat(handstr, cardface);
				}
			}
		}
	}
	strcat(handstr, WHT);
	return handstr;
}

int main()
{
	struct node *deck = createNodeDeck();
	struct node *pile = malloc(sizeof(struct node));
	deck = shuffle(deck);
	pile=deck->next;
	deck=deck->next->next;
	pile->next=NULL;
	struct node **hands = calloc(sizeof(struct node *), 2);
	for (int i = 0; i < 13; i++)
	{
		hands[i] = createHand(deck);
	}
	printf("%s %s\n",pile->card->color,pile->card->name);
	//signal(SIGINT,sighandler);
	int socket = 0;
	socket = server_setup();
	int to_client[2];
	int from_client[2];
	int i = 0;
	while (1)
	{
		char *response = calloc(sizeof(char), 1000);
		while (i < 2)
		{
			response = calloc(sizeof(char), 1000);
			if(i!=0){
				sprintf(response, "\nDiscard Pile:\n%s\n[Player %d]", pileToString(pile),i+1);
			}
			else{
				sprintf(response, "\nDiscard Pile:\n%s\n[Player %d]", pileToString(pile),i+1);
			}

			from_client[i] = server_connect(socket,handToString(hands[i]),response); //server_handshake(to_client, i,handToString(hands[i]),response);
			printf("%d\n",i);
			free(response);

			i++;
		}
		i = 0;
		
		char *data = calloc(BUFFER_SIZE, sizeof(char));
		while (read(from_client[i], data, BUFFER_SIZE))
		{	
			printf("sd index: %d\n",i);
			char *hand = handToString(hands[i % 2]);
			response = calloc(sizeof(char), 1000);
			printf("data: %s card:%s %s Result %d\n",data,pile->card->color,pile->card->name,cardcmp(pile, data, 0));
			if (indexOf(hands[i % 2], data) >= 0 && !cardcmp(pile, data, 0))
			{
				hands[i % 2] = play(hands[i % 2], indexOf(hands[i % 2], data), pile);
				hand = handToString(hands[i % 2]);
				sprintf(response, "\nDiscard Pile:\n%s\nWait for Your Turn\n", pileToString(pile));
				write(from_client[i],response,strlen(response));
				printf("The player played %s\n", data);
				fflush(stdout);
				data = calloc(BUFFER_SIZE, sizeof(char));
				i++;
				if(i==2){
					i=0;
				}
			}
			else if(!strcmp(data,"draw")){
				draw(deck,hands[i % 2]);
				write(from_client[i],handToString(hands[i % 2]),strlen(handToString(hands[i % 2])));
				i++;
				if(i==2){
					i=0;
				}
			}
			else if(indexOf(hands[i % 2], data)<0){
				strcat(response,"Card not in hand\n Choose Again:");
			}
			else{
				strcat(response,"Card does not match pile\n Choose Again:");
			}
			free(response);
		}
	}
}
