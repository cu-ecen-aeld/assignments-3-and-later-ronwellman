#define _XOPEN_SOURCE 500
#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg, ...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg, ...) printf("threading ERROR: " msg "\n", ##__VA_ARGS__)

void *threadfunc(void *thread_param)
{
    if (NULL == thread_param)
    {
        ERROR_LOG("threadfunc called with NULL parameter");
        return NULL;
    }

    struct thread_data *data = (struct thread_data *)thread_param;

    if (0 != usleep(data->wait_to_obtain_ms * 1000))
    {
        ERROR_LOG("usleep wait_to_obtain_ms failed in threadfunc");
        data->thread_complete_success = false;
        return thread_param;
    }

    if (0 != pthread_mutex_lock(data->mutex))
    {
        ERROR_LOG("pthread_mutex_lock failed in threadfunc");
        data->thread_complete_success = false;
        return thread_param;
    }

    if (0 != usleep(data->wait_to_release_ms * 1000))
    {
        ERROR_LOG("usleep wait_to_release_ms failed in threadfunc");
        data->thread_complete_success = false;
        return thread_param;
    }

    if (0 != pthread_mutex_unlock(data->mutex))
    {
        ERROR_LOG("pthread_mutex_unlock failed in threadfunc");
        data->thread_complete_success = false;
        return thread_param;
    }

    data->thread_complete_success = true;

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    // struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    return thread_param;
}

bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex, int wait_to_obtain_ms, int wait_to_release_ms)
{
    if (NULL == thread || NULL == mutex)
    {
        ERROR_LOG("start_thread_obtaining_mutex called with NULL parameters");
        return false;
    }

    struct thread_data *thread_data = malloc(sizeof(struct thread_data));
    if (NULL == thread_data)
    {
        ERROR_LOG("Failed to allocate memory for thread_data");
        return false;
    }

    thread_data->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_data->wait_to_release_ms = wait_to_release_ms;
    thread_data->mutex = mutex;
    thread_data->thread_complete_success = false;

    if (0 != pthread_create(thread, NULL, threadfunc, thread_data))
    {
        ERROR_LOG("Failed to create thread");
        free(thread_data);
        return false;
    }

    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

    return true;
}
