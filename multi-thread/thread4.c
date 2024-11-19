// gcc -g thread4.c -o thread4 -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREAD 100

long long num = 0;

void* thread_increase(void* arg) {
    for (int i = 0; i < 50000000; i++)
        num += 1;
    return NULL;
}
void* thread_decrease(void* arg) {
    for (int i = 0; i < 50000000; i++)
        num -= 1;
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t thread_id[NUM_THREAD];

    printf("Size of long long: %ld-byte\n", sizeof(long long));

    for (int i = 0; i < NUM_THREAD; i++) {
        if (i % 2)
            pthread_create(&(thread_id[i]), NULL, thread_increase, NULL);
        else 
            pthread_create(&(thread_id[i]), NULL, thread_decrease, NULL);
    }

    for (int i = 0; i < NUM_THREAD; i++)
        pthread_join(thread_id[i], NULL);

    printf("result: %lld\n", num);

    return 0;
}