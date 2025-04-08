#ifndef _MAIN_H_
#define _MAIN_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdint.h>


enum XYD_HELMET_CMD{
	XYD_MSG_VIDEO,//视频数据
	XYD_MSG_AUIDO,//音频数据
	XYD_MSG_CLIENT,//客户端的ID合法校验
	XYD_MSG_TERMINAL,//终端ID合法校验
};
//安全帽传输协议信息
typedef struct helmet_message_str
{
    enum XYD_HELMET_CMD command;//命令
    uint8_t * data_ptr;//数据指针
    uint32_t data_length;//数据长度
    uint32_t sum;//和校验
}HELMET_MSG;

uint8_t recv_buf[1920*1080*2];

uint8_t au_recv_buf[1200];
uint32_t sum_value(HELMET_MSG msg);
bool sum_test(HELMET_MSG msg);

int mysock_send(int sockfd,void * data,int size);
int mysock_recv(int sockfd,void * data,int size);
#endif