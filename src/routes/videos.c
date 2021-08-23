#include <cerver/http/http.h>
#include <cerver/http/request.h>
#include <cerver/http/response.h>

#include "controllers/service.h"

// GET /api/stream/videos
void stream_videos_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	(void) http_response_send (oki_doki, http_receive);

}

// GET /api/stream/videos/:id/info
void stream_video_data_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	(void) http_response_send (oki_doki, http_receive);

}

// GET /api/stream/videos/:id/data
void stream_video_info_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	(void) http_response_send (oki_doki, http_receive);

}
