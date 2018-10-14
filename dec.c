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
/*Error handler*/
void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
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


int main (void)
{
char buf[100];
FILE *outFile; //The output file (encrypted)

  /* A 256 bit key */
  unsigned char key[] ="01234567890123456789012345678901";

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"01234567890123456";
int count=0;
/* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);

while(count<10)
{
 int fd;
 struct stat sb;
void * memblock;
sprintf(buf,"result%d.jpg",count);
  fd = open(buf,O_RDONLY,0666);
	if(fd==-1){printf("Error opening original file"); return 1;}

  fstat(fd, &sb);


unsigned char plaintext[sb.st_size];

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[sb.st_size];

  int decryptedtext_len, ciphertext_len;

  /* Initialise the library */
 /* ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);*/

 memblock = mmap(NULL, sb.st_size,PROT_READ, MAP_SHARED, fd, 0);
 if (memblock == MAP_FAILED) {
	close(fd);
	perror("Error mapping the file");
	exit(EXIT_FAILURE);
    }
decryptedtext_len = decrypt((unsigned char *)memblock, sb.st_size,key,iv,plaintext);
close(fd);
outFile=fopen(buf,"wb");
fwrite( plaintext,1, decryptedtext_len,outFile);
fclose(outFile);
SHA256(key, strlen(key),key);
count++;
}
  
  EVP_cleanup();
  ERR_free_strings();	

  return 0;
}


