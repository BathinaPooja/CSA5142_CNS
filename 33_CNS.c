#include <stdio.h>

#include <string.h>
void print_hex(const char *label, const unsigned char *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    DES_cblock key = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    DES_cblock iv = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    DES_key_schedule schedule;
    DES_set_key_checked(&key, &schedule);
    unsigned char plaintext[8] = "OpenAI!";
    unsigned char ciphertext[8];
    unsigned char decryptedtext[8];
    DES_ncbc_encrypt(plaintext, ciphertext, sizeof(plaintext), &schedule, &iv, DES_ENCRYPT);
    print_hex("Ciphertext", ciphertext, sizeof(ciphertext));
    DES_cblock iv_decrypt = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    DES_ncbc_encrypt(ciphertext, decryptedtext, sizeof(ciphertext), &schedule, &iv_decrypt, DES_DECRYPT);
    print_hex("Decrypted text", decryptedtext, sizeof(decryptedtext));
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
