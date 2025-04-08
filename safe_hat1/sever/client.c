#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

pthread_t id = 0;
int fd = 0;
char s_buf[50] = {0};
char r_buf[100] = {0};

void *fun_recv(void *p);

int main()
{
    //创建连接套接字
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("socket");
    }
    //向服务器发送连接申请
    //绑定服务器的ip地址和端口号
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;//ipv4
    ser.sin_port = htons(55555);//服务器端口号
    ser.sin_addr.s_addr = inet_addr("192.168.100.25");//服务器ip地址
    int res = connect(fd,(const struct sockaddr *)&ser,sizeof(ser));
    if(res == -1)
    {
        perror("connect");
    }
    printf("成功建立连接\n");
    //创建副线程
    pthread_create(&id,NULL,fun_recv,NULL);
    //开始通信
    while (1)
    {
        //发送
        printf("请输入要向服务器发送的内容\n");
        scanf("%s",s_buf);
        send(fd,s_buf,50,0);
        if(strcmp(s_buf,"quit") == 0)
            exit(0);
    }
    
    return 0;
}

void *fun_recv(void *p)
{
    while(1)
    {
        //接收
        recv(fd,r_buf,100,0);
        if(strcmp(r_buf,"quit") == 0)
            exit(0);
        printf("从客户端收到：%s\n",r_buf);
    }
}
