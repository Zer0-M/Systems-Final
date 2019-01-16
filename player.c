
#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  while(1){
    char * response=calloc(BUFFER_SIZE,sizeof(char));
    printf("Note: +2 - adds two cards to next players hand\nX- skip next players turn\nR- change direction of turns\nW - change color being played\nW4 - change color and add 4 cards to next players hand\n");
    printf("Please play a card from a hand in this format:color name\nexamples:red 4,red +2,green R,blue X, W4\n");
    printf("Select Card From Hand:");
    fgets(response,BUFFER_SIZE,stdin);
    response[strlen(response)-1]='\0';
    write(to_server,response,strlen(response));
    free(response);
    response=calloc(BUFFER_SIZE,sizeof(char));
    char * data=calloc(BUFFER_SIZE,sizeof(char));
    read(from_server,data,BUFFER_SIZE);
    printf("The server says %s\n",data);
  }
}