//
//  testc.c
//  macapp
//
//  Created by jiweiLi on 2020/12/12.
//  Copyright © 2020 . All rights reserved.
//

#include "testc.h"

static int rec_status = 0;//是否开始录制

void set_status(int status){
    rec_status = status;
}

int rec_audio(){
    
    // note  c 风格
    AVFormatContext* fmt_ctx=NULL;
    int ret = -1;
    char errors[1024]={0};
    
    //[[video device]:[audio device]]   : 代表可以选
    char devicename[] = ":0";//第一个音频设备
    
    AVPacket pkt;//分配在栈空间
    
    FILE *outfile = NULL;
    
    
    rec_status = 1;// start record
    
    //1 注册设备
    avdevice_register_all();
    
    //2 获取格式
    AVInputFormat * iformat = av_find_input_format("avfoundation");
    if (NULL == iformat)
    {
        printf("av_find_input_format fail\n");
        return -1;
    }
    
    //3 打开设备 url可以是本地地址或网络地址
    ret = avformat_open_input(&fmt_ctx, devicename,iformat, NULL);
    if (ret)
    {
        av_strerror(ret, errors, 1024);
        printf("avformat_open_input fail,[%d]%s",ret,errors);
        return -1;
    }
    
    //4 读数据
    av_init_packet(&pkt);
    
    outfile = fopen("/Users/jiweili/Desktop/macapp/macapp/audio.pcm", "wb+");
    if (NULL == outfile)
    {
        printf("fopen fail\n");
        return -1;
    }
    
    while((ret = av_read_frame(fmt_ctx, &pkt)) == 0 &&
           rec_status)
    {
        fwrite(pkt.data, pkt.size, 1, outfile);
        fflush(outfile); // 实时将缓冲区的数据写入文件 但是会对性能产生影响
        printf("pkt size is %d\n",pkt.size);
        
        av_packet_unref(&pkt);//释放每一次获取的Buf 的引用计数 与av_init_packet成对使用
    }
    
    
    avformat_close_input(&fmt_ctx);//释放申请的上下文空间 防止内存泄漏
    fclose(outfile);//关闭文件
    
    printf("Finish\n");
    return 0;
}
