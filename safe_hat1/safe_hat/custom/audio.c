
#include "custom.h"

AVCodecContext *audiocodecContext = NULL;
AVPacket audiopacket;
AVFrame *audioframe = NULL;

SDL_AudioDeviceID audioDevice;

SDL_AudioSpec audioSpec;

void audio_decode_init(void)
{
    // 查找音频解码器 (G.711 A codec)
    AVCodec *audioCodec = avcodec_find_decoder(AV_CODEC_ID_PCM_ALAW);  // 使用 G.711 A-law 解码器
    if (!audioCodec)
    {
    	printf("音频解码器未找到\n");
        exit(-1);
    }

    // 创建解码上下文
    audiocodecContext = avcodec_alloc_context3(audioCodec);
    if (!audiocodecContext) {
    	printf("无法分配解码上下文\n");
        exit(-1);
    }

    // 配置解码器上下文
    audiocodecContext->channels = 1;
    audiocodecContext->sample_rate = 8000;  // G.711 A 的标准采样率
    audiocodecContext->sample_fmt = AV_SAMPLE_FMT_S16;  // 解码后的 PCM 格式
    audiocodecContext->channel_layout = AV_CH_LAYOUT_MONO; // 单声道

    // 打开解码器
    int ret = avcodec_open2(audiocodecContext, audioCodec, NULL);
    if (ret < 0)
    {
        char errbuf[AV_ERROR_MAX_STRING_SIZE];
        av_strerror(ret, errbuf, sizeof(errbuf));
        printf("无法打开音频解码器，错误码\r\n");
        exit(-1);
    }
    printf("音频解码器打开成功\r\n");//////////////////////////////////////////////

    // 初始化 SDL 音频
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
    	printf("SDL 初始化失败：\n");
        avcodec_free_context(&audiocodecContext);
        close(sockfd);
        return ;
    }

    
    audioSpec.freq = audiocodecContext->sample_rate;
    audioSpec.format = AUDIO_S16SYS;  // 16-bit PCM
    audioSpec.channels = audiocodecContext->channels;
    audioSpec.samples = 1024;  // 音频缓冲区的大小
    audioSpec.callback = NULL;  // 我们通过队列播放音频
    audioSpec.userdata = (void *)audiocodecContext;

    // 打开音频设备
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &audioSpec, NULL, 0);
    if (audioDevice == 0)
    {
    	printf("无法打开音频设备\r\n");
        SDL_Quit();
        avcodec_free_context(&audiocodecContext);
        close(sockfd);
        return ;
    }
    printf("音频设备打开成功\r\n");

    SDL_PauseAudioDevice(audioDevice, 0);  // 启动音频播

    // audiopacket = av_packet_alloc();
    audioframe = av_frame_alloc();
}