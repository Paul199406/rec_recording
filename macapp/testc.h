//
//  testc.h
//  macapp
//
//  Created by jiweiLi on 2020/12/12.
//  Copyright © 2. All rights reserved.
//

#ifndef testc_h
#define testc_h

#include <stdio.h>
#include <libavutil/avutil.h>
#include <libavdevice/avdevice.h>
#include <libavformat/avformat.h>  //对于ffmepg 所有的设备 多媒体文件 都是一种格式 都使用avformat 解析
#include <libavcodec/avcodec.h>

int rec_vedio(void);
void set_status(int status);
#endif /* testc_h */
