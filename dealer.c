#include "pipe_networking.h"
#include "dealer.h"
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



int main() {
  struct card deck[108];
  createDeck(deck);
  //signal(SIGINT,sighandler);
  int to_client[2];
  int from_client[2];
  int i=0;
  while(1){
    while(i<2){
      printf("Waiting For at least two players\n");
      from_client[i] = server_handshake( to_client,i );
      i++;
    }
    i=0;
    char * data=calloc(BUFFER_SIZE,sizeof(char));
    while(read(from_client[i],data,BUFFER_SIZE)){
      printf("Player %d's Turn\n",i);
      printf("The player played %s\n",data);
      fflush(stdout);
      char * response=calloc(BUFFER_SIZE,sizeof(char));
      strcpy(response,data);
      write(to_client[i],response,strlen(response));
      free(response);
      free(data);
      response=calloc(BUFFER_SIZE,sizeof(char));
      data=calloc(BUFFER_SIZE,sizeof(char));
      i++;
      if(i==2){
        i=0;
      }
    }
  }
}