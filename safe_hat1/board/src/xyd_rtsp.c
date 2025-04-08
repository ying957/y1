#include "xyd_rtsp.h"
void myvenc1_data_backfunction(MEDIA_BUFFER mb);
void myaenc1_data_backfunction(MEDIA_BUFFER mb);

/*
    视频 音频 网上/服务器推流
        Mp4/flv/h264数据包 发送给服务器->推流！
    推流方法很多：
        * 直接裸推-> H264编码包 ->发送服务器
          上位机->服务器->获取H264编码包->解码->播放    拉流
        * RTSP：
            RTSP是一个 TCP的推流协议 
            前面加点数据 H264 + AAC 后面数据-> RTSP的包
            包->RTSP库/协议/方法 推流 RTSP的专用服务器 
            各种平台/软件/库都可以快速拉流->观看直播
            理论来说 
                RTSP的延时更低        

        * RTMP
            RTMP是一个 UDP的推流协议 

    瑞芯微：
        写了一个 封装好不开源库——>librtsp.a
        1: 创建 RTSP的 服务器-> 类似 socket创建了服务器
                服务器在 开发版系统里面 
                外部就可以连接！
        2: 初始化 音频 和视频相关参数 


        3：推流 音频 视频->片段暂存于你自己创建RTSP服务器
            上位机就可以通过  拉流网址直接获取 推流数据了！



*/

rtsp_demo_handle g_rtsplive = NULL;
rtsp_session_handle g_rtsp_session;

void Init_Rtsp(void)
{

    	// init rtsp	初始化rtsp
	g_rtsplive = create_rtsp_demo(554);
	g_rtsp_session = rtsp_new_session(g_rtsplive, "/live0");
	rtsp_set_video(g_rtsp_session, RTSP_CODEC_ID_VIDEO_H264, NULL, 0);
    rtsp_set_audio(g_rtsp_session,RTSP_CODEC_ID_AUDIO_G711A,NULL,0);
	rtsp_sync_video_ts(g_rtsp_session, rtsp_get_reltime(), rtsp_get_ntptime());
    rtsp_sync_audio_ts(g_rtsp_session,rtsp_get_reltime(),rtsp_get_ntptime());

//音频RTSP的初始化 
/*
    AENC->不支持编码  Mp3 
		  支持 Mp2  G711A G711U G726
	官方 RTSP:
		G711A G711U G726 MP3
		*live555 FFMPEG LibRTMp 人家不挑格式！
		
		想要官方的Rtsp的库推流只能用 
			G711A / G711U / G726
        你现在图方便->不追求质量 而追求效率 和 有声音
        按照实际情况考虑 摄像头音频质量差可以接受！
        可以使用官方库直接编码 音频！
        用 FFMPEG ->编码音频-> AAC 
*/

/*
    G711A特点：
        采样率  8KHZ
        传输带宽  64kbps== 8k/s 
        单声道
*/
    //AENC1->G711A
    
//VENC1的数据回调
    /*
        VENC0->Muxer
        VENC1->backfunction->回调函数
    */
   
   
   // 给 VENC 1通道搞了一个输出回调 -> myvenc1_data_backfunction

// AENC1 数据回调
/*
    AENC0 -> Muxer 
    AENC1 -> outCb-> Rtsp 
        AENC-> Mp2 
        RTsp要的数据 G711A
*/

   

}


void myaenc1_data_backfunction(MEDIA_BUFFER mb)
{
   mb = mb;

}
void myvenc1_data_backfunction(MEDIA_BUFFER mb)
{
    
    mb = mb;
}