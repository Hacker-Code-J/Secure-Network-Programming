// gcc -g thread1.c -o thread1 -lpthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_main(void* arg) {
    int cnt = *((int*)arg);
    for (int i = 0; i < cnt; i++) {
        sleep(1);
        printf("Running Thread\n");
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t t_id;
    int thread_param = 5;
    if (pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0) {
        fprintf(stderr, "pthread_create() error!\n");
        return -1;
    }
    sleep(10);
    printf("end of main\n");
    
    return 0;
}