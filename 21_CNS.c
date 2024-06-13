#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 8
void xor_encrypt_decrypt(char *input, char *key, char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}
void pad_plaintext(char *plaintext, int *length) {
    int pad_len = BLOCK_SIZE - (*length % BLOCK_SIZE);
    for (int i = 0; i < pad_len; i++) {
        plaintext[*length + i] = (i == 0) ? 0x80 : 0x00;  
    }
    *length += pad_len;
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
void cfb_mode(char *plaintext, char *key, char *iv, char *ciphertext, int length) {
    char buffer[BLOCK_SIZE];
    char feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        xor_encrypt_decrypt(feedback, key, buffer);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ buffer[j];
            feedback[j] = ciphertext[i + j];
        }
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
    char ciphertext_cfb[256];
    char decrypted_ecb[256];
    char decrypted_cbc[256];
    char decrypted_cfb[256];
    printf("Enter plaintext (max 255 characters): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; 
    int length = strlen(plaintext);
    printf("Enter key (8 characters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;  
    printf("Enter initialization vector (8 characters): ");
    fgets(iv, sizeof(iv), stdin);
    iv[strcspn(iv, "\n")] = 0;  
    pad_plaintext(plaintext, &length);
    printf("Original plaintext: %s\n", plaintext);
    ecb_mode(plaintext, key, ciphertext_ecb, length);
    printf("ECB ciphertext: ");
    print_hex(ciphertext_ecb, length);
    cbc_mode(plaintext, key, iv, ciphertext_cbc, length);
    printf("CBC ciphertext: ");
    print_hex(ciphertext_cbc, length);
    cfb_mode(plaintext, key, iv, ciphertext_cfb, length);
    printf("CFB ciphertext: ");
    print_hex(ciphertext_cfb, length);
    ecb_mode(ciphertext_ecb, key, decrypted_ecb, length);
    decrypted_ecb[length] = '\0';
    printf("Decrypted ECB plaintext: %s\n", decrypted_ecb);
    cbc_mode(ciphertext_cbc, key, iv, decrypted_cbc, length);
    decrypted_cbc[length] = '\0';
    printf("Decrypted CBC plaintext: %s\n", decrypted_cbc);
    cfb_mode(ciphertext_cfb, key, iv, decrypted_cfb, length);
    decrypted_cfb[length] = '\0';
    printf("Decrypted CFB plaintext: %s\n", decrypted_cfb);
    return 0;
}