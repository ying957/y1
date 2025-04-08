#include "xyd_rkmedia.h"
#include "xyd_audio.h"
#include "xyd_video.h"
#include "xyd_muxer.h"
#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int num=0;
int Check_SD_card(void);
void Init_ISP(void)
{
}

void Init_RKMedia(void)
{
    RK_MPI_SYS_Init();
    //1:初始化 音频相关的  AI AENC AO ADEC 
    Init_xyd_Audio();
    //2:初始化 视频相关的  VI VENC 
    Init_xyd_Video();
    /*
        AENC0->MP2  ->Muxer
        AENC1->MP2  -> RTSP网络推流             
                                
        VENC0->H264 ->Muxer
        VENC1->H264 -> RTSP网络推流   
    */
    //3:初始化 Muxer相关
    if(Check_SD_card() == 0)
    {
        Init_xyd_Muxer();
    }
    
}



int Check_SD_card(void)
{
   
    if (access("/dev/mmcblk2p1", F_OK) == 0) //使用access函数对sd卡的设备文件进行查询当查询到设备文件时会返回0
    {
        printf("SD卡已插入\n");
    } else {
        
        if (errno == ENOENT) {
            printf("SD卡未入！\n");
            return -1;
        } 
    }

    char ret[1024] = {0};
	FILE *fp;
	fp = popen("df -h /mnt/sdcard","r");
	fread(ret,1,1024,fp);
    pclose(fp); // 关闭管道 
	
    
    char target = '%';
    int length = sizeof(ret);
    int j=0,a=0;
    for (int i = 0; i < length; ++i) {
        if (ret[i] == target) 
        {
            j=i+1;
            for(j = 0; j < length; ++j)
            {
                if (ret[j] == target)
                {
                    a=j;
                    
                }
            }

            
        }
    }
    printf("内存已使用：%c%c%% \n", ret[a-2],ret[a-1]);  
// char tim[3]={0};
// sprintf(&tim[0],"%c",ret[a-2]);
// sprintf(&tim[1],"%c",ret[a-1]);
// num = atoi(tim); 


   return 0;
}


int dele_mp4(void)
{
    
    char ret1[1024] = {0};
	FILE *fp1;
	fp1 = popen("df -h /mnt/sdcard","r");
	fread(ret1,1,1024,fp1);
    pclose(fp1); // 关闭管道 
   
    char target = '%';
    int length = sizeof(ret1);
    int j=0,a=0;
    for (int i = 0; i < length; ++i) {
        if (ret1[i] == target) 
        {
            j=i+1;
            for(j = 0; j < length; ++j)
            {
                if (ret1[j] == target)
                {
                    a=j;
                    
                }
            }

            
        }
    }
    //printf("内存已使用：%c%c%% \n", ret1[a-2],ret1[a-1]);  
    char tim1[3]={0};
    sprintf(&tim1[0],"%c",ret1[a-2]);
    sprintf(&tim1[1],"%c",ret1[a-1]);
    num = atoi(tim1); 

    //当查找删除 mp4文件
    char directory[] = "/mnt/sdcard"; 
     //int num1 = 98;
    if (num >= 90) 
    {
        struct dirent *entry;
        // time_t oldest_time = time(NULL);
        char oldest_file[256] = {0};
        long long int time_1=0 , time_old=0;
        DIR *dir = opendir(directory);
        char full_path[512] = {0};
        if (dir == NULL) 
        {
            perror("无法打开目录");
            return -1;
        }
        printf("11111111111111111111111111111122222222\n");
        while ((entry = readdir(dir)) != NULL) 
        {
            // 检查文件是否是 MP4 文件 
            if (strstr(entry->d_name, ".mp4") != NULL) 
            {

                printf("11111111111111111111111133333333333\n");
                // 提取文件名中的日期部分
                char *date_ptr = strstr(entry->d_name, "_");  // 查找第一个下划线 
                if (date_ptr != NULL) 
                {
                    printf("11111111111111111111114444444444\n");
                    date_ptr++;  // 跳过下划线 
                    char date_str[15];  // 日期部分长度为 14 位
                    strncpy(date_str, date_ptr, 14);
                    date_str[14] = '\0';  // 确保字符串结束 
                    time_1 = atoll(date_str);
                    // 比较时间，找到最老的文件 ,另一种思路给time_old赋一个较大的值使所有time_1都小于它
                    if(time_1 < time_old || time_old == 0) 
                    {
                        time_old = time_1;
                        strcpy(oldest_file, entry->d_name);//把对应的路径放入oldest_fil内
                    }
                }
            }
        }
 
        closedir(dir);
 
        if (oldest_file != NULL) 
        {
            sprintf(full_path, "/mnt/sdcard/%s", oldest_file);
            if (unlink(full_path) == 0) 
            {
                printf("%s\n", full_path);
                printf("已删除最老的文件\n");
            } 
            else 
            {
                perror("无法删除文件\n");
                return -1;
            }
        } 
        else 
        {
            printf("文件夹中没有符合条件的 MP4 文件\n");
        }
    }

    return 0;
}

