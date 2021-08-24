#ifndef _STREAM_H_
#define _STREAM_H_

#include "runtime.h"

#define MONGO_URI_SIZE				256
#define MONGO_APP_NAME_SIZE			32
#define MONGO_DB_SIZE				32

#define VIDEOS_PATH					"/home/videos"
#define IMAGES_PATH					"/home/images"

struct _HttpResponse;

extern RuntimeType RUNTIME;

extern unsigned int PORT;

extern unsigned int CERVER_RECEIVE_BUFFER_SIZE;
extern unsigned int CERVER_TH_THREADS;
extern unsigned int CERVER_CONNECTION_QUEUE;

// inits stream main values
extern unsigned int stream_init (void);

// ends stream main values
extern unsigned int stream_end (void);

#endif