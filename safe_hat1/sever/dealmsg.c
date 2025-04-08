#include "main.h"


int mysock_send(int sockfd,void * data,int size)
{
    int len = size;
    int ret = 0;
    uint8_t * p = data;
    while(1)
    {
        ret = send(sockfd,p,len,0);
        if(ret < 0)
        {
            perror("send");
            printf("发送数据失败！\r\n");
            return ret;
        }else if(ret == 0)
        {
            printf("客户离线!\r\n");
            close(sockfd);
            return 0;
        }else 
        {

            len = len - ret;
            p+=ret;
            if(len == 0)
            {
                //printf("数据发送完毕！\r\n");
                break;
            }
        }

    }
    return size;
}

int mysock_recv(int sockfd,void * data,int size)
{
    int len = size;
    int ret = 0;
    uint8_t * p = data;
    while(1)
    {
        ret = recv(sockfd,p,len,0);
        if(ret < 0)
        {
            perror("send");
            printf("接受数据失败！\r\n");
            return ret;
        }else if(ret == 0)
        {
            //printf("客户离线!\r\n");
            close(sockfd);
            return 0;
        }else 
        {
            //printf("len==%d\r\n",len);
            len = len - ret;
            p+=ret;
            if(len == 0)
            {
                break;
            }
        }

    }
    return size;
}

uint32_t sum_value(HELMET_MSG msg)
{
    return msg.command + msg.data_length + (uintptr_t)msg.data_ptr;
}

bool sum_test(HELMET_MSG msg)
{
    if(msg.sum==msg.command + msg.data_length + (uintptr_t)msg.data_ptr)
    {
        return true;
    }
    return false;
}