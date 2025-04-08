#include "main.h"
#include "xyd_rkmedia.h"
#include "xyd_rtsp.h"
#include "xyd_net.h"
void Check_Net(void);
void Init_Rtsp(void);
void tcp(void);
int main(int argc,char * argv[])
{

    argc=argc;
    argv=argv;
#if 0
//1:检查网络是否正常！ 网络正常之后才会正常工作 
/*
    检查 有线 
    检查 WIFI
*/ 
    Check_Net();

//2：初始化网络->创建线程 Socket 接收来自上位机的音频数据 解析 播放
    Init_Net(self_ip,55555);//系统->Linux下网络编程！
//3：初始化 ISP摄像头服务 服务器
    Init_ISP();
//4：初始化 音视频部分
    /*  
        AI AO AENC ADEC 
        VI VENC Muxer 
    */
    Init_RKMedia();//已经实现了！
//5：初始化 RTSP服务器
    Init_Rtsp();
#endif
    Check_Net();
    Check_SD_card();
    tcp ();
    Init_Rtsp();
    Init_xyd_Video();
    Init_xyd_Audio();
    Init_xyd_Muxer();

 
//   adec_ao_func();
  

 
    while(1)
    {
        
        dele_mp4();
        sleep(3);
    }


    return 0;    
}










