#include <cerver/utils/log.h>

#include "version.h"

// print full test version information
void stream_version_print_full (void) {

	cerver_log_both (
		LOG_TYPE_NONE, LOG_TYPE_NONE,
		"\nStream Service Version: %s", STREAM_VERSION_NAME
	);

	cerver_log_both (
		LOG_TYPE_NONE, LOG_TYPE_NONE,
		"Release Date & time: %s - %s", STREAM_VERSION_DATE, STREAM_VERSION_TIME
	);

	cerver_log_both (
		LOG_TYPE_NONE, LOG_TYPE_NONE,
		"Author: %s\n", STREAM_VERSION_AUTHOR
	);

}

// print the version id
void stream_version_print_version_id (void) {

	cerver_log_both (
		LOG_TYPE_NONE, LOG_TYPE_NONE,
		"\nStream Service Version ID: %s\n", STREAM_VERSION
	);

}

// print the version name
void stream_version_print_version_name (void) {

	cerver_log_both (
		LOG_TYPE_NONE, LOG_TYPE_NONE,
		"\nStream Service Version: %s\n", STREAM_VERSION_NAME
	);

}
