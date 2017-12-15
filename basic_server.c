#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
  char returned[BUFFER_SIZE];
  read(from_client, returned, sizeof(returned));
  while(1){
  	char returned[BUFFER_SIZE];
  	read(from_client, returned, sizeof(returned));
  	printf("Server: recieved %s", returned);
  	returned[0] = 'A';
  	write(to_client, returned, sizeof(returned));
  }
}
