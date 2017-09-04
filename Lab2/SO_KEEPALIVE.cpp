#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
   int socket_;
   int optval;
   socklen_t optlen = sizeof(optval);

   if((socket_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
      perror("socket()");
      exit(0);
   }

   if(getsockopt(socket_, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
      perror("getsockopt()");
      close(socket_);
      exit(0);
   }
   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

   optval = 1;
   optlen = sizeof(optval);
   if(setsockopt(socket_, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
      perror("setsockopt()");
      close(socket_);
      exit(0);
   }
   printf("SO_KEEPALIVE set on socket\n");

   if(getsockopt(socket_, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
      perror("getsockopt()");
      close(socket_);
      exit(0);
   }
   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

   close(socket_);

   return 0;
}
