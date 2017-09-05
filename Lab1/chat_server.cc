#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main (int argc, char *argv[]) {
  if (argc < 2) {
    printf("Error: Less arguments provided.\n");
    exit(1);  
  }
  int socket_fd, new_socket_fd, port_num;
  socklen_t client_addr_len;
  char buffer[256];
  struct sockaddr_in server_addr, client_addr;
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    printf("Error: Error while creating socket for the server.\n");  
    exit(1);
  }
  bzero((char *)&server_addr, sizeof(server_addr));
  port_num = atoi(argv[1]);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port_num);
  
  if (bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    printf("Error: Error while binding socket to the giving port and socket family\n");
    exit(1);  
  }
  listen(socket_fd, 10);
  client_addr_len = sizeof(client_addr);
  new_socket_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &client_addr_len);
  if (new_socket_fd < 0) {
    printf("Error: Error while accepting connection from a client.\n");
    exit(1);  
  }
  printf("Server received connection from %s port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
  bzero(buffer, 256);
  if(read(new_socket_fd, buffer, 255) < 0) {
    printf("Error: Error while reading message from the client.\n");
    exit(1);
  }
  printf("Message received from client: %s\n", buffer);
  printf("Write a message for the client:");
  bzero(buffer, 256);
  fgets(buffer, 255, stdin);
  send(new_socket_fd, buffer, 255, 0);
  close(new_socket_fd);
  close(socket_fd);
  return 0;
}
