/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

int button =0;
static void screen_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSED:
	{
		break;
	}
    default:
        break;
    }
}

static void screen_imgbtn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSED:
	{
        if(button==0)
        {
            button=1;
            if(video_pth_id == 0)//播放
            {
                pthread_create(&video_pth_id, NULL, dec_video, NULL); // 创建新线程，开始解码视频
            }
            else{
                printf("已经有视频在播放\n");
            }
        }else if(button==1)//暂停
        {
            if(video_pth_id == 0)
            {
                printf("没有视频播放!!\n");
            }
            else{
                pthread_cancel(video_pth_id);
                video_pth_id = 0;
            }	

        }
        
		break;
	}
    default:
        break;
    }
}

static void screen_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSED:
	{
		break;
	}
    default:
        break;
    }
}

static void screen_imgbtn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSED:
	{
		break;
	}
    default:
        break;
    }
}

void events_init_screen (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_imgbtn_1, screen_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_imgbtn_2, screen_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_btn_1, screen_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_imgbtn_3, screen_imgbtn_3_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
