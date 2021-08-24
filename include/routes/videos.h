#ifndef _STREAM_ROUTES_VIDEOS_H_
#define _STREAM_ROUTES_VIDEOS_H_

struct _HttpReceive;
struct _HttpRequest;


// GET /api/stream/videos
extern void stream_videos_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET /api/stream/videos/:id/info
extern void stream_video_data_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET /api/stream/videos/:id/image
extern void stream_video_image_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET /api/stream/videos/:id/data
extern void stream_video_info_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

#endif