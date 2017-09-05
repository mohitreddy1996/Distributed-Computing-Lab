/*
 * Sets or gets the maximum socket send buffer in bytes. The kernel doubles
 * this value (to allow space for bookkeeping overhead) when it is set using setsockopt.
 * Minimum value for this option is 2048. This is the doubled value.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
   int socket_;
   int send_buff;
   socklen_t send_buff_len = sizeof(send_buff);

   if((socket_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
      perror("socket()");
      exit(0);
   }

   if(getsockopt(socket_, SOL_SOCKET, SO_SNDBUF, &send_buff, &send_buff_len) < 0) {
      perror("getsockopt()");
      close(socket_);
      exit(0);
   }
   // initially the value is set to 2048 (doubled). Therefore ans = 2048*int_bytes.
   printf("SO_SNDBUFF value is %d\n", send_buff);
   printf("Setting SO_SNDBUF to 2500 bytes.\n");
   send_buff = 2500;
   send_buff_len = sizeof(send_buff);
   if(setsockopt(socket_, SOL_SOCKET, SO_SNDBUF, &send_buff, send_buff_len) < 0) {
      perror("setsockopt()");
      close(socket_);
      exit(0);
   }

   if(getsockopt(socket_, SOL_SOCKET, SO_SNDBUF, &send_buff, &send_buff_len) < 0) {
      perror("getsockopt()");
      close(socket_);
      exit(0);
   }
   printf("SO_SNDBUF is %d\n", send_buff);

   close(socket_);

   return 0;
}
