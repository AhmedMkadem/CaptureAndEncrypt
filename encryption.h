// This content is based on this tutorial : https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_C_libraries.html

#ifndef _ENCRYPTION_
#define _ENCRYPTION_


void handleErrors(void);

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext);

int chiffrer (int number);


#endif

