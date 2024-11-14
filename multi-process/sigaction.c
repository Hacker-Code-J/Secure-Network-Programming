#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig) {
    if (sig == SIGALRM) puts("TIme out!");

    alarm(2);
}

int main(int argc, char* argv[]) {
    int idx;
    struct sigaction act;

    // act
    return 0;
}