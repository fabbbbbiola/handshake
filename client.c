#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  char buffer[BUFFER_SIZE];
  from_server = client_handshake( &to_server );

  while(1){
    printf("enter something:");
    fgets(buffer, sizeof(buffer), stdin);
    if (strchr(buffer, '\n') == 0){
      printf("no input\n");
      exit(0);
    }
    write(to_server, buffer, sizeof(buffer));
    read(to_server, buffer, sizeof(buffer));
  }
  return 0; 
}
