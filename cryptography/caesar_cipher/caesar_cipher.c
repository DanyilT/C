//
// Created by Dany on 07/15/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Caesar Cipher Implementation in C
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Buffer for input (plaintext / ciphertext), can hold up to 255 characters (plus null terminator)
#define MAX_INPUT_LENGTH 256

char *caesar_encrypt(char *plaintext, int key);
char *caesar_decrypt(char *ciphertext, int key);
void caesar_brute_force(const char *ciphertext);

int main(int argc, char **argv) {
    // Define a buffer for plaintext input and a variable for the key
    char plaintext[MAX_INPUT_LENGTH];
    char ciphertext[MAX_INPUT_LENGTH];
    int key;
    int operation = 0;

    // Check if key is provided as a command line argument
    if (argc == 2 || argc == 3) {
        key = atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s <shift value (key)> <operation (e/d)>\n", argv[0]);
        printf("Enter shift value (key): ");
        if (scanf("%d", &key) != 1) {
            fprintf(stderr, "Invalid input. Please enter a valid integer for the key.\n");
            return 1;
        }
        while (getchar() != '\n'); // Clear the input buffer
    }

    // Check if operation (encryption / decryption) type is provided as a command line argument
    if (argc == 3) {
        if (strcasecmp(argv[2], "e") == 0 || strcasecmp(argv[2], "encrypt") == 0 || strcasecmp(argv[2], "encryption") == 0) {
            operation = 1; // Encrypt
        } else if (strcasecmp(argv[2], "d") == 0 || strcasecmp(argv[2], "decrypt") == 0 || strcasecmp(argv[2], "decryption") == 0) {
            operation = 2; // Decrypt
        } else if (strcasecmp(argv[2], "bf") == 0 || strcasecmp(argv[2], "brute-force") == 0) {
            operation = 3; // Brute Force Decrypt
        } else {
            fprintf(stderr, "Invalid operation. Use 'e' for encrypt or 'd' for decrypt, or 'bf' for brute force decrypt.\n");
            return 1;
        }
    } else {
        // Prompt the user for choose the operation (encryption or decryption)
        printf("Choose operation:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Brute Force Decrypt\n");
        if (scanf("%d", &operation) != 1 || (operation < 1 && operation > 3)) {
            fprintf(stderr, "Invalid choice. Please enter 1, 2 or 3.\n");
            return 1;
        }
        while (getchar() != '\n'); // Clear the input buffer
    }

    if (operation == 1) {
        // Encrypt operation
        printf("You chose to encrypt.\n");
        printf("--------------------\n");

        // Prompt the user for plaintext input
        printf("Enter plaintext: ");
        fgets(plaintext, sizeof(plaintext), stdin); // Read plaintext input from the user
        plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

        // Encrypt the plaintext using the Caesar cipher with the specified key
        caesar_encrypt(plaintext, key);
        printf("Encrypted text: %s\n", plaintext);
    } else if (operation == 2) {
        // Decrypt operation
        printf("You chose to decrypt.\n");
        printf("--------------------\n");

        // Prompt the user for ciphertext input
        printf("Enter ciphertext: ");
        fgets(ciphertext, sizeof(ciphertext), stdin); // Read ciphertext input from the user
        ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

        // Decrypt the ciphertext using the Caesar cipher with the specified key
        caesar_decrypt(ciphertext, key);
        printf("Decrypted text: %s\n", ciphertext);
    } else if (operation == 3) {
        // Brute Force Decrypt operation
        printf("You chose to brute force decrypt.\n");
        printf("------------------------------\n");

        // Prompt the user for ciphertext input
        printf("Enter ciphertext: ");
        fgets(ciphertext, sizeof(ciphertext), stdin); // Read ciphertext input from the user
        ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

        // Perform brute force decryption on the ciphertext
        caesar_brute_force(ciphertext);
    } else {
        fprintf(stderr, "Invalid operation selected.\n");
        return 1;
    }

    return 0;
}

/**
 * Encrypts the given plaintext using the Caesar cipher.
 *
 * Each alphabetic character in the input string is shifted by the specified key value.
 * Non-alphabetic characters remain unchanged.
 *
 * \param plaintext Pointer to the input string to encrypt. The string is modified in place.
 * \param key       The shift value for the cipher (can be positive or negative).
 * \return          Pointer to the encrypted string (same as plaintext).
 */
char *caesar_encrypt(char *plaintext, const int key) {
    for (int i = 0, len = strlen(plaintext); i < len; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            int shift = (key % 26 + 26) % 26; // Ensure the shift is non-negative and within the range of 0-25
            plaintext[i] = (plaintext[i] - base + shift) % 26 + base;
            /*
             * `plaintext[i] - base`    -- Converts the character to a zero-based index relative to its alphabet (0-25 range)
             * `+ shift`                -- Adds the shift value (key) to the zero-based index
             * `% 26`                   -- Ensures the result wraps around within the alphabet
             * `+ base`                 -- Converts the zero-based index back to the ASCII value of the character
             */
        } else {
            // Non-alphabetic characters remain unchanged
        }
    }
    return plaintext;
}

/**
 * Decrypts the given ciphertext using the Caesar cipher.
 *
 * Each alphabetic character in the input string is shifted back by the specified key value.
 * Non-alphabetic characters remain unchanged.
 *
 * \param ciphertext Pointer to the input string to decrypt. The string is modified in place.
 * \param key       The shift value for the cipher (can be positive or negative).
 * \return          Pointer to the decrypted string (same as ciphertext).
 */
char *caesar_decrypt(char *ciphertext, const int key) {
    // Decrypting is just encrypting with the negative key
    return caesar_encrypt(ciphertext, -key);
}

/**
 * Performs brute force decryption on the given ciphertext using the Caesar cipher.
 *
 * Tries all possible shift values (0-25) and displays each result.
 * This helps identify the correct decryption when the key is unknown.
 *
 * \param ciphertext Pointer to the input string to decrypt.
 */
void caesar_brute_force(const char *ciphertext) {
    char temp[strlen(ciphertext) + 1]; // Temporary buffer for each decryption attempt (+1 for null terminator)

    printf("Brute force decryption results:\n");
    printf("==============================\n");

    for (int key = 0; key < 26; key++) {
        // Copy ciphertext to temporary buffer
        strcpy(temp, ciphertext);

        // Decrypt with current key
        caesar_decrypt(temp, key);

        printf("Key %2d: %s\n", key, temp);
    }
}
