struct card[52] createDeck(){
    struct card[52] deck;
    char colors[4][20] = ["red","green","blue","yellow"];
    int cardnum=0;
    for(int i=0;i<5;i++){
        for(int j=0;j<10;j++){
            card[cardnum]->color=colors[i];
            card[cardnum].number=j;
            cardnum++;
        }
    }
    return deck;
}



int main() {
  signal(SIGINT,sighandler);
  int to_client;
  int from_client;
  while(1){
    from_client = server_handshake( &to_client );
    char * data=calloc(BUFFER_SIZE,sizeof(char));

    while(read(from_client,data,BUFFER_SIZE)){
      printf("The player played %s",data);
      char * response=data;
      write(to_client,response,strlen(response));
      free(data);
    }
  }
}