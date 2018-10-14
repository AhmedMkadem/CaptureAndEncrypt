//This code is based on openssl implementation: https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "encryption.h"
/*Error handler*/
void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}


/*The encrypt function*/
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();


  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

/*The decrypt function*/
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}


int chiffrer (int number)
{
int count;
//printf("begin");
 // The file to be encrypted
char buf[100];
FILE *outFile; //The output file (encrypted)
  /* Set up the key and iv. Do I need to say to not hard code these in a
   * real application? :-)
   */
/*An initial key of 256 bit*/
unsigned char key[]="01234567890123456789012345678901";


  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"01234567890123456";
int decryptedtext_len, ciphertext_len;
void * memblock;


/* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);


while(count<number){
sprintf(buf,"result%d.jpg",count);

 int fd;
 struct stat sb;

  fd = open(buf,O_RDONLY,0666);
	if(fd==-1){printf("Error opening original file"); return 1;}
  fstat(fd, &sb);


 unsigned char ciphertext[sb.st_size];

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[sb.st_size];

 /*Mapping the file to memory*/
 memblock = mmap(NULL, sb.st_size,PROT_READ, MAP_SHARED, fd, 0);
 if (memblock == MAP_FAILED) {
	close(fd);
	perror("Error mapping the file");
	exit(EXIT_FAILURE);
    }
/*Perform the encryption process*/
ciphertext_len = encrypt((unsigned char *)memblock, sb.st_size,key,iv,ciphertext);
close(fd);
outFile=fopen(buf,"wb");
/*Overried the original file*/
fwrite( ciphertext,1, ciphertext_len,outFile);
fclose(outFile);
SHA256(key, strlen(key),key); //update the key 
count++;}
  EVP_cleanup();
  ERR_free_strings();	

  return 0;
}


