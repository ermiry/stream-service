#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <signal.h>

#include <cerver/cerver.h>
#include <cerver/version.h>

#include <cerver/http/http.h>
#include <cerver/http/route.h>

#include <cerver/utils/log.h>
#include <cerver/utils/utils.h>

#include "stream.h"
#include "version.h"

#include "routes/service.h"

static Cerver *stream_service = NULL;

void end (int dummy) {
	
	if (stream_service) {
		cerver_stats_print (stream_service, false, false);
		cerver_log_msg ("\nHTTP Cerver stats:\n");
		http_cerver_all_stats_print ((HttpCerver *) stream_service->cerver_data);
		cerver_log_line_break ();
		cerver_teardown (stream_service);
	}

	(void) stream_end ();

	cerver_end ();

	exit (0);

}

static void service_set_stream_routes (HttpCerver *http_cerver) {

	/* register top level route */
	// GET /api/stream
	HttpRoute *main_route = http_route_create (REQUEST_METHOD_GET, "stream", stream_handler);
	http_cerver_route_register (http_cerver, main_route);

	/* register stream children routes */
	// GET /api/stream/version
	HttpRoute *version_route = http_route_create (REQUEST_METHOD_GET, "version", stream_version_handler);
	http_route_child_add (main_route, version_route);

}

static void start (void) {

	stream_service = cerver_create (
		CERVER_TYPE_WEB,
		"stream-service",
		PORT,
		PROTOCOL_TCP,
		false,
		CERVER_CONNECTION_QUEUE
	);

	if (stream_service) {
		/*** cerver configuration ***/
		cerver_set_alias (stream_service, "stream");

		cerver_set_receive_buffer_size (stream_service, CERVER_RECEIVE_BUFFER_SIZE);
		cerver_set_thpool_n_threads (stream_service, CERVER_TH_THREADS);
		cerver_set_handler_type (stream_service, CERVER_HANDLER_TYPE_THREADS);

		/*** web cerver configuration ***/
		HttpCerver *http_cerver = (HttpCerver *) stream_service->cerver_data;

		service_set_stream_routes (http_cerver);

		// add a catch all route
		http_cerver_set_catch_all_route (http_cerver, stream_catch_all_handler);

		// admin configuration
		http_cerver_enable_admin_routes (http_cerver, true);
		http_cerver_register_admin_file_system (http_cerver, "/home/stream/uploads");

		if (cerver_start (stream_service)) {
			cerver_log_error (
				"Failed to start %s!",
				stream_service->info->name
			);

			cerver_delete (stream_service);
		}
	}

	else {
		cerver_log_error ("Failed to create cerver!");

		cerver_delete (stream_service);
	}

}

int main (int argc, char const **argv) {

	srand (time (NULL));

	// register to the quit signal
	(void) signal (SIGINT, end);
	(void) signal (SIGTERM, end);

	// to prevent SIGPIPE when writting to socket
	(void) signal (SIGPIPE, SIG_IGN);

	cerver_init ();

	cerver_version_print_full ();

	stream_version_print_full ();

	if (!stream_init ()) {
		start ();
	}

	else {
		cerver_log_error ("Failed to init stream!");
	}

	(void) stream_end ();

	cerver_end ();

	return 0;

}
