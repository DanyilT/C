//
// Created by Dany on 07/15/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Monoalphabetic Substitution Cipher Implementation in C
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Buffer for input (plaintext / ciphertext), can hold up to 255 characters (plus null terminator)
#define MAX_INPUT_LENGTH 256
#define ALPHABET_SIZE 26

char *monoalphabetic_encrypt(char *plaintext, const char *key);
char *monoalphabetic_decrypt(char *ciphertext, const char *key);
int validate_key(const char *key);
void generate_random_key(char *key);

int main(int argc, char **argv) {
    char text[MAX_INPUT_LENGTH];
    char key[ALPHABET_SIZE + 1]; // +1 for null terminator
    int operation = 0;

    printf("Monoalphabetic Substitution Cipher\n");
    printf("==================================\n");
    printf("This program can encrypt or decrypt text using a Monoalphabetic Substitution cipher.\n");
    printf("The key must be a 26-character string with each letter of the alphabet used exactly once.\n\n");

    // Check if key is provided as command line arguments
    if (argc == 2 || argc == 3) {
        if (strcasecmp(argv[1], "rand") == 0 || strcasecmp(argv[1], "random") == 0 || strcasecmp(argv[1], "generate") == 0) {
            generate_random_key(key);
            printf("Generated random key: %s\n", key);
        } else {
            strncpy(key, argv[1], ALPHABET_SIZE);
            key[ALPHABET_SIZE] = '\0'; // Ensure null termination
            if (validate_key(key) == 0) {
                fprintf(stderr, "Invalid key. Key must contain exactly 26 unique letters.\n");
                return 1;
            }
            printf("Using provided key: %s\n", key);
        }
    } else {
        fprintf(stderr, "Usage: %s <key (or rand)> [operation (e/d)]\n", argv[0]);

        // Ask user for key or generate a random key
        printf("Enter substitution key (26 unique letters) or press Enter to generate a random key: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        if (strlen(key) == 0) {
            // If no key is provided, generate a random key
            generate_random_key(key);
            printf("Generated random key: %s\n", key);
        } else {
            // Validate the provided key
            if (!validate_key(key)) {
                fprintf(stderr, "Invalid key. Key must contain exactly 26 unique letters.\n");
                return 1;
            }
        }
    }

    // Check if operation (encryption / decryption) type is provided as command line arguments
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
        monoalphabetic_encrypt(text, key);
        printf("Encrypted text: %s\n", text);
    } else {
        monoalphabetic_decrypt(text, key);
        printf("Decrypted text: %s\n", text);
    }

    return 0;
}

/**
 * Validates that the key contains exactly 26 unique letters.
 *
 * \param key   Pointer to the key string to validate.
 * \return      1 if the key is valid, 0 otherwise.
 */
int validate_key(const char *key) {
    if (strlen(key) != ALPHABET_SIZE) {
        return 0;
    }

    int letter_count[ALPHABET_SIZE] = {0};

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (!isalpha(key[i])) {
            return 0;
        }

        int index = tolower(key[i]) - 'a';
        letter_count[index]++;

        if (letter_count[index] > 1) {
            return 0; // Duplicate letter found
        }
    }

    return 1; // Valid key
}

/**
 * Generates a random monoalphabetic substitution key by shuffling the alphabet.
 *
 * The key will contain 26 unique letters (a-z) in a random order.
 * This function uses the Fisher-Yates shuffle algorithm to ensure randomness.
 *
 * \param key   Pointer to a character array where the generated key will be stored.
 * \return      void
 */
void generate_random_key(char *key) {
    srand(time(NULL)); // Seed random number generator

    // Initialize key with normal alphabet
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = 'a' + i;
    }
    key[ALPHABET_SIZE] = '\0';

    // Shuffle the alphabet using Fisher-Yates algorithm
    for (int i = ALPHABET_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap key[i] and key[j]
        char temp = key[i];
        key[i] = key[j];
        key[j] = temp;
    }
}

/**
 * Encrypts the given plaintext using Monoalphabetic Substitution cipher.
 *
 * Each alphabetic character in the input string is replaced by the corresponding character in the key.
 * Non-alphabetic characters remain unchanged.
 *
 * \param plaintext Pointer to the input string to encrypt. The string is modified in place.
 * \param key       The substitution key (26 unique letters).
 * \return          Pointer to the encrypted string (same as plaintext).
 */
char *monoalphabetic_encrypt(char *plaintext, const char *key) {
    for (int i = 0, len = strlen(plaintext); i < len; i++) {
        if (isalpha(plaintext[i])) {
            int index = tolower(plaintext[i]) - 'a';
            plaintext[i] = islower(plaintext[i]) ? tolower(key[index]) : toupper(key[index]);
        }
    }
    return plaintext;
}

/**
 * Decrypts the given ciphertext using Monoalphabetic Substitution cipher.
 *
 * Each alphabetic character in the input string is replaced by the corresponding character in the key.
 * Non-alphabetic characters remain unchanged.
 *
 * \param ciphertext Pointer to the input string to decrypt. The string is modified in place.
 * \param key       The substitution key (26 unique letters).
 * \return          Pointer to the decrypted string (same as ciphertext).
 */
char *monoalphabetic_decrypt(char *ciphertext, const char *key) {
    for (int i = 0, len = strlen(ciphertext); i < len; i++) {
        if (isalpha(ciphertext[i])) {
            for (int j = 0, key_len = strlen(key); j < key_len; j++) {
                if (tolower(ciphertext[i]) == tolower(key[j])) {
                    ciphertext[i] = islower(ciphertext[i]) ? ('a' + j) : ('A' + j);
                    break;
                }
            }
        }
    }
    return ciphertext;
}




/*

    # Compile
    gcc -o substitution_cipher substitution_cipher.c

    # Interactive mode
    ./substitution_cipher

    # Command line mode (example key: "zyxwvutsrqponmlkjihgfedcba" - reverse alphabet)
    ./substitution_cipher zyxwvutsrqponmlkjihgfedcba e

*/