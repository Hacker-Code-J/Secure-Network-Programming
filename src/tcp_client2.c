#include "config.h"

void error_handling(char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char msg[30];
    int str_len = 0;
    int idx = 0, read_len = 0;

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

    while ((read_len = read(sock, &msg[idx++], 1))) {
        if (read_len == -1) {
            error_handling("read() error!");
            break;
        }
        str_len += read_len;
    }

    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf("wait time: %d\n", i);
    }
    read_len = read(sock, msg, sizeof(msg));
    
    printf("Message from server: %s \n", msg);
    printf("Function read call count: %d \n", str_len);

    close(sock);

    return 0;
}