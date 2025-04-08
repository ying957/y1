#include "xyd_net.h"
#include "pthread.h"
char * self_ip = NULL;
char * Get_Ip( char * buf);
char * Get_ServerIp(char * ip);

void * Dell_Client_Accept_Pthreadfunction(void * arg);
void * Dell_Client_Audio_Data_Pthreadfunction(void * arg);
void Check_Net(void)
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) 
    {
        perror("socket");
       
    }
    struct ifreq ifr;//定义一个结构体
//检测有线网络
    strcpy(ifr.ifr_name,"eth0");
    //检查接口是否存在且已启用
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) == -1) 
    {
        if (errno == ENODEV) 
        {
            fprintf(stderr, "网络端口不存在\n");
        } 
        else 
        {
            perror("ioctl SIOCGIFFLAGS");
        }
        close(sock);
        
    }

    if (!(ifr.ifr_flags & IFF_UP)) 
    {
        printf("IFF_UP未开启\n");
        close(sock);
       
    }

    FILE *fp1;
    char ret[1024]={0};
    char *need="time";
    fp1 = popen("ping 192.168.111.222","r");
    fread(ret,1,1024,fp1);
    pclose(fp1); // 关闭管道 
    char *result = strstr(ret, need);
    if (result != NULL) 
    {
        printf("有线网络有网\n");
    } else {
        printf("有线网络没有网\n");
    }
    //检测wifi网络
    
    strcpy(ifr.ifr_name,"wlan0");
    char ip_str[20];
    if (ioctl(sock, SIOCGIFADDR, &ifr) == 0) 
    {
        struct sockaddr_in *addr = (struct sockaddr_in *)&ifr.ifr_addr;//因为ifr_addr是sockaddr类型要打印出来需要转换成sockaddr_in类型
        // printf("IP Address: %s\n", inet_ntoa(addr->sin_addr));
        inet_ntop(AF_INET, &addr->sin_addr,  ip_str, sizeof(ip_str));
        printf("wifi的动态ip为：%s\n",ip_str);
        
    } 
    else 
    {
        perror("ioctl failed");
    }
     close(sock);
    //  char cbuf[20]={0};
    //  int len = strlen(ip_str);
    //  for(int b=0;b < len-2;b++)
    //  {
    //     sprintf(&cbuf[b],"%c",ip_str[b]);
    //  }
    //  printf("路由器地址为：%s\n",cbuf);
    //fp1 = popen("ping %s",cbuf);
    fp1 = popen("ping 192.168.111.111","r");
    fread(ret,1,1024,fp1);
    pclose(fp1); // 关闭管道 
    char *result1 = strstr(ret, need);
    if (result1 != NULL) 
    {
        printf("wifi有网\n");
        
    } else {
        printf("wifi没有网\n");
    }
    


    /*
        检查 WIFI 和 有线哪个有网络！
        优先检查 有线！ 默认用 有线！
   
        检查网络的最基本原理->他的有线有没有IP！
    路由器链接 WIFI形式强行桥接公司网络
	公司IP地址 192.168.110.xx 
	
	我开发板通过网线链接路由器->链接到公司网络
	udhcpc  eth0  找链接网关(猫/路由器) 动态要一个IP 
		给我一个IP 192.168.110.118
		这个动态IP 正常可以上网的IP 
		
		一定能够ping通 网络终端(猫/路由器)
			192.168.110.1
        +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            ping www.baidu.com
        ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        所以我们该如何判定 网络正常？
            ping www.baidu.com -> 不行！
                不是所有公司的部署的网络都可以链接外网！
                    
            ping 192.168.110.1
        ++++++++++++++++++++++++++++++++++++++++++++++++++++++
            IP: 192.168.88.66
                192.168.88.1
        ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        如何以程序形式来做这个事情呢？
            popen();
    */
  
   
}


char * Get_Ip(char * buf)
{
    buf = buf;
    // int sock = socket(AF_INET, SOCK_DGRAM, 0);
    // if (sock < 0) 
    // {
    //     perror("socket");
    //     return -1;
    // }
    // struct ifreq ifr;//定义一个结构体

    // ifr.ifr_name = "eth0";
    // //检查接口是否存在且已启用
    // if (ioctl(sock, SIOCGIFFLAGS, &ifr) == -1) 
    // {
    //     if (errno == ENODEV) 
    //     {
    //         fprintf(stderr, "网络端口不存在\n");
    //     } 
    //     else 
    //     {
    //         perror("ioctl SIOCGIFFLAGS");
    //     }
    //     close(sock);
    //     return -1;
    // }
    // //检测IFF_UP是否开启
    // if (!(ifr.ifr_flags & IFF_UP)) 
    // {
    //     fprintf("IFF_UP未开启\n");
    //     close(sock);
    //    return -1;
    // }

    // //获取ip地址，ioctl会将获取到的ip地址放入ifr结构体内
    // if (ioctl(sock, SIOCGIFADDR, &ifr) == 0) 
    // {
    //     struct sockaddr_in *addr = (struct sockaddr_in *)&ifr.ifr_addr;//因为ifr_addr是sockaddr类型要打印出来需要转换成sockaddr_in类型
    //     printf("IP Address: %s\n", inet_ntoa(addr->sin_addr));
    // } 
    // else 
    // {
    //     perror("ioctl failed");
    // }
    // close(sock);

    return NULL;
}


char * Get_ServerIp(char * ip)
{
    ip = ip;
    return NULL;
}
/*
    创建服务器
        等待客户连接(上位机)->上位机一旦连接就代表上位机想喊话
        上位机连接后  他要发送数据给 监控节点
        得到数据就是上位机录制音频编码数据
        节点端需要解析+解码+播放

        断掉连接：
            就代表上位机关闭了 音频通话功能
            返回 accept();等待连接
*/
int skd = 0;

pthread_t pd;
void Init_Net(char * bind_ip,uint16_t bind_port)
{
    bind_ip = bind_ip;
    bind_port =bind_port;
}
/*
    处理来自客户音频数据
*/
pthread_t auido_del_pd;
void * Dell_Client_Accept_Pthreadfunction(void * arg)
{
    arg = arg;
    return NULL;
}
/*
    上位机定一个协议：
        编码后的音频数据和视频数据大小都是不固定！

*/
void * Dell_Client_Audio_Data_Pthreadfunction(void * arg)
{
    //客户-上位机离线了->只需要结束这个线程就行！
    arg = arg;
    return NULL;
}












