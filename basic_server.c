#include "pipe_networking.h"
#include <ctype.h>


int main() {

  int to_client;
  int from_client;

  while(1){
    from_client = server_handshake( &to_client );
    char returned[BUFFER_SIZE];
    read(from_client, returned, sizeof(returned));
    while(read(from_client, returned, sizeof(returned))){
    	printf("Server: recieved %s", returned);
      int i = 0;
      while(returned[i]){
        returned[i] = toupper(returned[i]);
        i++;
      }
    	write(to_client, returned, sizeof(returned));
    }
  }
}
