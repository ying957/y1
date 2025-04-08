#ifndef _XYD_RKMEDIA_H_
#define _XYD_RKMEDIA_H_


#include "stdio.h"
#include "stdint.h"
#include "rtsp_demo.h"
#include "sample_common.h"
#include "rkmedia_api.h"
#include "rkmedia_venc.h"


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>

void Init_RKMedia(void);
void Init_ISP(void);
int Check_SD_card(void);
int dele_mp4(void);
#endif // !1