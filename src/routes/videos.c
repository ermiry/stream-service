#include <cerver/files.h>

#include <cerver/http/http.h>
#include <cerver/http/request.h>
#include <cerver/http/response.h>

#include "errors.h"
#include "stream.h"

#include "models/video.h"

#include "controllers/service.h"
#include "controllers/stream.h"

// GET /api/stream/videos
void stream_videos_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	size_t json_len = 0;
	char *json = NULL;

	if (!service_videos_get_all (&json, &json_len)) {
		if (json) {
			(void) http_response_json_custom_reference_send (
				http_receive,
				HTTP_STATUS_OK,
				json, json_len
			);

			free (json);
		}

		else {
			(void) http_response_send (not_found_error, http_receive);
		}
	}

	else {
		(void) http_response_send (not_found_error, http_receive);
	}

}

// GET /api/stream/videos/:id/info
void stream_video_data_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	const String *video_id = request->params[0];

	if (video_id) {
		size_t json_len = 0;
		char *json = NULL;

		if (!service_video_get_by_id_to_json (
			video_id->str,
			NULL,
			&json, &json_len
		)) {
			if (json) {
				(void) http_response_json_custom_reference_send (
					http_receive, HTTP_STATUS_OK, json, json_len
				);

				free (json);
			}

			else {
				(void) http_response_send (server_error, http_receive);
			}
		}

		else {
			(void) http_response_send (not_found_error, http_receive);
		}
	}

	else {
		(void) http_response_send (bad_request_error, http_receive);
	}

}

// GET /api/stream/videos/:id/image
void stream_video_image_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	const String *video_id = request->params[0];

	char image[VIDEO_IMAGE_SIZE] = { 0 };
	char filename[FILENAME_DEFAULT_SIZE] = { 0 };

	if (video_id) {
		ServiceError error = service_video_get_image (video_id->str, image);
		if (error == SERVICE_ERROR_NONE) {
			(void) snprintf (
				filename, FILENAME_DEFAULT_SIZE - 1,
				"%s/%s",
				IMAGES_PATH, image
			);

			(void) http_response_render_file (
				http_receive, HTTP_STATUS_OK, filename
			);
		}

		else {
			service_error_send_response (error, http_receive);
		}
	}

	else {
		(void) http_response_send (bad_request_error, http_receive);
	}

}

// GET /api/stream/videos/:id/data
void stream_video_info_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	const String *video_id = request->params[0];

	if (video_id) {
		// TODO:
	}

	else {
		(void) http_response_send (bad_request_error, http_receive);
	}

}
