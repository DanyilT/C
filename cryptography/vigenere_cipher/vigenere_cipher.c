//
// Created by Dany on 07/16/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Vigenère Cipher Implementation in C
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Buffer for input (plaintext / ciphertext), can hold up to 255 characters (plus null terminator)
#define MAX_INPUT_LENGTH 256
#define MAX_KEY_LENGTH 100 // Maximum length for the key is 99 characters (plus null terminator)

char *vigenere_encrypt(char *plaintext, const char *key);
char *vigenere_decrypt(char *ciphertext, const char *key);
int validate_key(const char *key);
void generate_random_key(char *key);

int main(int argc, char **argv) {
    char text[MAX_INPUT_LENGTH];
    char key[MAX_KEY_LENGTH];
    int operation = 0;

    printf("Vigenère Cipher\n");
    printf("===============\n");
    printf("This program can encrypt or decrypt text using the Vigenère cipher.\n");
    printf("The key must contain only alphabetic characters.\n\n");

    // Check if key is provided as command line arguments
    if (argc == 2 || argc == 3) {
        if (strcasecmp(argv[1], "rand") == 0 || strcasecmp(argv[1], "random") == 0 || strcasecmp(argv[1], "generate") == 0) {
            generate_random_key(key);
            printf("Generated random key: %s\n", key);
        } else {
            strncpy(key, argv[1], MAX_KEY_LENGTH - 1);
            key[MAX_KEY_LENGTH - 1] = '\0'; // Ensure null termination
            if (!validate_key(key)) {
                fprintf(stderr, "Invalid key. Key must contain only alphabetic characters. (max length %d)\n", MAX_KEY_LENGTH - 1);
                return 1;
            }
            printf("Using provided key: %s\n", key);
        }
    } else {
        fprintf(stderr, "Usage: %s <key (or rand)> [operation (e/d)]\n", argv[0]);

        // Ask user for key or generate a random key
        printf("Enter key (alphabetic characters only) or press Enter to generate a random key: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0'; // Remove newline character

        if (strlen(key) == 0) {
            // If no key is provided, generate a random key
            generate_random_key(key);
            printf("Generated random key: %s\n", key);
        } else {
            // Validate the provided key
            if (!validate_key(key)) {
                fprintf(stderr, "Invalid key. Key must contain only alphabetic characters.\n");
                return 1;
            }
        }
    }

    // Check if operation (encryption / decryption) is provided as command line argument
    if (argc == 3) {
        if (strcasecmp(argv[2], "e") == 0 || strcasecmp(argv[2], "encrypt") == 0 || strcasecmp(argv[2], "encryption") == 0) {
            operation = 1; // Encrypt
        } else if (strcasecmp(argv[2], "d") == 0 || strcasecmp(argv[2], "decrypt") == 0 || strcasecmp(argv[2], "decryption") == 0) {
            operation = 2; // Decrypt
        } else {
            fprintf(stderr, "Invalid operation. Use 'e' for encrypt or 'd' for decrypt.\n");
            return 1;
        }
    } else {
        // Prompt the user to choose the operation (encryption or decryption)
        printf("Choose operation:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        if (scanf("%d", &operation) != 1 || (operation < 1 || operation > 2)) {
            fprintf(stderr, "Invalid choice. Please enter 1 or 2.\n");
            return 1;
        }
        while (getchar() != '\n'); // Clear input buffer
    }

    printf("You chose to %s.\n", operation == 1 ? "encrypt" : "decrypt");
    printf("--------------------\n");

    // Get text input
    printf("Enter %s: ", operation == 1 ? "plaintext" : "ciphertext");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    if (operation == 1) {
        vigenere_encrypt(text, key);
        printf("Encrypted text: %s\n", text);
    } else {
        vigenere_decrypt(text, key);
        printf("Decrypted text: %s\n", text);
    }

    return 0;
}

/**
 * Validates that the key contains only alphabetic characters.
 *
 * \param key   Pointer to the key string to validate.
 * \return      1 if the key is valid, 0 otherwise.
 */
int validate_key(const char *key) {
    if (strlen(key) == 0 || strlen(key) > MAX_KEY_LENGTH - 1) {
        return 0;
    }

    for (int i = 0, key_len = strlen(key); i < key_len; i++) {
        if (!isalpha(key[i])) {
            return 0;
        }
    }
    return 1;
}

/**
 * Generates a random Vigenère key with random length and random alphabetic characters.
 *
 * \param key   Pointer to a character array where the generated key will be stored (must be pre-allocated).
 * \return      void
 */
void generate_random_key(char *key) {
    srand(time(NULL)); // Seed random number generator

    // Generate random length between 3 and MAX_KEY_LENGTH-1
    int key_length = (rand() % (MAX_KEY_LENGTH - 3)) + 3;

    for (int i = 0; i < key_length; i++) {
        key[i] = 'a' + (rand() % 26); // Random lowercase letter
    }
    key[key_length] = '\0';
}

/**
 * Encrypts the given plaintext using the Vigenère cipher.
 *
 * Each alphabetic character is shifted by the corresponding key character value.
 * The key repeats cyclically throughout the text.
 * Non-alphabetic characters remain unchanged.
 *
 * \param plaintext Pointer to the input string to encrypt. The string is modified in place.
 * \param key       The keyword for encryption.
 * \return          Pointer to the encrypted string (same as plaintext).
 */
char *vigenere_encrypt(char *plaintext, const char *key) {
    int key_index = 0;

    for (int i = 0, len = strlen(plaintext); i < len; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            int shift = tolower(key[key_index % strlen(key)]) - 'a'; // Get shift from key character, wrap around if necessary
            plaintext[i] = (plaintext[i] - base + shift) % 26 + base;
            key_index++;
        }
    }
    return plaintext;
}

/**
 * Decrypts the given ciphertext using the Vigenère cipher.
 *
 * Each alphabetic character is shifted back by the corresponding key character value.
 * The key repeats cyclically throughout the text.
 * Non-alphabetic characters remain unchanged.
 *
 * \param ciphertext Pointer to the input string to decrypt. The string is modified in place.
 * \param key       The keyword for decryption.
 * \return          Pointer to the decrypted string (same as ciphertext).
 */
char *vigenere_decrypt(char *ciphertext, const char *key) {
    // Create and inverse key for decryption by subtracting each character in the key from 'z'.
    char inverse_key[strlen(key) + 1]; // Create an array to hold the inverse key (+1 for null terminator)
    inverse_key[strlen(key)] = '\0'; // Ensure null termination

    for (int i = 0, key_len = strlen(key); i < key_len; i++) {
        inverse_key[i] = 'a' + (26 - (tolower(key[i]) - 'a')) % 26; // Calculate inverse key character
    }

    // Decrypting is just encrypting with the inverse key
    return vigenere_encrypt(ciphertext, inverse_key);
}
