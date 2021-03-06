#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client,int playernum, /*char * hand,*/char * pile) {
  int s2cp=mkfifo("/tmp/s2c",0644);
  if(s2cp==-1){
    printf("%s \n",strerror(errno));
  }
  //printf("Well-Known FIFO s2c created\n");
  int upstream=open("/tmp/s2c",O_RDONLY);
  if(upstream==-1){
    printf("%s \n",strerror(errno));
  }
  char buff[HANDSHAKE_BUFFER_SIZE];
  read(upstream,buff,HANDSHAKE_BUFFER_SIZE);
  char * wrfile=buff;
  //printf("Name of Client's Private Pipe Received: %s\n",wrfile);
  to_client[playernum]=open(wrfile,O_WRONLY);
  remove("/tmp/s2c");
  //printf("Removed WKP\n");
  if(to_client[playernum]==-1){
    printf("%s \n",strerror(errno));
  }
  //printf("%s\n",hand);
  //strcat(hand,pile);
  write(to_client[playernum],ACK,strlen(ACK));
  char response[HANDSHAKE_BUFFER_SIZE];
  read(upstream,response,HANDSHAKE_BUFFER_SIZE);
  //printf("Response received from client: %s\n",response);
  printf("Handshake Complete\n");
  s2cp=mkfifo("/tmp/s2c",0644);
  if(s2cp==-1){
    printf("%s \n",strerror(errno));
  }
  return upstream;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int pid=getpid();
  char privatepipe[10];
  sprintf(privatepipe,"/tmp/%d",pid);
  int c2sp=mkfifo(privatepipe,0644);
  if(c2sp){
    printf("%s \n",strerror(errno));
  }
  *to_server=open("/tmp/s2c",O_WRONLY);
  if(*to_server==-1){
    printf("%s \n",strerror(errno));
  }
  write(*to_server,privatepipe,HANDSHAKE_BUFFER_SIZE);
  //printf("Sent FIFO name: %s\n",privatepipe);
  int downstream=open(privatepipe,O_RDONLY);
  if(downstream==-1){
    printf("%s \n",strerror(errno));
  }
  char * buff=calloc(sizeof(char),1000);
  read(downstream,buff,1000);
  printf("Cards in your hand:\n%s\n",buff);
  remove(privatepipe);
  //printf("Private FIFO removed\n");
  write(*to_server,ACK,HANDSHAKE_BUFFER_SIZE);
  //printf("Response sent to server\n");
  printf("Handshake complete\n");
  return downstream;
}
