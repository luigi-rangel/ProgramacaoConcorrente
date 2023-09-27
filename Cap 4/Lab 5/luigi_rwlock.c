#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "luigi_rwlock.h"

pthread_cond_t rcond, wcond;
int w = 0, r = 0;

void r_lock(pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
    while (w != 0)
    {
        pthread_cond_wait(&rcond, mutex);
    }
    r++;
    pthread_mutex_unlock(mutex);
}

void r_unlock(pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
    r--;
    if (r == 0) pthread_cond_signal(&wcond);
    pthread_mutex_unlock(mutex);
}

void w_lock(pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
    while (r != 0 || w != 0)
    {
        pthread_cond_wait(&wcond, mutex);
    }
    w++;
    pthread_mutex_unlock(mutex);
}

void w_unlock(pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
    w--;
    pthread_cond_broadcast(&rcond);
    pthread_cond_signal(&wcond);
    pthread_mutex_unlock(mutex);
}

void rw_init() {
    pthread_cond_init(&rcond, NULL);
    pthread_cond_init(&wcond, NULL);
}

void rw_destroy() {
    pthread_cond_destroy(&rcond);
    pthread_cond_destroy(&wcond);
}