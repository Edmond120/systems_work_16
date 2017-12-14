#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
 	if(!mkfifo("s",0666)){
		printf("server: made fifo\n");
	}
	else{
		printf("server: make fifo error\n");
		return -1;
	}
	printf("server: waiting for connection\n");
	int fd = open("s", O_RDONLY);
	char name[50];
	read(fd,name,sizeof(char) * 3);
	printf("server: connection established, deleting fifo\n");
	remove("s");
	printf("server: connecting to client\n");
    *to_client = open(name,O_WRONLY,0666);
	int buffer = 1;
	write(*to_client,&buffer,sizeof(int));
  	return fd;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
	printf("client: creating private fifo\n");
	mkfifo("ss", 0666);
  printf("client: connecting to server\n");
  int fd = open("s",O_WRONLY,0666);
	char * name = "ss";
	write(fd,name,sizeof(char) * 3);
	int buffer;
  int private_fifo = open("ss", O_RDONLY, 0666);
	printf("client: waiting for server to respond\n");
	read(private_fifo,&buffer,sizeof(int));
	printf("client: buffer = %d\n",buffer);
	if(buffer == 1){
		printf("client: message recived\n");
		remove("ss");
		printf("client: send message to server\n");
		write(fd,&buffer,sizeof(int));
	}
	*to_server = fd;
 	return private_fifo;
}
