// gcc -g mutex.c -o mutex -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#ifdef __i386
#include <x86intrin.h> // Use this on x86 platforms
#elif defined(__x86_64)
#include <x86intrin.h> // Use this on x86_64 platforms
#endif

#define NUM_THREAD 100

long long num = 0;
pthread_mutex_t mutex;

void* thread_increase(void* arg) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 50000000; i++)
        num += 1;
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void* thread_decrease(void* arg) {
    for (int i = 0; i < 50000000; i++) {
        pthread_mutex_lock(&mutex);
        num -= 1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    // __uint32_t ui;
    // __uint64_t start, end;

    pthread_t thread_id[NUM_THREAD];

    printf("Size of long long: %ld-byte\n", sizeof(long long));

    // start = __rdtscp(&ui);
    for (int i = 0; i < NUM_THREAD; i++) {
        if (i % 2)
            pthread_create(&(thread_id[i]), NULL, thread_increase, NULL);
        else 
            pthread_create(&(thread_id[i]), NULL, thread_decrease, NULL);
    }

    for (int i = 0; i < NUM_THREAD; i++)
        pthread_join(thread_id[i], NULL);
    // end = __rdtscp(&ui);
    
    printf("result: %lld\n", num);
    // printf("took: %ld\n", (end - start));
    return 0;
}