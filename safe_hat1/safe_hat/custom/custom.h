/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include <stdio.h> // 引入标准输入输出库，用于打印信息
#include "lvgl.h"  // 引入LVGL图形库
#include "custom.h" // 引入自定义头文件
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavcodec/avcodec.h>
#include <SDL2/SDL.h>
#include <bits/select.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavcodec/avcodec.h>

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
    uint8_t * data_ptr;//数据指针
    uint32_t data_length;//数据长度
    uint32_t sum;//和校验
}HELMET_MSG;
pthread_t video_pth_id;

void custom_init(lv_ui *ui);
void *dec_video(void *arg);
void connect_sever(void);
int mysock_recv(int sockfd,void * data,int size);
uint32_t sum_value(HELMET_MSG msg);
bool sum_test(HELMET_MSG msg);

void audio_decode_init(void);
void video_decode_init(void);

int sockfd;
extern AVCodecContext *audiocodecContext;
#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
