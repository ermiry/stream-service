#ifndef _STREAM_ROUTES_MAIN_H_
#define _STREAM_ROUTES_MAIN_H_

struct _HttpReceive;
struct _HttpRequest;

// GET /api/stream
extern void stream_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET /api/stream/version
extern void stream_version_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET *
extern void stream_catch_all_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

#endif