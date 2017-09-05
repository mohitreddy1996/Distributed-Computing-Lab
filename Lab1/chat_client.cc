#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main (int argc, char* argv[]) {
  if (argc < 3) {
    printf("Error: Enter hostname and port number.\n");
    exit(1);
  }
  int port_num;
  int socket_fd;
  struct sockaddr_in server_addr;
  struct hostent *server;
  port_num = atoi(argv[2]);
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    printf("Error: Error while creating socket.\n");
    exit(1); 
  }
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    printf("Error: No such host.\n");
    exit(1);  
  }
  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  bcopy((char *) server->h_addr, (char *) &server_addr.sin_addr.s_addr, server->h_length);
  server_addr.sin_port = htons(port_num);
  if (connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    printf("Error: Error while connecting to the client.\n");
    exit(1);  
  }
  char client_message[256];
  fprintf(stdout, "Enter message to be sent to the server:");
  fgets(client_message, 255, stdin);
  int n = write(socket_fd, client_message, 255);
  if (n < 0) {
    printf("Error: Error while writing a message.\n");
    exit(1);    
  }
  char buffer[256];
  n = read(socket_fd, buffer, 255);
  if (n < 0) {
    printf("Error: Error while reading messages.\n");  
    exit(1);  
  }
  printf("Received message back from client: %s\n", buffer);
  close(socket_fd);  
  return 0;
}
