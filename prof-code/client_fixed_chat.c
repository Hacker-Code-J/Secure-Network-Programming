#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <assert.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#include "readnwrite.h"
#include "aesenc.h"
#include "msg.h"

void error_handling(char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int sock;
    int len;
    struct sockaddr_in serv_adr;

    APP_MSG msg_in;
    APP_MSG msg_out;
    char PT[BUFSIZE + AES_BLOCK_SIZE] = { 0x00, };

    unsigned char KEY[AES_KEY_128] = { 0x00, };
    unsigned char IV[AES_KEY_128] = { 0x00, };
    unsigned char encryptedKey[BUFSIZE] = { 0x00, };

    BIO* rpub = NULL;
    RSA* rsa_pk = NULL;

    int n;
    int pt_len;
    int ct_len;

    RAND_poll();
    RAND_bytes(KEY, sizeof(KEY));

    for (int i = 0; i < AES_KEY_128; i++)
		IV[i] = (unsigned char)i;

	if (argc != 3) {
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) error_handling("socket() error");
    
	memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, 
                (struct sockaddr*)&serv_adr,
                sizeof(serv_adr)) == -1)
        error_handling("connect() error!");

	memset(&msg_out, 0, sizeof(msg_out));
	msg_out.type = PUBLIC_KEY_REQUEST;
	msg_out.type = htonl(msg_out.type);

	n = write(sock, &msg_out, sizeof(APP_MSG));
	if (n == -1) error_handling("write() error");

	memset(&msg_in, 0, sizeof(msg_out));
	n = read(sock, &msg_in, sizeof(APP_MSG));
	msg_in.type = ntohl(msg_in.type);
	msg_in.msg_len = htonl(msg_in.msg_len);
   
	if (n == -1) error_handling("readn() error");
	if (n == 0) error_handling("reading EOF");

	if (msg_in.type != PUBLIC_KEY) error_handling("message error");
	else { 
		BIO_dump_fp (stdout, (const char*)msg_in.payload, msg_in.msg_len);

		rpub = BIO_new_mem_buf(msg_in.payload, -1);
		BIO_write(rpub, msg_in.payload, msg_in.msg_len);
		if (!PEM_read_bio_RSAPublicKey, NULL, NULL)
			error_handling("PEM_read_bio_RSAPublicKey() error");
	}

	memset(&msg_out, 0, sizeof(msg_out));
	msg_out.type = ENCRYPTED_KEY;
	msg_out.type = htonl(msg_out.type);
	msg_out.msg_len = RSA_public_encrypt(sizeof(KEY), KEY, msg_out.payload, rsa_pk, RSA_PKCS1_OAEP_PADDING);
	msg_out.msg_len = htonl(msg_out.msg_len);

	n = write(sock, &msg_out, sizeof(APP_MSG));
	if (n == -1) error_handling("writen() error");

	getchar();

	while (1) {
		printf("Input a message > \n");
		if (fgets(PT, BUFSIZE+1, stdin) == NULL) break;

		len = strlen(PT);
		if (PT[len-1] == '\n') PT[len-1] = '\0';
		if (strlen(PT) == 0) break;
	}

	ct_len = encrypt((unsigned char*)PT, len, KEY, IV, msg_out.payload);
	msg_out.msg_len = htonl(ct_len);

	n = writen(sock, &msg_out, sizeof(APP_MSG));
	if (n == -1) {
		error_handling("writen() error");
		break;
	}

	n = readn(sock, &msg_in, sizeof(APP_MSG));

	if (n == -1) {
		error_handling("readn() error");
		break;
	} else if (n == 0) break;

	msg_in.type = ntohl(msg_in.type);
	msg_in.msg_len = ntohl(msg_in.msg_len);

    close(sock);
}