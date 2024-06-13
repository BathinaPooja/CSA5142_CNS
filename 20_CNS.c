#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 8
void xor_encrypt_decrypt(char *input, char *key, char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}
void ecb_mode(char *plaintext, char *key, char *ciphertext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        xor_encrypt_decrypt(&plaintext[i], key, &ciphertext[i]);
    }
}
void cbc_mode(char *plaintext, char *key, char *iv, char *ciphertext, int length) {
    char buffer[BLOCK_SIZE];
    char previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE);
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            buffer[j] = plaintext[i + j] ^ previous_block[j];
        }
        xor_encrypt_decrypt(buffer, key, &ciphertext[i]);
        memcpy(previous_block, &ciphertext[i], BLOCK_SIZE);
    }
}
void print_hex(char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02x ", (unsigned char)data[i]);
    }
    printf("\n");
}
int main() {
    char plaintext[256];
    char key[BLOCK_SIZE + 1];
    char iv[BLOCK_SIZE + 1];
    char ciphertext_ecb[256];
    char ciphertext_cbc[256];
    char decrypted_ecb[256];
    char decrypted_cbc[256];
    printf("Enter plaintext (max 255 characters): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; 
    int length = strlen(plaintext);
    if (length % BLOCK_SIZE != 0) {
        length += BLOCK_SIZE - (length % BLOCK_SIZE);  
    }
    printf("Enter key (8 characters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;  
    printf("Enter initialization vector (8 characters): ");
    fgets(iv, sizeof(iv), stdin);
    iv[strcspn(iv, "\n")] = 0;  
    printf("Original plaintext: %s\n", plaintext);
    ecb_mode(plaintext, key, ciphertext_ecb, length);
    printf("ECB ciphertext: ");
    print_hex(ciphertext_ecb, length);
    cbc_mode(plaintext, key, iv, ciphertext_cbc, length);
    printf("CBC ciphertext: ");
    print_hex(ciphertext_cbc, length);
    ecb_mode(ciphertext_ecb, key, decrypted_ecb, length);
    decrypted_ecb[length] = '\0';
    printf("Decrypted ECB plaintext: %s\n", decrypted_ecb);
    cbc_mode(ciphertext_cbc, key, iv, decrypted_cbc, length);
    decrypted_cbc[length] = '\0';
    printf("Decrypted CBC plaintext: %s\n", decrypted_cbc);
    return 0;
}