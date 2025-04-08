#include "main.h"

void * pthread_client_connect(void * arg);

int s_fd = 0;
char s_buf[100] = {0};
char r_buf[1200] = {0};
int c_fd[10] = {0};
int count = 0;
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
int main()
{
    //处理连接线程ID
    pthread_t connect_pd;

    //创建连接套接字
    s_fd = socket(AF_INET,SOCK_STREAM,0);
    if(s_fd == -1)
    {
        perror("socket");
    }

    //绑定服务器的ip地址和端口号
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;//ipv4
    ser.sin_port = htons(55555);//服务器端口号
    ser.sin_addr.s_addr = inet_addr("192.168.100.25");//服务器ip地址
    int res = bind(s_fd,(const struct sockaddr *)&ser,sizeof(ser));
    if(res == -1)
    {
        perror("bind");
    }

    //监听
    res = listen(s_fd,10);
    if(res == -1)
    {
        perror("listen");
    }
    struct sockaddr_in cli;
    int size = sizeof(cli);

    //确定最大文件描述符
    int max = s_fd;

    //创建备份集合和监听集合
    fd_set bf;//备份
    fd_set jt;//监听

    //初始化（清空）备份集合
    FD_ZERO(&bf);

    //将socket的返回值（连接套接字的文件描述符加入备份集合）
    FD_SET(s_fd,&bf);

    //select循环监听异动并根据发生异动的文件不同做不同的操作
    while (1)
    {
        //将备份集合赋值给监听集合
        jt = bf;

        //调用select阻塞监听
        res = select(max+1,&jt,NULL,NULL,NULL);

        //判断是不是连接套接字发生异动
        if(FD_ISSET(s_fd,&jt))
        {
            /*能够进来说明连接套接字发生异动也就是说有客户端申请和服务器进行连接所以应该调用accept来接收客户端连接*/
            c_fd[count] = accept(s_fd,(struct sockaddr *)&cli,&size);
            printf("%d号客户端已上线\n",c_fd[count]);

            // 创建线程处理连接
            

            //更新备份集合(将新产生通信套接字的文件描述符放入备份集合)
            FD_SET(c_fd[count],&bf);

            //更新最大文件描述符
            if(max < c_fd[count])
                max = c_fd[count];

            //数组下标+1
            count++;

            //如果只有连接套接字发生异动，直接跳出本次循环
            if(res == 1)
                continue;
            
        }

        //定位哪(几)个通信套接字发生异动
        for(int i = 0;i<count;i++)//遍历所有的通信套接字的文件描述符
        {
            //判断是否在监听集合中
            if(FD_ISSET(c_fd[i],&jt))
            {

                
                /*能够进来说明c_fd[i]对应的通信套接字发生异动也就是说该通信套接字对应的客户端给服务器发消息了所以应该调用recv来接收客户的信息*/
                //接收信息
                HELMET_MSG readmsg;
                int n = mysock_recv(c_fd[i],&readmsg,sizeof(readmsg));
                
                //printf("command = %d\n",readmsg.command);
                //printf("readmsg.data_length == %d\n",readmsg.data_length);
                // printf("sizeof = %ld\n",sizeof(readmsg));
                // printf("收到%d\n",n);
                //下线处理
                if(n == 0)
                {
                    //将c_fd[i]从备份集合移除
                    FD_CLR(c_fd[i],&bf);

                    //将cfd[i],从数组中移除
                    for(int j=i;j<count-1;j++)
                    {
                        c_fd[j] = c_fd[j+1];
                    }
                    c_fd[count-1] = 0;
                    count--;
                }//消息转发
                else if(n == sizeof(readmsg))
                {
                    switch (readmsg.command)
                    {
                        case XYD_MSG_VIDEO:
                        {
                            printf("sendvideo_msg.command==%d\r\n",readmsg.command);
                            printf("sendvideo_msg.data_length==%d\r\n",readmsg.data_length);
                            printf("sendvideo_msg.sum==%d\r\n",readmsg.sum);\

                            if(readmsg.data_length > 500000)
                            {
                                printf("丢弃垃圾值\r\n");
                                break;
                            }
                            printf("视频接收完成!\r\n");
                            
                            memset(recv_buf,0,sizeof(recv_buf));
                            n =mysock_recv(c_fd[i],recv_buf,readmsg.data_length);
                            
                            if(sum_test(readmsg))
                            {
                                for(int k = 0;k<count;k++)
                                {
                                    //排除自己
                                    if(c_fd[k]!=c_fd[i])
                                    {
                                        readmsg.data_ptr = recv_buf;
                                        //memset(recv_buf,0,sizeof(recv_buf));
                                        mysock_send(c_fd[k],&readmsg,sizeof(HELMET_MSG));
                                        mysock_send(c_fd[k],readmsg.data_ptr,readmsg.data_length);
                                    }    
                                }
                            }
                            break;
                        }
                            
                        case XYD_MSG_AUIDO:
                            {
                                printf("sendaudio_msg.command==%d\r\n",readmsg.command);
                                printf("sendaudio_msg.data_length==%d\r\n",readmsg.data_length);
                                printf("sendaudio_msg.sum==%d\r\n",readmsg.sum);
                                memset(r_buf,0,sizeof(r_buf));
                                int ret = mysock_recv(c_fd[i],r_buf,1024);
                                printf("音频接收完成!\r\n");
                                if(sum_test(readmsg))
                                {
                                    for(int k = 0;k<count;k++)
                                    {
                                        //排除自己
                                        if(c_fd[k]!=c_fd[i])
                                        {
                                            readmsg.data_ptr = r_buf;
                                            // memset(recv_buf,0,sizeof(recv_buf));
                                            mysock_send(c_fd[k],&readmsg,sizeof(HELMET_MSG));
                                            mysock_send(c_fd[k],readmsg.data_ptr,readmsg.data_length);

                                        }    
                                    }
                                }
                                break;
                            }
                            
                            
                        default:
                            break;
                    }

                }
            }
        }

    }
    return 0;
}

void * pthread_client_connect(void * arg)
{
    int ret = 0;
    intptr_t ckd = (intptr_t)arg;
    HELMET_MSG readmsg;
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
    printf("ckd==%ld\r\n",ckd);
    ret = mysock_recv(ckd,&readmsg,sizeof(readmsg));
    printf("##############################################\r\n");
    if(ret != sizeof(readmsg)&&sum_test(readmsg))
    {
        printf("读取错误!\r\n");
        close(ckd);
        return NULL;
    }

}

