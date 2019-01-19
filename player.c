
#include "networking.h"


int main(int argc, char **argv) {

  	int to_server;
  	int from_server;
    if (argc == 2)
      from_server = client_setup( argv[1]);
    else
      from_server = client_setup( TEST_IP );
  	//from_server = //client_handshake( &to_server );
  	while(1){
      char buff[1000];
      read(from_server,buff,1000);
      printf("%s\n",buff);
    	char * response=calloc(BUFFER_SIZE,sizeof(char));
    	printf("Note: +2 - adds two cards to next players hand\nX- skip next players turn\nR- change direction of turns\nW - change color being played\nW4 - change color and add 4 cards to next players hand\n");
    	printf("Please play a card from a hand in this format:color name\nexamples:red 4,red +2,green R,blue X, W4\n");
    	printf("Select Card From Hand:");
    	fgets(response,BUFFER_SIZE,stdin);
    	response[strlen(response)-1]='\0';
    	write(from_server,response,strlen(response));
    	free(response);
    	response=calloc(BUFFER_SIZE,sizeof(char));
    	char * data=calloc(BUFFER_SIZE,sizeof(char));
    	read(from_server,data,BUFFER_SIZE);
    	printf("The server says %s\n",data);
  	}
}
