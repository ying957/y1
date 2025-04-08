#include "xyd_audio.h"

/*
    初始化  AI AO  ADEC AENC
         音频捕获(AI)->  音频编码 0 ->Muxer->MP4
                        音频编码 1 ->RTSP->推流
          网络数据送到 -> 音频解码  音频输出   
*/
extern rtsp_demo_handle g_rtsplive;
extern rtsp_session_handle g_rtsp_session;
MPP_CHN_S aenc0_src;
int count1 = 0;
FILE *out = NULL;
FILE *out_ao = NULL;
MEDIA_BUFFER mb1 = NULL;
void myaudio_bak(MEDIA_BUFFER mb)
{
	uint8_t senddata[1920*1080];
    uint8_t * data = RK_MPI_MB_GetPtr(mb); //真正的数据
    uint32_t size = RK_MPI_MB_GetSize(mb); //数据的长度
    
    HELMET_MSG sendaudio_msg;//发送信息的结构体
    sendaudio_msg.command = XYD_MSG_AUIDO;
    sendaudio_msg.data_length = size;
    sendaudio_msg.data_ptr = data;
    sendaudio_msg.sum = sum_value(sendaudio_msg);
    //发送命令和长度,第一次发送data_ptr是数据的内存地址
    sendcnt = mysock_send(sockfd,&sendaudio_msg,sizeof(sendaudio_msg));
    printf("sendaudio_msg.command==%d\r\n",sendaudio_msg.command);
    printf("sendaudio_msg.data_length==%d\r\n",sendaudio_msg.data_length);
    printf("sendaudio_msg.sum==%d\r\n",sendaudio_msg.sum);
    //发送真正的数据
    //发送真正的数据
    memset(senddata,0,1920*1080);
    memcpy(senddata,data,size);

    mysock_send(sockfd,senddata,size);
    printf("开发版发音频字节 == %d\r\n",sendaudio_msg.data_length);
    //释放mb
    RK_MPI_MB_ReleaseBuffer(mb);

	//rtsp推流
	// rtsp_tx_audio(g_rtsp_session,RK_MPI_MB_GetPtr(mb),RK_MPI_MB_GetSize(mb),RK_MPI_MB_GetTimestamp(mb));
	// rtsp_do_event(g_rtsplive);
	// RK_MPI_MB_ReleaseBuffer(mb);
	
}


