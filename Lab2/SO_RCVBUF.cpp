/*
 * Sets or gets the maximum socket receive buffer in bytes. The kernel 
 * doubles this value (to allow space for bookkeeping overhead) when it is set
 * using setsockopt. The minimum value for this option is 256. This is the doubled value.
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
   int recv_buff;
   socklen_t recv_buff_len = sizeof(recv_buff);

   if((socket_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
      perror("socket()");
      exit(0);
   }

   if(getsockopt(socket_, SOL_SOCKET, SO_RCVBUF, &recv_buff, &recv_buff_len) < 0) {
      perror("getsockopt()");
      close(socket_);
      exit(0);
   }
   // initially the value is set to 256 (doubled). Therefore ans = 256*int_bytes.
   printf("SO_RCVBUF value is %d\n", recv_buff);
   printf("Setting SO_RCVBUF to 2500 bytes.\n");
   recv_buff = 2500;
   recv_buff_len = sizeof(recv_buff);
   if(setsockopt(socket_, SOL_SOCKET, SO_RCVBUF, &recv_buff, recv_buff_len) < 0) {
      perror("setsockopt()");
      close(socket_);
      exit(0);
   }

   if(getsockopt(socket_, SOL_SOCKET, SO_RCVBUF, &recv_buff, &recv_buff_len) < 0) {
      perror("getsockopt()");
      close(socket_);
      exit(0);
   }
   printf("SO_RCVBUF is %d\n", recv_buff);

   close(socket_);

   return 0;
}
