#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#define SOCKET_DEST "/home/rajarshi664/socket_local/sock_glomosim"
#define SOCKET_OPENFLOW "/home/rajarshi664/socket_remote/sock_openflow"
#define SOCKET_NAME SOCKET_OPENFLOW


static struct sockaddr_un dest_addr;

static int sock = 0;


typedef enum
{
  GLOMOSIM_SS_EVENT = 0,
  GLOMOSIM_SS_STATS_REQ,
  GLOMOSIM_SS_STATS_RES,
  GLOMOSIM_SS_CONFIG
}GLOMOSIM_SS_MESSAGE_TYPE;

typedef enum
{
    CSMA_PROTO = 0,
    WIFI_PROTO = 1
} GLOMOSIM_MAC_TYPES;

typedef enum
{
    GLOMOSIM_SWITCH_MAC = 0
}   GLOMOSIM_CONFIG_TYPE;


typedef struct GLOMOSIM_SS_MESSAGE_CONFIG
{
    GLOMOSIM_CONFIG_TYPE     config_type;
    union
    {
      struct
      {
        uint8_t              type;
      } switch_mac;
    } u;
} GLOMOSIM_SS_MESSAGE_CONFIG;

typedef struct GLOMOSIM_SS_MESSAGE {
    GLOMOSIM_SS_MESSAGE_TYPE type;
    union
    {
        GLOMOSIM_SS_MESSAGE_CONFIG config;
    } u;

} GLOMOSIM_SS_MESSAGE;


void sock_init()
{
  struct sockaddr_un sock_addr;
  
  printf("\nStarting\n");

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
    strcpy(dest_addr.sun_path, SOCKET_DEST);
    unlink(SOCKET_NAME);
    if (0 > bind(sock, (const struct sockaddr*)&sock_addr, sizeof(sock_addr)))
    {
      printf("bind error with error: %s", strerror(errno));
      return;
    }
    printf("sock binded\n");
  }

  printf("Sending Initialized.for socekt %d\n", sock);
}

void sock_close()
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

int main() {
    GLOMOSIM_SS_MESSAGE msg;
    int i = 1;
    msg.type = GLOMOSIM_SS_CONFIG;
    msg.u.config.config_type = GLOMOSIM_SWITCH_MAC;
    msg.u.config.u.switch_mac.type = WIFI_PROTO;
    sock_init();

    while(i==1) {
        if (0 > sendto(sock, &msg, sizeof(msg), 0, 
                (const struct sockaddr*)&dest_addr, sizeof(dest_addr)))
        {
           // printf("Send message to GLOMOSIM failure");
        }
        i++;
    }
    sock_close();
    
}
