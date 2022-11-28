#pragma once
#include <queue>
#include "libavutil/avstring.h"
#include "libavutil/channel_layout.h"
#include "libavutil/eval.h"
#include "libavutil/mathematics.h"
#include "libavutil/pixdesc.h"
#include "libavutil/imgutils.h"
#include "libavutil/dict.h"
#include "libavutil/fifo.h"
#include "libavutil/parseutils.h"
#include "libavutil/samplefmt.h"
#include "libavutil/time.h"
#include "libavutil/bprint.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libavutil/opt.h"
#include "libavcodec/avfft.h"
#include "libswresample/swresample.h"
#include "Config.h"

#ifndef VIDEO_STATE_H
#define VIDEO_STATE_H

class Clock;
typedef struct VideoState {
		int av_sync_type = AV_SYNC_AUDIO_MASTER;
		AVStream* video_st;
		AVStream* audio_st;
		Clock* vidclk;
		Clock* audclk;
		Clock* extclk;
		int video_stream;
		int audio_stream;
		std::queue<AVFifo*>* videoq;
		std::queue<AVFifo*>* audioq;
} VideoState;
#endif