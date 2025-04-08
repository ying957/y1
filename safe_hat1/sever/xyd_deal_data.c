#include "main.h"
void * sync_read_pthread(void * arg)
{
    arg = arg;
    return NULL;
}
void sync_client(int ckd)
{
    ser_info.sync_flag = true;
    ser_info.sync_ckd = ckd;
    pthread_t pd  = 0;
    pthread_create(&pd,NULL,sync_read_pthread,(void *)ckd);
}
void deal_terminal_online_client(HELMET_MSG * msg,int ckd)
{
    msg = msg;
    ckd = ckd;
    struct helmet_client_info * tmp = head;
    HELMET_MSG readmsg={
        .xyd="xyd",
       
    };
    //int flag = verify_terminal_deviceid(msg->device_id); 
    //if(flag == 0)
    if(msg->device_id == 0xFFFFFFFF && ser_info.helmet_terminal_ckd == 0)
    {
        printf("监视终端上线！\r\n");
        ser_info.helmet_terminal_ckd = ckd;
        FD_SET(ckd,&ser_info.lock_list);
        if(ckd > ser_info.max)
            ser_info.max = ckd; 
        printf("ser_info.count==%d\r\n",ser_info.count);
        for(int i =0;i<ser_info.count;i++)
        {
            readmsg.command = XYD_MSG_CLIENTID_TERMINAL_UP;
            readmsg.device_id = tmp->device_id;
            tmp=tmp->pnext;
            mysock_write(ser_info.helmet_terminal_ckd,&readmsg,sizeof(readmsg));
        } 
    }
    else{
        printf("终端ID不合法！或者已经有监视终端上线！\r\n");
        ser_info.helmet_terminal_ckd = 0;
        msg->command = XYD_MSG_TERMINAL_ERR;
        msg->sum = sum_value(*msg);
        mysock_write(ckd,msg,sizeof(HELMET_MSG));
    }
        

}
void deal_client_video(HELMET_MSG * msg,int ckd)
{
    msg = msg;
    ckd = ckd;
    int ret =mysock_read(ckd,recv_buf,msg->data_length);
    printf("服务器接受ret == %d\n",ret);
    printf("msg->data_length == %d\n",msg->data_length);
    if(sum_test(*msg))
    {
        if(ser_info.helmet_terminal_ckd >0)
        {
            msg->data_ptr = recv_buf;
            mysock_write(ser_info.helmet_terminal_ckd,msg,sizeof(HELMET_MSG));
            mysock_write(ser_info.helmet_terminal_ckd,msg->data_ptr,msg->data_length);
        }else 
        {
            msg->command = XYD_VIDEO_STOP;
            mysock_write(ser_info.helmet_terminal_ckd,msg,sizeof(HELMET_MSG));
        }
    }else 
    {
        printf("数据校验错误，正在同步客户端！\r\n");
        sync_client(ckd);
    }
   
}
// void deal_client_audio(HELMET_MSG * msg,int ckd)
// {
//     msg = msg;
//     ckd = ckd;
//     mysock_read(ckd,recv_buf,msg->data_length);
//     if(sum_test(*msg))
//     {
//         if(ckd != ser_info.helmet_terminal_ckd)
//         {
//             if(ser_info.helmet_terminal_ckd >0)
//             {
//                 msg->data_ptr = recv_buf;
//                 mysock_write(ser_info.helmet_terminal_ckd,msg,sizeof(HELMET_MSG));
//                 mysock_write(ser_info.helmet_terminal_ckd,msg->data_ptr,msg->data_length);
//             }else 
//             {
//                 msg->command = XYD_VIDEO_STOP;
//                 mysock_write(ser_info.helmet_terminal_ckd,msg,sizeof(HELMET_MSG));
//             }
//         }else
//         {
//             // int toclient_ckd = bydeviceid_get_ckd(msg->audio_device_id);
//             // if(toclient_ckd>0)
//             // {   
//                 msg->data_ptr = recv_buf;
//                 mysock_write(toclient_ckd,msg,sizeof(HELMET_MSG));
//                 mysock_write(toclient_ckd,msg->data_ptr,msg->data_length);
//             // }
//         }
//     }else 
//     {
//         printf("数据校验错误，正在同步客户端！\r\n");
//         sync_client(ckd);
//     }
// }
void deal_video_stop(HELMET_MSG * msg,int ckd)
{
    msg = msg;
    ckd = ckd;
    // int tmpckd = bydeviceid_get_ckd(msg->device_id);
    mysock_write(ckd,msg,sizeof(HELMET_MSG));
}
void deal_video_start(HELMET_MSG * msg,int ckd)
{

    msg = msg;
    ckd = ckd;
    // int tmpckd = bydeviceid_get_ckd(msg->device_id);
    mysock_write(ckd,msg,sizeof(HELMET_MSG));
   
}
void deal_client_audio_stop(HELMET_MSG * msg,int ckd)
{
    msg = msg;
    ckd = ckd;
    // int tmpckd = bydeviceid_get_ckd(msg->device_id);
    mysock_write(ckd,msg,sizeof(HELMET_MSG));
}
void deal_client_audio_start(HELMET_MSG * msg,int ckd)
{
    msg = msg;
    ckd = ckd;
    // int tmpckd = bydeviceid_get_ckd(msg->device_id);
    mysock_write(ckd,msg,sizeof(HELMET_MSG));
}
void deal_client_downline(HELMET_MSG * msg,int ckd)
{
    msg = msg;
    ckd = ckd;
    // mylist_remove(ckd);
    if(ser_info.helmet_terminal_ckd > 0)
    {
        mysock_write(ser_info.helmet_terminal_ckd,msg,sizeof(HELMET_MSG));
    }
}
