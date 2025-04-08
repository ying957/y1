#ifndef __XYD_NET__H_
#define __XYD_NET__H_
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  
#include "sys/types.h"
#include "unistd.h"
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "stdint.h"

#include "sample_common.h"
#include "rkmedia_api.h"
#include "rkmedia_venc.h"



#include <sys/ioctl.h>
#include <net/if.h>
#include <errno.h>

extern char * self_ip;
void Check_Net(void);
void Init_Net(char * bind_ip,uint16_t bind_port);
#endif


