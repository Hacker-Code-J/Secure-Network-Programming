#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

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
    char msg[BUF_SIZE + 1];
    int str_len;
    struct sockaddr_in serv_addr;
    
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

    while (1) {
        fputs("Input message (Q to quit): ", stdout);
        fgets(msg, BUF_SIZE, stdin);

        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) break;

        write(sock, msg, strlen(msg));
        str_len = read(sock, msg, BUF_SIZE);
        msg[str_len] = '\0';
        printf("Message from server: %s \n", msg);
    }
    
    close(sock);

    return 0;
}