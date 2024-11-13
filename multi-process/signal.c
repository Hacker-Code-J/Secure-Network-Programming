#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig) {
    if (sig == SIGALRM) puts("Time out!");
    alarm(2);
}

void keycontrol(int sig) {
    if (sig == SIGINT) puts("CTR + C pressed!");
}

int main(int argc, char* argv[]) {
    int idx;

    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    for (idx = 0; idx < 3; idx++) {
        printf("wait...");
        sleep(100);
    }

    return 0;
}