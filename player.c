
#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  while(1){
    char *response=calloc(BUFFER_SIZE,sizeof(char));
    printf("Select Card From Hand:");
    fgets(response,BUFFER_SIZE,stdin);
    response[strlen(response)-1]='\0';
    write(to_server,response,strlen(response));
    free(response);
    response=calloc(BUFFER_SIZE,sizeof(char));
    char * data=calloc(BUFFER_SIZE,sizeof(char));
    read(from_server,data,BUFFER_SIZE);
    printf("The server says %s\n",data);
    free(data);
    data=calloc(BUFFER_SIZE,sizeof(char));
  }
}