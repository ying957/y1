#ifndef _XYD_AUDIO_H_
#define _XYD_AUDIO_H_


#include "stdio.h"
#include "stdint.h"
#include "rtsp_demo.h"
#include "sample_common.h"
#include "rkmedia_api.h"
#include "rkmedia_venc.h"
#include "xyd_muxer.h"
void Init_xyd_Audio(void);
void adec_ao_func(void);
void myaudio_bak(MEDIA_BUFFER mb);
#endif // !1