#include "xyd_muxer.h"

extern MPP_CHN_S aenc0_src;
extern MPP_CHN_S venc0_src;
void Init_xyd_Muxer(void)
{
    MUXER_CHN_ATTR_S muter_attr;
    //1.1：Muxer本地保存文件的分割方式和命名方式
    muter_attr.enMode = MUXER_MODE_AUTOSPLIT;//自动分割！
    muter_attr.enType = MUXER_TYPE_FLV;//文件保存为Mp4格式
    //muter_attr.pcOutputFile;//用单一模式 输出路径
    //1.2：自动分割属性->分割方法： 大小 时间
    muter_attr.stSplitAttr.enSplitNameType=MUXER_SPLIT_NAME_TYPE_AUTO;
    muter_attr.stSplitAttr.enSplitType = MUXER_SPLIT_TYPE_TIME;
    muter_attr.stSplitAttr.stNameAutoAttr.bTimeStampEnable = RK_TRUE;
    muter_attr.stSplitAttr.stNameAutoAttr.pcBaseDir = "/mnt/sdcard";
    muter_attr.stSplitAttr.stNameAutoAttr.pcPrefix = "yx";//命名标识
    muter_attr.stSplitAttr.stNameAutoAttr.u16StartIdx = 0;//不加索引号
    muter_attr.stSplitAttr.u32TimeLenSec = 60;//60S自动分割视频

    //1.4：合成流的视频属性 从
    muter_attr.stVideoStreamParam.enCodecType = RK_CODEC_TYPE_H264;
    muter_attr.stVideoStreamParam.enImageType = IMAGE_TYPE_NV12;//
    muter_attr.stVideoStreamParam.u16Fps = 30;//30 帧每秒
    muter_attr.stVideoStreamParam.u16Level = 41;//等级.....
    muter_attr.stVideoStreamParam.u16Profile = 77;//高质量等级
    muter_attr.stVideoStreamParam.u32BitRate = 1920*1080;//码流速
    muter_attr.stVideoStreamParam.u32Height = 1080;
    muter_attr.stVideoStreamParam.u32Width = 1920;//分辨率

    //音频
    muter_attr.stAudioStreamParam.enCodecType = RK_CODEC_TYPE_G711A;
    muter_attr.stAudioStreamParam.enSampFmt = RK_SAMPLE_FMT_S16;
    muter_attr.stAudioStreamParam.u32Channels = 1;
    muter_attr.stAudioStreamParam.u32NbSamples = 1024;
    muter_attr.stAudioStreamParam.u32SampleRate = 8000;
    muter_attr.u32MuxerId = 0;
    RK_MPI_MUXER_EnableChn(0,&muter_attr);

    // MPP_CHN_S venc0_src,aenc0_src;
    MUXER_CHN_S muxer_audio,muxer_video;

    // venc0_src.enModId = RK_ID_VENC;
    // venc0_src.s32ChnId = 0;
    // venc0_src.s32DevId = 0;

    // aenc0_src.enModId = RK_ID_AENC;
    // aenc0_src.s32ChnId = 0;
    // aenc0_src.s32DevId = 0;

    muxer_video.enChnType = MUXER_CHN_TYPE_VIDEO;
    muxer_video.enModId = RK_ID_MUXER;
    muxer_video.s32ChnId = 0;

    muxer_audio.enChnType = MUXER_CHN_TYPE_AUDIO;
    muxer_audio.enModId = RK_ID_MUXER;
    muxer_audio.s32ChnId = 0;
    RK_MPI_MUXER_Bind(&venc0_src,&muxer_video);//VENC0->Muxer                                                                     
    RK_MPI_MUXER_Bind(&aenc0_src,&muxer_audio);//AENC0->Muxer

    RK_MPI_MUXER_StreamStart(0);
}