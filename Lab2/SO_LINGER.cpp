/*
 * struct linger {
 *  int l_onoff; // linger active
 *  int l_linger; // how many seconds to linger for.
 * };
 * When enabled, a close(2) or shutdown(2) will not return until all 
 * queued messages for the socket have been successfully sent or linger 
 * timeout has been reached. Otherwise the call returns immediately and closing is done in the background.
 *
 * l_onoff is boolean. 
 * - When l_onoff is false, l_linger does not matter. The data is sent after close(2) is called only if possible.
 * - l_onoff is true, l_linger is non-zero, it is the timeout period to be applied at close(2) time. If pending data and successful close occur before timeout, successful return else error. If l_linger is zero causes the connection to be aborted and pending data is immediately discared upon close(2).
 */

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
  struct linger so_linger;
  int socket_;
  socklen_t so_linger_len = sizeof(so_linger);
  // create a socket.
  if ((socket_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror ("Error while creating socket()");
    exit (0);
  }

  if (getsockopt(socket_, SOL_SOCKET, SO_LINGER, &so_linger, &so_linger_len) < 0) {
    perror("Error while getting so_linger options for the socket.");
    close(socket_);
    exit (0);
  }
  printf("l_onoff is %s with l_linger %d\n", (so_linger.l_onoff > 0 ? "true" : "false"), so_linger.l_linger);

  // Set socket options.
  so_linger.l_onoff = 1;
  so_linger.l_linger = 5; // Set it to 5 seconds.
  so_linger_len = sizeof(so_linger);
  if (setsockopt(socket_, SOL_SOCKET, SO_LINGER, &so_linger, so_linger_len) < 0) {
    perror("setsockopt()");
    close(socket_);
    exit(0);
  }
  printf("SO_LINGER set on socket.\n");
  
  // Get socket options.
  if (getsockopt(socket_, SOL_SOCKET, SO_LINGER, &so_linger, &so_linger_len) < 0) {
    perror("getsockopt()");
    close(socket_);
    exit(0);
  }
  printf("l_onoff is %s with l_linger %d\n", (so_linger.l_onoff > 0 ? "true" : "false"), so_linger.l_linger);
  return 0;
}
