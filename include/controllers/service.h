#ifndef _STREAM_MAIN_H_
#define _STREAM_MAIN_H_

struct _HttpResponse;

extern struct _HttpResponse *stream_works;
extern struct _HttpResponse *current_version;

extern struct _HttpResponse *catch_all;

extern unsigned int stream_service_init (void);

extern void stream_service_end (void);

#endif