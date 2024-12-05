#include "aesenc.h"
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>

void handleErrors(void) {
    ERR_print_erros_fp(stderr);
    abort();
}

int
encrypt (unsigned char* pt,
         int pt_len,
         unsigned char* key,
         unsigned char* iv,
         unsigned char* ct) {
    EVP_CIPHER_CTX* ctx;

    int len, ct_len;

    if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handleErrors();
    
    if (1 != EVP_EncryptUpdate(ctx, ct, &len, pt, pt_len)) handleErrors();
    ct_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ct + len, &len)) handleErrors();
    ct_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ct_len;
}

int
decrypt (unsigned char* ct,
         int ct_len,
         unsigned char* key,
         unsigned char* iv,
         unsigned char* pt) {
    EVP_CIPHER_CTX* ctx;

    int len, pt_len;

    if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handleErrors();
    
    if (1 != EVP_EncryptUpdate(ctx, pt, &len, ct, ct_len)) handleErrors();
    pt_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, pt + len, &len)) handleErrors();
    pt_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return pt_len;
}