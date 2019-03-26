#ifndef THREADS_H
#define THREADS_H

#include <game/macros.h>

#ifdef IS_UNIX
#include <pthread.h>
typedef pthread_t thread_t;
#elif IS_WINDOWS
typedef int thread_t;
#endif

int thread_create(thread_t *thread, void *(*thread_func)(void *), void *argument);
int thread_join(thread_t thread, void **ret);

#endif