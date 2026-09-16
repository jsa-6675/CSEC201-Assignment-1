#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 100

void xor_encrypt_decrypt(char *data, int length, const char *key) {
    for (int i = 0; i < length; ++i) {
        data[i] ^= key[i % strlen(key)];
    }
}

int main() {
    char choice[20];
    printf("Enter 'encrypt' or 'decrypt': ");
    scanf("%s", choice);

    if (strcmp(choice, "encrypt") != 0 && strcmp(choice, "decrypt") != 0) {
        printf("Invalid choice. Please enter 'encrypt' or 'decrypt'.\n");
        return 1;
    }

    char filename[256];
    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, (strcmp(choice, "encrypt") == 0) ? "w" : "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char key[MAX_KEY_LENGTH];
    printf("Enter the key: ");
    fgets(key, MAX_KEY_LENGTH, stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    if (strcmp(choice, "encrypt") == 0) {
        char plaintext[1024];
        printf("Enter the string to encrypt: ");
        fgets(plaintext, sizeof(plaintext), stdin);
        plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

        xor_encrypt_decrypt(plaintext, strlen(plaintext), key);

        fwrite(plaintext, 1, strlen(plaintext), file);
    } else {
        char ciphertext[1024];
        size_t bytes_read = fread(ciphertext, 1, sizeof(ciphertext) - 1, file);
        if (bytes_read == 0) {
            perror("Error reading file");
            fclose(file);
            return 1;
        }
        ciphertext[bytes_read] = '\0';

        xor_encrypt_decrypt(ciphertext, bytes_read, key);

        printf("Decrypted text: %s\n", ciphertext);
    }

    fclose(file);
    return 0;
}