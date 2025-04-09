#ifndef __MAIN_H_

#define __MAIN_H_

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
#include "rtsp_demo.h"
#include "sample_common.h"
#include "rkmedia_api.h"
#include "rkmedia_venc.h"
#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include "xyd_audio.h"
#include "xyd_rkmedia.h"
#include "xyd_net.h"
#include "xyd_video.h"
#include "xyd_muxer.h"
#include "xyd_rtsp.h"

int mysock_recv(int fd,void * data,int size);
int mysock_send(int fd,void * data,int size);
void xyd_sever(void);
// bool sum_test(HELMET_MSG msg);
// uint32_t sum_value(HELMET_MSG msg);

enum XYD_HELMET_CMD
{
	XYD_MSG_VIDEO,//视频数据
	XYD_MSG_AUIDO,//音频数据
	XYD_MSG_CLIENT,//客户端的ID合法校验
	XYD_MSG_TERMINAL,//终端ID合法校验

};
//安全帽传输协议信息
typedef struct helmet_message_str
{
    enum XYD_HELMET_CMD command;//命令
    uint32_t tmp;
    uint8_t * data_ptr;//数据指针
    uint32_t tmp1;
    uint32_t data_length;//数据长度
    uint32_t sum;//和校验
}HELMET_MSG;
uint32_t sum_value(HELMET_MSG msg);
bool sum_test(HELMET_MSG msg);
#endif


