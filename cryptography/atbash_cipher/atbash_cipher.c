//
// Created by Dany on 07/18/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Atbash Cipher Implementation in C
//

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Buffer for input (plaintext / ciphertext), can hold up to 255 characters (plus null terminator)
#define MAX_INPUT_LENGTH 256

char *atbash_cipher(char *text);

int main(int argc, char **argv) {
    char text[MAX_INPUT_LENGTH];
    int operation = 0;

    printf("Atbash Cipher\n");
    printf("=============\n");
    printf("This program can encrypt or decrypt text using the Atbash cipher.\n");
    printf("The Atbash cipher is a simple substitution cipher where A↔Z, B↔Y, C↔X, etc.\n");
    printf("Note: Atbash encryption and decryption are the same operation.\n\n");

    // Check if text is provided as command line argument
    if (argc == 2) {
        strncpy(text, argv[1], MAX_INPUT_LENGTH - 1);
        text[MAX_INPUT_LENGTH - 1] = '\0'; // Ensure null termination
    } else {
        // Prompt the user for text input
        printf("Enter text (plaintext / ciphertext): ");
        fgets(text, sizeof(text), stdin); // Read text input from the user
        text[strcspn(text, "\n")] = '\0'; // Remove newline character
    }

    // Apply Atbash cipher
    atbash_cipher(text);
    printf("Atbash result (ciphertext / plaintext): %s\n", text);

    return 0;
}

/**
 * Encrypts/Decrypts the given text using the Atbash cipher.
 *
 * Each alphabetic character is replaced with its mirror character in the alphabet:
 * A↔Z, B↔Y, C↔X, D↔W, E↔V, F↔U, G↔T, H↔S, I↔R, J↔Q, K↔P, L↔O, M↔N
 * Non-alphabetic characters remain unchanged.
 *
 * The same function is used for both encryption and decryption.
 *
 * \param text  Pointer to the input string to transform. The string is modified in place.
 * \return      Pointer to the transformed (encrypted/decrypted) string (same as text).
 */
char *atbash_cipher(char *text) {
    for (int i = 0, len = strlen(text); i < len; i++) {
        if (isalpha(text[i])) {
            if (islower(text[i]))
                text[i] = 'z' - (text[i] - 'a'); // For lowercase: 'a' becomes 'z', 'b' becomes 'y', etc.
            else
                text[i] = 'Z' - (text[i] - 'A'); // For uppercase: 'A' becomes 'Z', 'B' becomes 'Y', etc.
        }
        // Non-alphabetic characters remain unchanged
    }
    return text;
}
