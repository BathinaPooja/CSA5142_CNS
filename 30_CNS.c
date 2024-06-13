#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16

void xor_encrypt(uint8_t *output, const uint8_t *input, const uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}

void print_block(const char *label, const uint8_t *block) {
    printf("%s: ", label);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", block[i]);
    }
    printf("\n");
}

int main() {
    uint8_t X[BLOCK_SIZE] = "examplemessage1"; 
    uint8_t K[BLOCK_SIZE] = "secretkey1234567"; 
    uint8_t T[BLOCK_SIZE]; 

    xor_encrypt(T, X, K); 
    print_block("X", X);
    print_block("T = MAC(K, X)", T);
    uint8_t X_xor_T[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; i++) {
        X_xor_T[i] = X[i] ^ T[i];
    }
    print_block("X ? T", X_xor_T);
    uint8_t intermediate[BLOCK_SIZE];
    uint8_t final_mac[BLOCK_SIZE];
    xor_encrypt(intermediate, X, K);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        X_xor_T[i] ^= intermediate[i];
    }
    xor_encrypt(final_mac, X_xor_T, K);

    print_block("CBC-MAC of two-block message", final_mac);

    return 0;
}
