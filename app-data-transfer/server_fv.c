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
    int serv_sock, clnt_sock;
    char buf[BUF_SIZE + 1];
    int n, dataLen;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1) error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, 
             (struct sockaddr*)&serv_addr,
             sizeof(serv_addr)) == -1) error_handling("bind() error");

    if (listen(serv_sock, 5) == -1) error_handling("listen() error");

    while (1) { // 클라이언트로 부터 접속 요청을 받아서 클라이언트와 통신을 하기 위한 통신용 소켓을 만들기
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        
        if (clnt_sock == -1) error_handling("accept() error");
        printf("\n[TCP Server] Client connected: IP = %s, port=%d", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

        // 클라이언트가 전송하는 데이터를 전송받기 위해서 동작하는 부분
        while (1) {
            // reading fixed part
            n = readn(clnt_sock, &dataLen, sizeof(int));
            dataLen = ntohl(dataLen);
            if (n == -1) error_handling("readn() error!");
            else if (n == 0) break;
            
            // reading variable part
            n = readn(clnt_sock, buf, dataLen);
            if (n == -1) error_handling("readn() error!");
            else if (n == 0) break;

            buf[n] = '\0';
            printf("\n[TCP/%s:%d] %s", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port), buf);
        }
        close(clnt_sock);
        printf("\n[TCP Server] Client close: IP = %s, port=%d\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
    }
    
    close(serv_sock);

    return 0;
}