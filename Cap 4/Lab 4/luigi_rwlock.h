#pragma once

#include<pthread.h>

void r_lock(pthread_mutex_t *mutex);

void r_unlock(pthread_mutex_t *mutex);

void w_lock(pthread_mutex_t *mutex);

void w_unlock(pthread_mutex_t *mutex);

void rw_init();

void rw_destroy();