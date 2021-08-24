#include <stdlib.h>

#include <cerver/files.h>

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

ServiceError service_video_get_image (
	const char *video_id, const char *filename
) {

	ServiceError error = SERVICE_ERROR_NONE;

	Video *video = video_new ();
	if (video) {
		bson_oid_t video_oid = { 0 };
		bson_oid_init_from_string (&video_oid, video_id);

		if (!video_get_by_oid (video, &video_oid, NULL)) {
			(void) strncpy (filename, video->filename, VIDEO_IMAGE_SIZE - 1);
		}

		else {
			cerver_log_error ("Failed to get video %s!", video_id);

			error = SERVICE_ERROR_NOT_FOUND;
		}

		video_delete (video);
	}

	else {
		error = SERVICE_ERROR_SERVER_ERROR;
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
