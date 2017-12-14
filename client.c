#include "pipe_networking.h"
#include <ctype.h>


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  while(1){
  	printf("Enter Some Text: ");
  	char line[200];
  	fgets(line, sizeof(line), stdin);
  	write(to_server, line, sizeof(line));
  	char returned[200];
  	read(from_server, returned, sizeof(returned));
  	printf("Returned: %s\n", returned);
  }
}
