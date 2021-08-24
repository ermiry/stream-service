#ifndef _SERVICE_STREAM_H_
#define _SERVICE_STREAM_H_

#include <bson/bson.h>

extern unsigned int service_videos_get_all (
	char **json, size_t *json_len
);

extern ServiceError service_video_get_image (
	const char *video_id, const char *filename
);

extern unsigned int service_video_get_by_id_to_json (
	const char *video_id,
	const bson_t *query_opts,
	char **json, size_t *json_len
);

#endif