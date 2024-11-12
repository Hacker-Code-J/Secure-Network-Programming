#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "readnwrite.h"

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

#define BUF_SIZE    128

void error_handling(char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE + 1];
    char* testdata[] = {"Hello", "I am Kookmin", "Nice to meet you"};
    int n, idx, dataLen;

    if (argc != 3) {
        printf("Usage: %s <IP> <port>", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) error_handling("socket() error");    

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error!");
    else puts("Connected .........");

    for (idx = 0; idx < sizeof(testdata)/sizeof(char*); idx ++) {
        memset(buf, '#', sizeof(buf));
        dataLen = strnlen(testdata[idx], sizeof(buf));
        strncpy(buf, testdata[idx], dataLen);
        n = writen(sock, buf, BUF_SIZE);
        if (n == -1) error_handling("write() error");

        printf("[TCP Client] %d byte sent\n", n);
    }

    close(sock);

    return 0;
}