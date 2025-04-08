#include "main.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
    

#define PORT 55555
#define BACKLOG 50
int sockfd = 0;//套接字
void* thread_tcp(void *arg);
    
void tcp(void)
{
    pthread_t sd_pthread;
    int result = pthread_create(&sd_pthread, NULL, thread_tcp, NULL);//创建线程
    if (result!= 0)
    {
        perror("pthread_create error");
        return;
    }
}

void* thread_tcp(void *arg) //
{
    (void)arg;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addrlen = sizeof(client_addr);
    //char buffer[8196];

    // 1. 创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket creation failed");
        exit(0);
    }

        //向服务器发送连接申请绑定服务器的ip地址和端口号
        struct sockaddr_in ser;
        ser.sin_family = AF_INET;//ipv4
        ser.sin_port = htons(55555);//服务器端口号
        ser.sin_addr.s_addr = inet_addr("192.168.100.25");//服务器ip地址
        int ret = connect(sockfd,(const struct sockaddr *)&ser,sizeof(ser));//发送连接申请
        if(ret < 0)
        {
            perror("connect");
            printf("服务器不在线！\r\n");
            close(sockfd);
            exit(0);
        }
        printf("发送校验数据成功！\r\n");
        printf("服务器连接成功!\r\n");
}

int mysock_recv(int fd,void * data,int size)//接收函数
{
    int len = size;
    int ret = 0;
    uint8_t * p = data;
    while(1)
    {
        ret = recv(fd,p,len,0);
        if(ret < 0)
        {
            perror("read");
            printf("接受数据失败！\r\n");
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
                break;
            }
        }

    }
    return size;
}

int mysock_send(int fd,void * data,int size)//发送函数
{
    int len = size;
    int ret = 0;
    uint8_t * p = data;
    while(1)
    {
        ret = send(fd,p,len,0);
        if(ret < 0)
        {
            perror("write");
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
                break;
            }
        }

    }
    return size;
}






