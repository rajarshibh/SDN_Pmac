/*
 *  * GloMoSim is COPYRIGHTED software.  Release 2.02 of GloMoSim is available
 *  * at no cost to educational users only.
 *  *
 *  * Commercial use of this software requires a separate license.  No cost,
 *  * evaluation licenses are available for such purposes; please contact
 *  * info@scalable-networks.com
 *  *
 *  * By obtaining copies of this and any other files that comprise GloMoSim2.02,
 *  * you, the Licensee, agree to abide by the following conditions and
 *  * understandings with respect to the copyrighted software:
 *  *
 *  * 1.Permission to use, copy, and modify this software and its documentation
 *  *   for education and non-commercial research purposes only is hereby granted
 *  *   to Licensee, provided that the copyright notice, the original author's
 *  *   names and unit identification, and this permission notice appear on all
 *  *   such copies, and that no charge be made for such copies. Any entity
 *  *   desiring permission to use this software for any commercial or
 *  *   non-educational research purposes should contact:
 *  *
 *  *   Professor Rajive Bagrodia
 *  *   University of California, Los Angeles
 *  *   Department of Computer Science
 *  *   Box 951596
 *  *   3532 Boelter Hall
 *  *   Los Angeles, CA 90095-1596
 *  *   rajive@cs.ucla.edu
 *  *
 *  * 2.NO REPRESENTATIONS ARE MADE ABOUT THE SUITABILITY OF THE SOFTWARE FOR ANY
 *  *   PURPOSE. IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 *  *
 *  * 3.Neither the software developers, the Parallel Computing Lab, UCLA, or any
 *  *   affiliate of the UC system shall be liable for any damages suffered by
 *  *   Licensee from the use of this software.
 *  */

// Use the latest version of Parsec if this line causes a compiler error.

#ifndef _SDN_MESSAGE_H_
#define _SDN_MESSAGE_H_
#include <stdint.h>
#include "main.h" 


#define LOG_FILE "/home/prith664/glomosim_log"
#define MAX_RETRIES 10

/*void LOG_WRITE_STRING(char *log)
{
    FILE *fd;
    fd = fopen(LOG_FILE, "a");
    fprintf(fd, "%s\n", log);
    fclose(fd);
}

void LOG_WRITE_INT(int log)
{
    FILE *fd;
    fd = fopen(LOG_FILE, "a");
    fprintf(fd, "%d\n", log);
    fclose(fd);
}*/


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

int msg_process_msg(GLOMOSIM_SS_MESSAGE *buf, const int len);

void msg_create_socket();

int msg_recv(void);

void msg_init(GlomoNode *node, GlomoNodeInput  *input);

void msg_close(void);

#endif

