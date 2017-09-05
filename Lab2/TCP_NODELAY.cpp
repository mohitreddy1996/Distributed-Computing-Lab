/*
 * Nagle's algorithm: Means to improve efficiency of TCP/IP networks by reducing
 * the number of packets that need to be sent over the network. 
 * Application repeatedly emits data in small chunks causing huge overhead. 
 * Nagle's algorithm works by combining a number of small outgoing messages 
 * and sending them all at once. Specifically, as long as there is a sent 
 * packet for which the sender has received an ack, the sender should keep
 * buffering its output until it has a full packet's worth of output, 
 * thus allowing output to be sent all at once.
 */

#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
   int socket_;
   int tcp_nodelay_set;
   socklen_t opt_len = sizeof(tcp_nodelay_set);

   if((socket_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
      perror("socket()");
      exit(0);
   }

   if(getsockopt(socket_, IPPROTO_TCP, TCP_NODELAY, &tcp_nodelay_set, &opt_len) < 0) {
      perror("getsockopt()");
      close(socket_);
      exit(0);
   }
   printf("TCP_NODELAY is %s\n", (tcp_nodelay_set ? "ON" : "OFF"));

   tcp_nodelay_set = 1;
   opt_len = sizeof(tcp_nodelay_set);
   if(setsockopt(socket_, IPPROTO_TCP, TCP_NODELAY, (char *)&tcp_nodelay_set, opt_len) < 0) {
      perror("setsockopt()");
      close(socket_);
      exit(0);
   }
   printf("TCP_NODELAY set on socket\n");

   if(getsockopt(socket_, IPPROTO_TCP, TCP_NODELAY, &tcp_nodelay_set, &opt_len) < 0) {
      perror("getsockopt()");
      close(socket_);
      exit(0);
   }
   printf("TCP_NODELAY is %s\n", (tcp_nodelay_set ? "ON" : "OFF"));

   close(socket_);

   return 0;
}
