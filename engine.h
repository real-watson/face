#ifndef __ENGINE_H__

extern "C" 
{
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h> 
	#include <libavcodec/avcodec.h>
	#include <libswresample/swresample.h>
}


#define URL "rtmp://120.77.214.213:1935/live_video/video"
#define OUT "helloworld.flv"
#define JPG "hello.jpg"
#define VERSION 6.01
#define FLAG 1
#define RTMP 1/*always do it not*/
#define FACE 0

extern void face_feature_detection(const char *filename, char *mesg);
extern int save_jpeg(AVFrame *pFrame,char *outfile, int width, int height);




#define __ENGINE_H__
#endif
