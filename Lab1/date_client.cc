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
  struct sockaddr_in server_addr, client_addr;
  struct hostent *server;
  port_num = atoi(argv[2]);
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
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

  client_addr.sin_family = AF_INET;
  client_addr.sin_addr.s_addr = INADDR_ANY;
  client_addr.sin_port = htons(0);
  if (bind(socket_fd, (struct sockaddr *) &client_addr, sizeof(client_addr)) < 0) {
    printf("Error: Error while binding socket to the giving port and socket family\n");
    exit(1);
  }
  char buffer[256];
  socklen_t server_addr_len = sizeof(server_addr);
  fgets(buffer, 255, stdin);
  int n = sendto(socket_fd, buffer, 255, 0, (struct sockaddr *) &server_addr, server_addr_len);
  n = recvfrom(socket_fd, &buffer, 255, 0, (struct sockaddr *) &server_addr, &server_addr_len);
  if (n < 0) {
    printf("Error: Error while receiving message from the client.");
    exit(1);  
  } 
  printf("Current date and time: %s\n", buffer);
  close(socket_fd);  
  return 0;
}
