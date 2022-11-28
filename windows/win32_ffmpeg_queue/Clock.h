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
#include "VideoState.h"

#ifndef CLOCK_H
#define CLOCK_H
class Clock {
		double pts; /* clock base */
		double
			pts_drift; /* clock base minus time at which we updated the clock */
		double last_updated;
		double speed;
		int serial; /* clock is based on a packet with this serial */
		int paused;
		std::queue<int>
			queue_serial; /* pointer to the current packet queue serial, used
							 for obsolete clock detection */

		double get_clock(Clock* c);

		void set_clock_at(Clock* c, double pts, int serial, double time);

		void set_clock(Clock* c, double pts, int serial);

		void set_clock_speed(Clock* c, double speed);

		void init_clock(Clock* c, int queue_serial);

		void sync_clock_to_slave(Clock* c, Clock* slave);

		int get_master_sync_type(VideoState* is);
		
		double get_master_clock(VideoState* is);

		void check_external_clock_speed(VideoState* is);
};
#endif