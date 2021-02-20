#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include "log.h"

static struct {
	pthread_mutex_t *lock;
	FILE *fp;
	int level;
	int quiet;
} _l;

static const char *_level_names[] = {
	"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

static const char *_level_colors[] = {
	"\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};

static void lock(void)
{
	if (!_l.lock) {
		_l.lock = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(_l.lock, NULL);
	}

	pthread_mutex_lock(_l.lock);
}

static void unlock(void)
{
	pthread_mutex_unlock(_l.lock);
}

void log_set_fp(FILE *fp)
{
	_l.fp = fp;
}

void log_set_level(int level)
{
	_l.level = level;
}

void log_set_quiet(int enable)
{
	_l.quiet = enable ? 1 : 0;
}

void log_write(int level, const char *file, const char *fmt, ...)
{
	if (level < _l.level)
		return;

	lock();

	time_t t = time(NULL);
	struct tm *lt = localtime(&t);

	if (!_l.quiet) {
		va_list args;
		char buf[16];
		buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';
		
		fprintf(stderr, "%s %s%-5s\x1b[0m \x1b[90m%d %s:\x1b[0m ", buf,
			_level_colors[level], 
			_level_names[level], getpid(), file);

		va_start(args, fmt);
		vfprintf(stderr, fmt, args);
		va_end(args);
		fprintf(stderr, "\n");
		fflush(stderr);
	}

	if (_l.fp) {
		va_list args;
		char buf[32];
		buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt)] = '\0';
		fprintf(_l.fp, "%s %-5s %d %s: ", buf, _level_names[level], getpid(), file);
		va_start(args, fmt);
		vfprintf(_l.fp, fmt, args);
		va_end(args);
		fprintf(_l.fp, "\n");
		fflush(_l.fp);
	}

	unlock();
}
