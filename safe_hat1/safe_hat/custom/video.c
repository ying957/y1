#include "custom.h"

AVCodecContext *videocodecContext = NULL;
AVPacket *video_packet = NULL; // 创建AVPacket用于存储压缩数据
AVFrame *video_frame = NULL; // 创建AVFrame用于存储解码后的帧
AVFrame *video_rgb_frame = NULL;
struct SwsContext *swsContext = NULL;

extern uint8_t img_buf[480*400*4]; // 图像缓冲区，用于存储解码后的图像数据800*480

void video_decode_init(void)
{
    /*1.初始化视频解码器 --- 打开解码器*/
     // 查找解码器
    AVCodec *avcodec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!avcodec) {
        fprintf(stderr, "Codec not found\n");
        return ;
    }
    // 创建视频编解码上下文
    videocodecContext = avcodec_alloc_context3(avcodec);
    // 填充上下文
    videocodecContext->profile = FF_PROFILE_H264_MAIN;//压缩等级
    videocodecContext->level  = 50;//标识level为 5.0 
    videocodecContext->height = 1080;
    videocodecContext->width = 1920;
    //GOP相关的
    videocodecContext->gop_size = 250;//组大小 
    videocodecContext->keyint_min = 30;//最小25帧插入一个 I 帧 
    //B帧 
    videocodecContext->max_b_frames = 1;//不超过3帧
    videocodecContext->has_b_frames = 1;
    //参考帧 
    videocodecContext->refs = 3;
    //设置输出YUV格式 
    videocodecContext->pix_fmt = AV_PIX_FMT_YUV420P;
    //设置码率
    videocodecContext->bit_rate = 1920*1080*2;//600kbps
    //设置帧率  
    videocodecContext->time_base = (AVRational){1,30};//帧与帧之间的间隔
    videocodecContext->framerate = (AVRational){30,1};//帧率每秒25帧
    
    // 打开解码器
    int ret = avcodec_open2(videocodecContext, avcodec, NULL);
    if(ret < 0)
    {
        printf("解码器打开失败！\r\n");
        return ;
    }
    /*
        循环取数据并进行解码
    */
    video_packet = av_packet_alloc(); // 创建AVPacket用于存储压缩数据
    video_frame = av_frame_alloc(); // 创建AVFrame用于存储解码后的帧
    video_rgb_frame = av_frame_alloc(); // 创建AVFrame用于存储转换后的BGR格式帧（用于显示）

    av_image_fill_arrays(video_rgb_frame->data, video_rgb_frame->linesize, img_buf, AV_PIX_FMT_BGRA, 480, 400, 1); // 设置BGRframe的数据数组
    swsContext = sws_getContext( // 创建SWS上下文用于像素格式转换
        videocodecContext->width, videocodecContext->height, videocodecContext->pix_fmt,
        480, 400, AV_PIX_FMT_BGRA,
        SWS_BICUBIC, NULL, NULL, NULL);
}