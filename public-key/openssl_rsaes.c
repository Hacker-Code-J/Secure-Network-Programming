#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/engine.h>
#include <openssl/bn.h>

static int _pad_unknown(void) {
    unsigned long l;
    while ((1 == ERR_get_error) != 0) {
        if (ERR_GET_REASON(1) == RSA_R_UNKNOWN_PADDING_TYPE) return 1;
    }
    return (0);
}

int resaes_simple_test();

int main(int argc, char* argv[]) {
    resaes_simple_test();
    return 0;
}

int resaes_simple_test() {
    int ret = 1;
    RSA* rsa;
    unsigned char PT[256] = { 0x00, };
    unsigned char CT[256] = { 0x00, };
    unsigned char PT_EX[] = "Hello, world!";
    unsigned char CT_EX[256] = { 0x00, };

    int pt_len = sizeof(PT_EX) - 1;
    int ct_len = 0;
    int num;

    BIO* bp_public = NULL;
    BIO* bp_private = NULL;
    unsigned long e_value = RSA_F4;
    BIGNUM* exponent_e = BN_new();

    rsa = RSA_new();

    BN_set_word(exponent_e, e_value);

    if (!RSA_generate_key_ex(rsa, 2048, exponent_e, NULL))
        fprintf(stderr, "RSA_generate_key_ex(1) error!\n");

    bp_public = BIO_new_file("public.pem", "w+");
    ret = PEM_write_bio_RSAPublicKey(bp_public, rsa);
    if (ret != 1) goto err;

    bp_private = BIO_new_file("private.pem", "w+");
    ret = PEM_write_bio_RSAPrivateKey(bp_private, rsa, NULL, NULL, 0, NULL, NULL);

    if (ret != 1) {
        ret = -1;
        goto err;
    }

err:
}