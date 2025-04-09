#include "custom.h"


/*********************连接服务器****************/
void connect_sever(void)
{
    // 设置套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 创建套接字
    if (sockfd < 0) 
    {
        perror("无法创建套接字");
        return ;
    }

    // 连接到服务器
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(55555); // 目标端口
    server_addr.sin_addr.s_addr = inet_addr("192.168.111.222"); // 目标服务器 IP 地址

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("连接失败");
        close(sockfd);
        return ;
    }
    printf("已连接到服务器\n");
}

/*********************自定义接收函数*****************/
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


/****************检验函数*********************/
uint32_t sum_value(HELMET_MSG msg)
{
    return msg.command + msg.data_length +(uintptr_t)msg.data_ptr;
}

/****************检验函数111111*******************/
bool sum_test(HELMET_MSG msg)
{
    if(msg.sum==msg.command + msg.data_length +(uintptr_t)msg.data_ptr)
    {
        return true;
    }
    return false;
}
/**************************************** */

