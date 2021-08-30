#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cerver/http/http.h>
#include <cerver/http/response.h>

#include <cerver/utils/log.h>

#include "errors.h"

#include "models/video.h"

unsigned int service_videos_get_all (
	char **json, size_t *json_len
) {

	return videos_get_all_to_json (
		NULL, json, json_len
	);

}

static ServiceError service_video_get_by_id (
	const char *video_id, Video **found
) {

	ServiceError error = SERVICE_ERROR_NONE;

	Video *video = video_new ();
	if (video) {
		bson_oid_t video_oid = { 0 };
		bson_oid_init_from_string (&video_oid, video_id);

		if (!video_get_by_oid (video, &video_oid, NULL)) {
			*found = video;
		}

		else {
			cerver_log_error ("Failed to get video %s!", video_id);

			error = SERVICE_ERROR_NOT_FOUND;

			video_delete (video);
		}
	}

	else {
		error = SERVICE_ERROR_SERVER_ERROR;
	}

	return error;

}

ServiceError service_video_get_image (
	const char *video_id, char *filename
) {

	Video *video = NULL;

	ServiceError error = service_video_get_by_id (
		video_id, &video
	);

	if (error == SERVICE_ERROR_NONE) {
		(void) strncpy (filename, video->image, VIDEO_IMAGE_SIZE - 1);

		video_delete (video);
	}

	return error;

}

unsigned int service_video_get_by_id_to_json (
	const char *video_id,
	const bson_t *query_opts,
	char **json, size_t *json_len
) {

	unsigned int retval = 1;

	if (video_id) {
		bson_oid_t video_oid = { 0 };
		bson_oid_init_from_string (&video_oid, video_id);

		retval = video_get_by_oid_to_json (
			&video_oid,
			query_opts,
			json, json_len
		);
	}

	return retval;

}

ServiceError service_video_stream (
	const HttpReceive *http_receive,
	const char *video_id, const char *range
) {

	Video *video = NULL;

	ServiceError error = service_video_get_by_id (
		video_id, &video
	);

	if (error == SERVICE_ERROR_NONE) {
		http_response_handle_video (
			http_receive, video->filename
		);

		video_delete (video);
	}

	return error;

}
