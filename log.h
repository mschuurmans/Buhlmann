#ifndef __LOG_H_
#define __LOG_H_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

typedef void (*log_lock_function)(void*, int);

#define log_trace(...) log_write(LOG_TRACE, __FILENAME__, __VA_ARGS__)
#define log_debug(...) log_write(LOG_DEBUG, __FILENAME__, __VA_ARGS__)
#define log_info(...) log_write(LOG_INFO, __FILENAME__, __VA_ARGS__)
#define log_warn(...) log_write(LOG_WARN, __FILENAME__, __VA_ARGS__)
#define log_error(...) log_write(LOG_ERROR, __FILENAME__, __VA_ARGS__)
#define log_fatal(...) log_write(LOG_FATAL, __FILENAME__, __VA_ARGS__)

void log_set_fp(FILE *fp);
void log_set_level(int level);
void log_set_quiet(int enable);

void log_write(int level, const char *file, const char *fmt, ...);

#endif
