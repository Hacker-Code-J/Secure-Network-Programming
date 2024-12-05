#ifndef _AESENC_H_
#define _AESENC_H_

void handleErrors(void);

int
encrypt (unsigned char* pt,
         int pt_len,
         unsigned char* key,
         unsigned char* iv,
         unsigned char* ct);

int
decrypt (unsigned char* ct,
         int ct_len,
         unsigned char* key,
         unsigned char* iv,
         unsigned char* pt);

#endif  // -AESENC_H_