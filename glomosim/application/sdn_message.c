#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "sdn_message.h"


#define SOCKET_GLOMOSIM "/home/rajarshi664/socket_local/sock_glomosim"
#define SOCKET_REMOTE "/home/rajarshi664/socket_remote/sock_openflow"
#define SOCKET_NAME SOCKET_GLOMOSIM

static struct sockaddr_un dest_addr;

static int sock = 0;

void msg_create_socket()
{
  struct sockaddr_un sock_addr;

  printf("\nmsg_create_socket()\n");


  if (sock == 0)
  {
    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (0 >= sock)
    {
      printf("socket open error: %s\n", strerror(errno));
      sock = 0;
      return;
    }
    printf("sock opened\n");

    bzero(&sock_addr, sizeof(sock_addr));
    bzero(&dest_addr, sizeof(dest_addr));
    sock_addr.sun_family = AF_UNIX;
    dest_addr.sun_family = AF_UNIX;
    strcpy(sock_addr.sun_path, SOCKET_NAME);
    strcpy(dest_addr.sun_path, SOCKET_REMOTE);
    unlink(SOCKET_NAME);
    if (0 > bind(sock, (const struct sockaddr*)&sock_addr, sizeof(sock_addr)))
    {
      printf("bind error with error:%s\n", strerror(errno));
      return;
    }
    printf("sock binded\n");
  }


  printf("OpenFlow Initialized.\n");
  printf("sock = %d\n", sock);
}

                                                             
void msg_close()
{
  printf("msg_close()\n");
  if (sock > 0)
  {
    close(sock);
    unlink(SOCKET_NAME);
    sock = 0;

    printf("Socket Closed.\n");
  }
}


int msg_recv()
{
  int len;
  int retval = FALSE;

  GLOMOSIM_SS_MESSAGE buf;

  if (sock == 0)
    return;

  while (0 < (len = recv(sock, &buf, sizeof(buf), MSG_DONTWAIT)))
  {
    msg_process_msg(&buf, len);
    retval = TRUE;
  }

  if (errno != EAGAIN)
  {
    printf("msg_recv - recv error with error = %s\n",strerror(errno));
  }
  return retval;
}


