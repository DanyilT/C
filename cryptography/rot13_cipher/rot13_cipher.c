//
// Created by Dany on 07/15/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// ROT13 Cipher Implementation in C (using Caesar cipher)
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Buffer for input (plaintext / ciphertext), can hold up to 255 characters (plus null terminator)
#define MAX_INPUT_LENGTH 256
#define ROT13_KEY 13

char *caesar_encrypt(char *plaintext, int key);

int main(int argc, char **argv) {
    char text[MAX_INPUT_LENGTH];

    printf("ROT13 Cipher\n");
    printf("============\n");
    printf("Note: ROT13 encryption and decryption are the same operation.\n\n");

    // Check if text is provided as command line argument
    if (argc == 2) {
        strncpy(text, argv[1], MAX_INPUT_LENGTH - 1);
        text[MAX_INPUT_LENGTH - 1] = '\0'; // Ensure null termination
    } else {
        // Prompt the user for text input
        printf("Enter text: ");
        fgets(text, sizeof(text), stdin); // Read text input from the user
        text[strcspn(text, "\n")] = '\0'; // Remove newline character
    }

    // Apply ROT13 (which is Caesar cipher with key 13)
    caesar_encrypt(text, ROT13_KEY);
    printf("ROT13 result: %s\n", text);

    return 0;
}

/**
 * Encrypts/Decrypts the given text using the Caesar cipher.
 * (Reused from caesar_cipher.c)
 */
char *caesar_encrypt(char *plaintext, const int key) {
    for (int i = 0, len = strlen(plaintext); i < len; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            int shift = (key % 26 + 26) % 26;
            plaintext[i] = (plaintext[i] - base + shift) % 26 + base;
        }
    }
    return plaintext;
}
