#ifndef _STREAM_VERSION_H_
#define _STREAM_VERSION_H_

#define STREAM_VERSION			"0.1"
#define STREAM_VERSION_NAME		"Version 0.1"
#define STREAM_VERSION_DATE		"17/08/2021"
#define STREAM_VERSION_TIME		"23:11 CST"
#define STREAM_VERSION_AUTHOR	"Erick Salas"

// print full stream version information
extern void stream_version_print_full (void);

// print the version id
extern void stream_version_print_version_id (void);

// print the version name
extern void stream_version_print_version_name (void);

#endif