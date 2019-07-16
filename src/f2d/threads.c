#include <f2d/macros.h>
#include <f2d/threads.h>

#include <stdio.h>

#ifdef IS_UNIX
#include <pthread.h>
#elif IS_WINDOWS
#include <windows.h>
#endif

int thread_create(thread_t *thread, void *(*thread_func)(void *), void *argument) {
#ifdef IS_UNIX
    return pthread_create(thread, NULL, thread_func, argument);
#elif IS_WINDOWS
    int thread_id;
    void *handle;
    handle = CreateThread(0, 0, thread_func, argument, 0, &thread_id);
    return *((int *)handle);
#endif
}

int thread_join(thread_t thread, void **ret) {
#ifdef IS_UNIX
    return pthread_join(thread, ret);
#elif IS_WINDOWS
    (void)ret;
    WaitForSingleObject(thread, INFINITE);
    return 0;
#endif
}