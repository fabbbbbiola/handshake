#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;
  char buffer[BUFFER_SIZE];
  from_client = server_handshake( &to_client );
  
  while(1){
    read(from_client, buffer, sizeof(buffer));
    printf("message received: %s\n", buffer);
    int i;
    for ( i=0 ; buffer[i]; i++){
      buffer[i] = toupper(buffer[i]);
    }
    printf("new message: %s\n", buffer);
    write(to_client, buffer, sizeof(buffer));
  }

  return 0;
}
