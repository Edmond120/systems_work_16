#include "pipe_networking.h"
#include <string.h>
#include <ctype.h>


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  char line[BUFFER_SIZE];
  printf("Welcome! Enter text to see it become CAPITALIZED\nHit 'Control-C' to exit\n\n");
  while(1){
  	printf("Enter Some Text: ");
  	fgets(line, sizeof(line), stdin);
    //printf("entered: %s\n", line);
  	write(to_server, line, sizeof(line));
  	char returned[BUFFER_SIZE];
  	read(from_server, returned, sizeof(returned));
  	printf("Returned: %s\n", returned);
  }
}
