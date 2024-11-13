#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        sleep(40);
        return 3;
    } else {
        printf("Child PID: %d\n", pid);
        pid = fork();

        if (pid == 0) {
            sleep(40);
            exit(7);
        } else {
            printf("Child PID: %d\n", pid);
            wait(&status);
            if (WIFEXITED(status))
                printf("Child send one: %d\n", WEXITSTATUS(status));
            
            wait(&status);
            if (WIFEXITED(status))
                printf("Child send one: %d\n", WEXITSTATUS(status));
            sleep(30);
        }
    }

    return 0;
}