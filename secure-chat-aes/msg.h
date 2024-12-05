#ifndef _MSG_H_
#define _MSG_H_

// #define AES_BLOCK_SIZE  16
#define AES_KEY_128     16
#define BUFSIZE         256

typedef struct _APP_MSG_ {
    int type;
    unsigned char pyload[BUFSIZE + AES_BLOCK_SIZE];
    int msg_len;
} APP_MSG;

#endif  // _MSG_H_