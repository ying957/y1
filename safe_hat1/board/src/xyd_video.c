#include "xyd_video.h"
#include "main.h"
/*
    VI 
    VENC0
    VENC1   
*/
extern int sockfd;
MPP_CHN_S venc0_src;
extern rtsp_demo_handle g_rtsplive;
extern rtsp_session_handle g_rtsp_session;

FILE *out1 = NULL;

int cnt = 0;
void myvideo_bak(MEDIA_BUFFER mb)
{

    uint8_t senddata[480*400];
    uint8_t * data = RK_MPI_MB_GetPtr(mb); //真正的数据
    uint32_t size = RK_MPI_MB_GetSize(mb); //数据的长度
    
    HELMET_MSG sendvideo_msg;//发送信息的结构体
    sendvideo_msg.command = XYD_MSG_VIDEO;
    sendvideo_msg.data_length = size;
    sendvideo_msg.data_ptr = data;
    sendvideo_msg.sum = sum_value(sendvideo_msg);
    printf("sendvideo_msg.command==%d\r\n",sendvideo_msg.command);
    printf("sendvideo_msg.data_length==%d\r\n",sendvideo_msg.data_length);
    printf("sendvideo_msg.sum==%d\r\n",sendvideo_msg.sum);
   
    //发送命令和长度,第一次发送data_ptr是数据的内存地址
    cnt = mysock_send(sockfd,&sendvideo_msg,sizeof(sendvideo_msg));
    printf("sizeof%d\n",sizeof(sendvideo_msg));
    printf("发送视频频命令长度%d\n",cnt);

    //发送真正的数据
    memset(senddata,0,480 * 400);
    memcpy(senddata,RK_MPI_MB_GetPtr(mb),size);

    cnt = mysock_send(sockfd,senddata,size);
    printf("开发版发视频字节 == %d\r\n",size);
    printf("senddata[100]==%d\r\n",senddata[100]);
    printf("cnt==%d\r\n",cnt);
    //释放mb
    RK_MPI_MB_ReleaseBuffer(mb);

	//rtsp推流
	// rtsp_tx_video(g_rtsp_session, RK_MPI_MB_GetPtr(mb), RK_MPI_MB_GetSize(mb),RK_MPI_MB_GetTimestamp(mb));
	// rtsp_do_event(g_rtsplive);
	// RK_MPI_MB_ReleaseBuffer(mb);
	
}



void Init_xyd_Video(void)
{
    out1 = fopen("test.h264","w");
	//摄像头的3a处理，优化界面
	rk_aiq_working_mode_t hdr_mode = RK_AIQ_WORKING_MODE_NORMAL;
	SAMPLE_COMM_ISP_Init(0, hdr_mode, RK_FALSE, "/oem/etc/iqfiles");
	SAMPLE_COMM_ISP_Run(0);
	SAMPLE_COMM_ISP_SetFrameRate(0, 30);
	
	// init rtsp	初始化rtsp
	// g_rtsplive = create_rtsp_demo(554);
	// g_rtsp_session = rtsp_new_session(g_rtsplive, "/live0");
	// rtsp_set_video(g_rtsp_session, RTSP_CODEC_ID_VIDEO_H264, NULL, 0);
	// rtsp_sync_video_ts(g_rtsp_session, rtsp_get_reltime(), rtsp_get_ntptime());
	
	//初始化rkmida
	RK_MPI_SYS_Init();
	
	//设置vi通道的属性，vi通道用于采集
	VI_CHN_ATTR_S vi_attr;
	vi_attr.pcVideoNode = "rkispp_scale0";
	vi_attr.u32Width = 480;
	vi_attr.u32Height = 400;
	vi_attr.enPixFmt = IMAGE_TYPE_NV12;
	vi_attr.enBufType = VI_CHN_BUF_TYPE_MMAP;
	vi_attr.u32BufCnt = 5;
	vi_attr.enWorkMode = VI_WORK_MODE_NORMAL;
	RK_MPI_VI_SetChnAttr(0, 0, &vi_attr);
	RK_MPI_VI_EnableChn(0, 0);
	
	//创建venc通道
	VENC_CHN_ATTR_S venc_attr;
	venc_attr.stVencAttr.enType = RK_CODEC_TYPE_H264;
	venc_attr.stRcAttr.enRcMode = VENC_RC_MODE_H264CBR;
	venc_attr.stVencAttr.imageType = IMAGE_TYPE_NV12;
	venc_attr.stVencAttr.u32VirWidth = 480;
	venc_attr.stVencAttr.u32VirHeight = 400;
	venc_attr.stVencAttr.u32Profile = 77;
	venc_attr.stVencAttr.u32PicWidth = 480;
	venc_attr.stVencAttr.u32PicHeight = 400;
	venc_attr.stVencAttr.enRotation = 0;
	venc_attr.stRcAttr.stH264Cbr.u32Gop = 30;
	venc_attr.stRcAttr.stH264Cbr.u32SrcFrameRateNum = 30;
	venc_attr.stRcAttr.stH264Cbr.u32SrcFrameRateDen = 1;
	venc_attr.stRcAttr.stH264Cbr.fr32DstFrameRateNum = 30;
	venc_attr.stRcAttr.stH264Cbr.fr32DstFrameRateDen = 1;
	venc_attr.stRcAttr.stH264Cbr.u32BitRate = 480*400;
	
	RK_MPI_VENC_CreateChn(0, &venc_attr);
	RK_MPI_VENC_CreateChn(1, &venc_attr);
	//注册venc通道的回调函数
	MPP_CHN_S venc_chn;
	venc_chn.enModId = RK_ID_VENC;
	venc_chn.s32DevId = 0;
	venc_chn.s32ChnId = 1;

	RK_MPI_SYS_RegisterOutCb(&venc_chn, myvideo_bak);
	
	//绑定vi通道和venc通道
	MPP_CHN_S src,dest;
	src.enModId = RK_ID_VI;
	src.s32DevId = 0;
	src.s32ChnId = 0;
	dest.enModId = RK_ID_VENC;
	dest.s32DevId = 0;
	dest.s32ChnId = 1;
    venc0_src.enModId = RK_ID_VENC;
    venc0_src.s32ChnId = 0;
    venc0_src.s32DevId = 0;
	RK_MPI_SYS_Bind(&src, &venc0_src);
	RK_MPI_SYS_Bind(&src, &dest);
	// printf("请输入任意的字符结束视频采集\n");
	// getchar();
	
	// //解除vi和venc通道的绑定
	// RK_MPI_SYS_UnBind(&src, &venc0_src);
	// RK_MPI_SYS_UnBind(&src, &dest);
	
	// //销毁venc通道
	// RK_MPI_VENC_DestroyChn(0);
	// RK_MPI_VENC_DestroyChn(1);
	// //失能vi通道
	// RK_MPI_VI_DisableChn(0, 0);

}

/*
    总结：
        VI：
            采样  NV12   1080*1920分辨率

        VENC0 和VENC1
            编码 H264格式 CBR固定码率
             
        绑定 
            VI->VENC0 
            VI->VENC1 

*/