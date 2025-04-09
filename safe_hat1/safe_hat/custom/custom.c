/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

uint8_t recv_buf[1920*1080*2];
char r_buf[1200] = {0};


char rec_buf[4096];  // 缓存，用于存储从网络读取的数据
uint8_t img_buf[800*480*4]; // 图像缓冲区，用于存储解码后的图像数据
lv_img_dsc_t dec_img = { // 定义图像描述结构体
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA, // 图像格式为带透明度的真彩色
  .header.always_zero = 0, // 保持为零
  .header.reserved = 0, // 保留字段
  .header.w = 800, // 图像宽度
  .header.h = 480, // 图像高度
  .data_size = 384000 * LV_IMG_PX_SIZE_ALPHA_BYTE, // 图像数据的大小（800*480*4）
  .data = img_buf, // 图像数据缓冲区
};

extern AVCodecContext *videocodecContext;
extern AVPacket *video_packet; 
extern AVFrame *video_frame;
extern AVFrame *video_rgb_frame;
struct SwsContext *swsContext;

extern AVCodecContext *audiocodecContext;
extern AVPacket audiopacket;
extern AVFrame *audioframe;
extern SDL_AudioDeviceID audioDevice;
void *dec_video(void *arg)
{
    int ret;
    int videoIndex = -1;
    

    HELMET_MSG readmsg;//接收命令与长度结构体
    while(1)
    {
        // if(stop = 1)
        // {
        //     pthread_exit(NULL);
        // }
        //命令&长度
        int n = mysock_recv(sockfd,&readmsg,sizeof(readmsg));

        switch (readmsg.command)
        {
            case XYD_MSG_VIDEO:
            {
                
                memset(recv_buf,0,sizeof(recv_buf));
                int ret =mysock_recv(sockfd,recv_buf,readmsg.data_length);
                printf("视频接收完成!\r\n");
            
                av_init_packet(video_packet);
                video_packet->size = readmsg.data_length;
                video_packet->data = recv_buf;
                printf("pkt->size == %d\r\n",video_packet->size);
               
                ret = avcodec_send_packet(videocodecContext,video_packet);
                
                ret = avcodec_receive_frame(videocodecContext, video_frame);
                if(-EAGAIN == ret)
                {
                    break;
                }
                printf("视频解码成功！\r\n");

                
                // av_image_fill_arrays(rgb_frame->data, rgb_frame->linesize, img_buf, AV_PIX_FMT_BGRA, 800, 480, 1);
                ret = sws_scale(swsContext,(const uint8_t *const *)video_frame->data,video_frame->linesize,0,video_frame->height,
                video_rgb_frame->data,video_rgb_frame->linesize);
                printf("ret == %d\r\n",ret);
                printf("rgb_frame->linesize[0]: %d\n", video_rgb_frame->linesize[0]); 
                printf("RGB Data Size: %d\n", video_rgb_frame->linesize[0] * video_rgb_frame->height);
                lv_img_set_src(guider_ui.screen_img_1,&dec_img);
                printf("222222222222222222222222222222222222222222222\r\n");
                av_frame_unref(video_frame);
                // printf("3333333333333333333333333333333333333333\r\n");
                memset(recv_buf,0,sizeof(recv_buf));
                break;
            }
            case XYD_MSG_AUIDO:
            {
                printf("sendaudio_msg[96]==%d\r\n",r_buf[96]);
                printf("sizeof(readmsg) == %ld\r\n",sizeof(readmsg));
                printf("sendaudio_msg.command==%d\r\n",readmsg.command);
                printf("sendaudio_msg.data_length==%d\r\n",readmsg.data_length);
                printf("sendaudio_msg.sum==%d\r\n",readmsg.sum);
                memset(r_buf,0,sizeof(r_buf));
                ret = mysock_recv(sockfd,r_buf,readmsg.data_length);
                printf("音频接收完成!\r\n");
                av_init_packet(&audiopacket);
                audiopacket.size = ret;
                audiopacket.data = r_buf;

                // 发送音频包到解码器
                ret = avcodec_send_packet(audiocodecContext, &audiopacket);
                if (ret < 0)
                {
                    printf("发送音频包到解码器失败，%d\n",ret);
                    continue;
                }

                // 接收解码帧
                ret = avcodec_receive_frame(audiocodecContext, audioframe);
                if (ret < 0)
                {
                    printf("接收音频帧失败，错误码\n");
                    continue;
                }
                printf("音频解码帧的格式: %d\n", audioframe->format);
                printf("音频解码帧的通道数: %d\n", audioframe->channels);
                printf("音频解码帧的样本数: %d\n", audioframe->nb_samples);
                // 将解码后的音频数据加入 SDL 音频队列
                int data_size = audioframe->nb_samples * 2;  // 16-bit PCM 每个样本 2 字节
                ret = SDL_QueueAudio(audioDevice, audioframe->data[0], data_size);
                if (ret < 0)
                {
                    printf("将音频数据加入队列失败\n");
                }
                printf("音频数据加入队列成功\r\n");
                break;
            }
           
        }
    }

    return NULL;
}


void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    /**********连接服务器**********/
    connect_sever();

    /*******初始化音频解码器**********/
    audio_decode_init();

    /*******初始化视频解码器**********/
    video_decode_init();


}

