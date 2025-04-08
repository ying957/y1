#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
int main ()
{
    FILE * fp;
    int flag = 0;
    int r_buf[1024]={0};
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("socket");
    }
       //向服务器发送连接申请
       //绑定服务器的ip地址和端口号
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;//ipv4
    ser.sin_port = htons(55555);//服务器端口号 要与服务器一致
    ser.sin_addr.s_addr = inet_addr("192.168.100.25");//服务器ip地址
    int res = connect(fd,(const struct sockaddr *)&ser,sizeof(ser));//连接等待
       if(res == -1)
       {
        perror("connect");
       }
    else{
      printf("客户端成功建立连接\n");
      fp = fopen ("file.mp4", "w");
      while(1)
    {
        //接收信息
        res = recv(fd,r_buf,sizeof(r_buf),0);
        res = fwrite(r_buf,1,res,fp);
        printf("写入到字节数：%d",res);
        flag++;
        
        memset(r_buf,0,sizeof(r_buf));
        if(flag==10000)
        {
            fclose(fp);
            return 0;
        }
        //printf("%s\r\n",r_buf);                                  
    }
    }
    
    return 0;
}
