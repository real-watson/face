#ifndef __ENGINE_H__

extern "C" 
{
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h> 
	#include <libavcodec/avcodec.h>
	#include <libswresample/swresample.h>

	#include "libavutil/opt.h"
	#include "libavutil/pixdesc.h"
}


#define URL "rtmp://120.77.214.213:1935/live_video/video"
#define OUT "helloworld.flv"
#define JPG "hello.jpg"
#define VERSION 7.01
#define FLAG 1
#define RTMP 1/*always do it not*/
#define FACE 1
#define CONFIG_PATH "config.txt"
#define CONFIG_TMP "config_tmp.txt"
#define MAX_AUDIO_FRAME_SIZE 92000

extern void face_feature_detection(const char *filename, char *mesg);
extern int save_jpeg(AVFrame *pFrame,char *outfile, int width, int height);
extern int util_get_string(char *key,char *string);
extern int util_match_string(char *key,char *string);
extern int util_set_string(char *key,char *string);




#define __ENGINE_H__
#endif
