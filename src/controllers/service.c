#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cerver/http/response.h>

#include <cerver/utils/utils.h>

#include "version.h"

#define VERSION_BUFFER_SIZE		64

HttpResponse *stream_works = NULL;
HttpResponse *current_version = NULL;

HttpResponse *catch_all = NULL;

unsigned int stream_service_init (void) {

	unsigned int retval = 1;

	stream_works = http_response_json_key_value (
		HTTP_STATUS_OK, "msg", "Stream service works!"
	);

	char version[VERSION_BUFFER_SIZE] = { 0 };
	(void) snprintf (
		version, VERSION_BUFFER_SIZE - 1,
		"%s - %s",
		STREAM_VERSION_NAME, STREAM_VERSION_DATE
	);

	current_version = http_response_json_key_value (
		HTTP_STATUS_OK, "version", version
	);

	catch_all = http_response_json_key_value (
		HTTP_STATUS_OK, "msg", "Stream service service!"
	);

	if (
		stream_works && current_version
		&& catch_all
	) retval = 0;

	return retval;

}

void stream_service_end (void) {

	http_response_delete (stream_works);
	http_response_delete (current_version);

	http_response_delete (catch_all);

}