void Init_xyd_Audio(void)
{
    
    out = fopen("test.g711a","w");
	//1.初始化rkmedir
	RK_MPI_SYS_Init();
	//2.设置ai通道的属性
	AI_CHN_ATTR_S ai_attr;
	ai_attr.pcAudioNode = "plughw:1,0 ";
	ai_attr.enSampleFormat = RK_SAMPLE_FMT_S16;
	ai_attr.u32Channels = 1;
	ai_attr.u32SampleRate = 8000;
	ai_attr.u32NbSamples = 1024;
	ai_attr.enAiLayout = AI_LAYOUT_NORMAL;
	RK_MPI_AI_SetChnAttr(0,&ai_attr);
	
	RK_MPI_AI_EnableChn(0);
	//创建aenc通道
	AENC_CHN_ATTR_S aenc_attr;
	aenc_attr.enCodecType = RK_CODEC_TYPE_G711A;
	aenc_attr.u32Bitrate = 32000;
	aenc_attr.u32Quality = 1;

	aenc_attr.stAencG711A.u32Channels = 1;
	aenc_attr.stAencG711A.u32SampleRate = 8000;
	aenc_attr.stAencG711A.u32NbSample = 1024;
	RK_MPI_AENC_CreateChn(0,&aenc_attr);
	RK_MPI_AENC_CreateChn(1,&aenc_attr);
	//注册aenc回调函数
	MPP_CHN_S aenc_chn;
	aenc_chn.enModId = RK_ID_AENC;
	aenc_chn.s32DevId = 0;
	aenc_chn.s32ChnId = 1;
	int ret = RK_MPI_SYS_RegisterOutCb(&aenc_chn,myaudio_bak);
	if (ret != 0) {
		printf("注册回调失败，错误码：%d\n", ret);
		exit(EXIT_FAILURE);
	}
	//绑定ai和aenc通道
	MPP_CHN_S src,dest;
	src.enModId = RK_ID_AI;
	src.s32DevId = 0;
	src.s32ChnId = 0;
	
	dest.enModId = RK_ID_AENC;
	dest.s32DevId = 0;
	dest.s32ChnId = 1;
	aenc0_src.enModId = RK_ID_AENC;
    aenc0_src.s32ChnId = 0;
    aenc0_src.s32DevId = 0;
	RK_MPI_SYS_Bind(&src,&aenc0_src);
	// {

	// } 
	RK_MPI_SYS_Bind(&src,&dest);
	int ret1 = RK_MPI_SYS_Bind(&src,&dest);

	if (ret1 != 0) {
		printf("绑定失败，错误码：%d\n", ret1);
	}


}
//解析语音
void adec_ao_func(void)
{
	out_ao = fopen("./test.g711a","r");
	//1.初始化rkmedir
	RK_MPI_SYS_Init();
	//创建解码器通道
	ADEC_CHN_ATTR_S adec_attr;
	adec_attr.enCodecType = RK_CODEC_TYPE_G711A;
	adec_attr.stAdecG711A.u32Channels = 1;
	adec_attr.stAdecG711A.u32SampleRate = 8000;
	
	RK_MPI_ADEC_CreateChn(0,&adec_attr);
	
	//创建ao通道plughw:1,0 
	AO_CHN_ATTR_S ao_attr;
	ao_attr.pcAudioNode = "default";
	ao_attr.enSampleFormat = RK_SAMPLE_FMT_S16;
	ao_attr.u32Channels = 1;
	ao_attr.u32SampleRate = 8000;
	ao_attr.u32NbSamples = 1024;

	RK_MPI_AO_SetChnAttr(0,&ao_attr);
	//使能ao通道
	RK_MPI_AO_EnableChn(0);
	//绑定adec和ao通道
	MPP_CHN_S src1,dest1;
	src1.enModId = RK_ID_ADEC;
	src1.s32DevId = 0;
	src1.s32ChnId = 0;
	
	dest1.enModId = RK_ID_AO;
	dest1.s32DevId = 0;
	dest1.s32ChnId = 0;
	RK_MPI_SYS_Bind(&src1,&dest1);

	while(1)
	{
		mb1 = RK_MPI_MB_CreateAudioBuffer(1*8000*1024/8,RK_FALSE);
		count1 = fread(RK_MPI_MB_GetPtr(mb1), 1,RK_MPI_MB_GetSize(mb1),out_ao);
		if(count1 == 0)
		{
			break;
		}


		RK_MPI_MB_SetSize(mb1,count1);
		RK_MPI_SYS_SendMediaBuffer(RK_ID_ADEC,0,mb1);
		RK_MPI_MB_ReleaseBuffer(mb1);
		fflush(NULL);
	}
}



/*
    总结：
        1：初始化了  AI 音频捕获 
            双声道  S16采样格式  16000采样率  1152采样次数

        2：初始化 AENC0 ->编码通道 0
            编码格式为 MP2  S16采样格式  16000采样率  速率 32K
        3：初始化 AENC1 ->编码通道 1
            编码格式为 MP2  S16采样格式  16000采样率  速率 32K

        4: 绑定：
            把 AI->AENC0 一份   AI->AENC1 一份 
            我们有两份编码后的数据！ Mp2 目前都是

        5：初始化 AO 
            播放格式：
                 双声道  S16采样格式  16000采样率  1152采样次数
        6：初始化 解码器 ADEC
            解码格式：
                解码 G711A  双声道  16000采样率
        7： ADEC数据给 AO输出 
*/