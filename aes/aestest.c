// gcc -g -Wall -Wextra -o aestest aestest.c -lcrypto

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/bio.h>

#define AES_ENCRYPT     1
#define AES_DECRYPT     0

void aes_simple_test_class();

int main() {
    puts("AES CBC Mode TEST:");
    return 0;
}

void aes_simple_test_class() {
    AES_KEY aes_enc_key, aes_dec_key;

    const unsigned char MK[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
    };
    unsigned char iv_enc[AES_BLOCK_SIZE] = { 0x00, };
    unsigned char iv_dec[AES_BLOCK_SIZE] = { 0x00, };

    unsigned char PT[256] = { 0x00, };
    unsigned char CT[256] = { 0x00, };
    unsigned char DT[256] = { 0x00, };
    
    memcpy(iv_dec, iv_enc, sizeof(iv_enc));

    AES_set_encrypt_key(MK, 128, &aes_enc_key);
    AES_set_encrypt_key(MK, 128, &aes_dec_key);

    memset(PT, 'A', sizeof(PT));
    AES_cbc_encrypt(PT, CT, sizeof(PT), &aes_enc_key, iv_enc, AES_ENCRYPT);
    AES_cbc_encrypt(CT, DT, sizeof(CT), &aes_dec_key, iv_dec, AES_DECRYPT);

    puts("\n\nPT:");
    BIO_dump_fp(stdout, (const char*)PT, sizeof(PT));

    puts("\n\nCT:");
    BIO_dump_fp(stdout, (const char*)CT, sizeof(CT));

    puts("\n\nDT:");
    BIO_dump_fp(stdout, (const char*)DT, sizeof(DT));

    if (0 != memcmp(PT, DT, sizeof(PT))) fprintf(stderr, "\nDecryption Error!\n");
    else fprintf(stderr, "\nDecryption Succeeded!\n");
}
