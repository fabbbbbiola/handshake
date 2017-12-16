#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char hndshk[HANDSHAKE_BUFFER_SIZE];
  memset(hndshk, 0, 256);
  mkfifo("pipeA", 0664);
  int from_client = open("pipeA", O_RDONLY);
  read(from_client, hndshk, sizeof(hndshk));
  *to_client = open(hndshk, O_WRONLY);
  write(*to_client, "done", 256);
  //check the check:
  int cnc = read(from_client, hndshk, sizeof(hndshk));
  if (cnc != -1){
    printf("successful connection\n");
  }
  remove("pipeA");
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char hndshk[HANDSHAKE_BUFFER_SIZE] = "pipeB";
  int buffer[BUFFER_SIZE];
  *to_server = open("pipeA", O_WRONLY);
  write(*to_server, hndshk, sizeof(hndshk));
  mkfifo(hndshk, 0664);
  int from_server = open(hndshk, O_RDWR);
  int c = read(from_server, buffer, sizeof(buffer));
  if (c != -1){
    printf("successful connection\n");
    write(to_server, "received", 256);
  }
  else{
    printf("something went wrong oh noes");
  }

  remove(hndshk);
  return from_server;
}
