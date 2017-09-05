#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

bool substring_present(char str[], char pat[]) {
	for (int i = 0; i < strlen(str); i++) {
		int k = i;
		int j = 0;
		while (k < strlen(str) && j < strlen(pat) && str[k] == pat[j]) {
			k++;
			j++;
		}
		if (j == strlen(pat))
			return true;
	}
	return false;
}

int main (int argc, char *argv[]) {
  if (argc < 2) {
    printf("Error: Less arguments provided.\n");
    exit(1);  
  }
  int socket_fd, port_num;
  socklen_t client_addr_len;
  char buffer[256], write_buffer[256];
  struct sockaddr_in server_addr, client_addr;
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
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
  client_addr_len = sizeof(client_addr);

  bzero(buffer, 256);
  bzero(write_buffer, 256);
  time_t raw_time;
  struct tm* time_info;
  time(&raw_time);
  time_info = localtime(&raw_time);
  int n = recvfrom(socket_fd, buffer, 255, 0, (struct sockaddr *) &client_addr, &client_addr_len);
  if (substring_present(buffer, "time")) {
  	sprintf(write_buffer, "[%d %d %d %d:%d:%d]", time_info->tm_mday, time_info->tm_mon+1, time_info->tm_year + 1900, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
  }
  if (sendto(socket_fd, write_buffer, 255, 0, (struct sockaddr *) &client_addr, client_addr_len) < 0) {
	printf("Error: Error while sending data to client.");
	exit(1);  
  }
  close(socket_fd);
  return 0;
}
