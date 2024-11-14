#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig) {
    int status;
    __pid_t id = waitpid(-1, &status, WNOHANG);

    if (WIFEXITED(status)) {
        printf("Removed PID: %d\n", id);
        printf("Child send %d\n", WEXITSTATUS(status));
    }
}

int main(int argc, char* argv[]) {
    __pid_t pid;
    struct sigaction act;

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    pid = fork();

    if (pid == 0) {
        printf("Hi, I am a child process\n");
        sleep(10);
        return 12;
    } else {
        printf("Child PID: %d\n", pid);
        pid = fork();
        if (pid == 0) {
            printf("Hi, I am a child process\n");
            sleep(15);
            exit(24);
        } else {
            printf("Child PID: %d\n", pid);
            for (int i = 0; i < 8; i++) {
                puts("Wait...");
                sleep(5);
            }
        }
    }
    return 0;
}