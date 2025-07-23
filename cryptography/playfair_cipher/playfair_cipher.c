//
// Created by Dany on 07/22/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Playfair Cipher Implementation in C
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Buffer for input (plaintext / ciphertext), can hold up to 255 characters (plus null terminator)
#define MAX_INPUT_LENGTH 256
#define MAX_KEY_LENGTH 100 // Maximum length for the key is 99 characters (plus null terminator)
#define GRID_SIZE 5 // 5x5 grid for Playfair cipher

char *playfair_encrypt(char *plaintext, const char grid[GRID_SIZE][GRID_SIZE]);
char * playfair_decrypt(char *ciphertext, const char grid[GRID_SIZE][GRID_SIZE]);
void preprocess_text(const char *input, char *output);
void find_position(const char grid[GRID_SIZE][GRID_SIZE], const char c, int *row, int *col);
int validate_key(const char *key);
void generate_random_key(char *key);
void create_key_grid(const char *key, char grid[GRID_SIZE][GRID_SIZE]);
void print_key_grid(const char grid[GRID_SIZE][GRID_SIZE]);

int main(int argc, char **argv) {
    char key[MAX_KEY_LENGTH];
    char grid[GRID_SIZE][GRID_SIZE];
    char text[MAX_INPUT_LENGTH];
    char processed_text[MAX_INPUT_LENGTH * 2]; // May expand during preprocessing
    int operation = 0;

    printf("Playfair Cipher\n");
    printf("===============\n");
    printf("This program can encrypt or decrypt text using the Playfair cipher.\n");
    printf("Uses a 5x5 grid with a keyword (I and J share the same position).\n\n");

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
        create_key_grid(key, grid);
        printf("Key grid:\n");
        print_key_grid(grid);
    } else {
        fprintf(stderr, "Usage: %s <key (or rand)> <operation (e/d)>\n", argv[0]);

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
            printf("Using provided key: %s\n", key);
        }
        create_key_grid(key, grid);
        printf("Key grid:\n");
        print_key_grid(grid);
    }

    // Check if operation (encryption / decryption) is provided as command line argument
    if (argc == 3) {
        if (strcasecmp(argv[2], "e") == 0 || strcasecmp(argv[2], "encrypt") == 0 || strcasecmp(argv[2], "encryption") == 0) {
            operation = 1; // Encrypt
        } else if (strcasecmp(argv[2], "d") == 0 || strcasecmp(argv[2], "decrypt") == 0 || strcasecmp(argv[2], "decryption") == 0) {
            operation = 2; // Decrypt
        } else {
            fprintf(stderr, "Invalid operation. Use 'e'/'encrypt' or 'd'/'decrypt'.\n");
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

    // Preprocess text (remove non-alphabetic, handle duplicates, ensure even length)
    preprocess_text(text, processed_text);
    printf("Processed text: %s\n", processed_text);

    if (operation == 1) {
        // Encryption
        playfair_encrypt(processed_text, grid);
        printf("Encrypted text: %s\n", processed_text);
    } else {
        // Decryption
        playfair_decrypt(processed_text, grid);
        printf("Decrypted text: %s\n", processed_text);
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
        return 0; // Key must be non-empty and within length limits
    }

    for (int i = 0; key[i] != '\0'; i++) {
        if (!isalpha(key[i])) {
            return 0;
        }
    }
    return 1;
}

/**
 * Generates a random Playfair key.
 *
 * Creates a random string of 8-15 characters from the alphabet.
 *
 * \param key   Pointer to a character array where the generated key will be stored (must be pre-allocated).
 * \return      void
 */
void generate_random_key(char *key) {
    srand(time(NULL)); // Seed random number generator

    int key_length = 8 + (rand() % 8); // Random key length between 8 and 15

    for (int i = 0; i < key_length; i++) {
        key[i] = 'A' + (rand() % 26); // Random letter A-Z
    }
    key[key_length] = '\0';
}

/**
 * Creates a 5x5 Playfair cipher key grid from the given keyword.
 *
 * Removes duplicate letters and fills remaining positions with unused alphabet letters.
 * I and J share the same position in the grid.
 *
 * \param key   Pointer to the keyword string.
 * \param grid  Pointer to store the generated key grid.
 * \return      void
 */
void create_key_grid(const char *key, char grid[GRID_SIZE][GRID_SIZE]) {
    int used[26] = {0}; // Track used letters
    int pos = 0;

    // Fill grid with key letters (removing duplicates)
    for (int i = 0; key[i] != '\0' && pos < 25; i++) {
        char c = toupper(key[i]);
        if (isalpha(c)) {
            // Treat J as I
            if (c == 'J') c = 'I';

            int index = c - 'A';
            if (!used[index]) {
                grid[pos / GRID_SIZE][pos % GRID_SIZE] = c;
                used[index] = 1;
                pos++;
            }
        }
    }

    // Fill remaining positions with unused letters
    for (int i = 0; i < 26 && pos < 25; i++) {
        if (!used[i] && i != ('J' - 'A')) { // Skip J as it's represented by I
            grid[pos / GRID_SIZE][pos % GRID_SIZE] = 'A' + i;
            pos++;
        }
    }
}

/**
 * Prints the 5x5 Playfair key grid.
 *
 * \param grid  The Playfair key grid to print.
 * \return      void
 */
void print_key_grid(const char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Finds the position of a character in the Playfair key grid.
 *
 * \param grid  The Playfair key grid.
 * \param c     The character to find.
 * \param row   Pointer to store the row position.
 * \param col   Pointer to store the column position.
 * \return      void
 */
void find_position(const char grid[GRID_SIZE][GRID_SIZE], const char c, int *row, int *col) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

/**
 * Preprocesses text for Playfair cipher:
 * - Converts to uppercase
 * - Removes non-alphabetic characters
 * - Converts J to I
 * - Inserts X between duplicate letters in pairs
 * - Adds X at end if odd length
 *
 * \param input Input text to preprocess. The string is modified in place. (Rewritten to output)
 * \return      void
 */
void preprocess_text(const char *input, char *output) {
    int out_pos = 0;

    // First pass: clean and convert
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            char c = toupper(input[i]);
            if (c == 'J') c = 'I'; // Convert J to I
            output[out_pos++] = c;
        }
    }

    // Second pass: handle duplicate pairs
    char temp[MAX_INPUT_LENGTH * 2];
    int temp_pos = 0;

    for (int i = 0; i < out_pos; i++) {
        temp[temp_pos++] = output[i];

        // Check if next character is the same and we're at an even position
        if (i + 1 < out_pos && output[i] == output[i + 1] && temp_pos % 2 == 0) {
            temp[temp_pos++] = 'X'; // Insert X between duplicates
        }
    }

    // Ensure even length
    if (temp_pos % 2 != 0) {
        temp[temp_pos++] = 'X';
    }

    temp[temp_pos] = '\0';
    strcpy(output, temp);
}

/**
 * Encrypts the given plaintext using the Playfair cipher.
 *
 * Each pair of characters is processed according to the Playfair rules:
 * - If both characters are in the same row, replace them with the characters to their right.
 * - If both characters are in the same column, replace them with the characters below.
 * - If they form a rectangle, swap their columns.
 * Non-alphabetic characters are ignored, and J is treated as I.
 *
 * \param plaintext Pointer to the input string to encrypt. The string is modified in place.
 * \param grid      The Playfair key grid.
 * \return          Pointer to the encrypted string (same as ciphertext).
 */
char *playfair_encrypt(char *plaintext, const char grid[GRID_SIZE][GRID_SIZE]) {
    int out_pos = 0;

    for (int i = 0, len = strlen(plaintext); i < len; i += 2) {
        char c1 = plaintext[i], c2 = plaintext[i + 1];

        int row1, col1, row2, col2;
        find_position(grid, c1, &row1, &col1);
        find_position(grid, c2, &row2, &col2);

        if (row1 == row2) {
            // Same row: move right
            plaintext[out_pos++] = grid[row1][(col1 + 1) % GRID_SIZE];
            plaintext[out_pos++] = grid[row2][(col2 + 1) % GRID_SIZE];
        } else if (col1 == col2) {
            // Same column: move down
            plaintext[out_pos++] = grid[(row1 + 1) % GRID_SIZE][col1];
            plaintext[out_pos++] = grid[(row2 + 1) % GRID_SIZE][col2];
        } else {
            // Rectangle: swap columns
            plaintext[out_pos++] = grid[row1][col2];
            plaintext[out_pos++] = grid[row2][col1];
        }
    }

    plaintext[out_pos] = '\0';
    return plaintext;
}

/**
 * Decrypts the given ciphertext using the Playfair cipher.
 *
 * Each pair of characters is processed according to the Playfair rules:
 * - If both characters are in the same row, replace them with the characters to their left.
 * - If both characters are in the same column, replace them with the characters above.
 * - If they form a rectangle, swap their columns.
 * Non-alphabetic characters are ignored, and J is treated as I.
 *
 * \param ciphertext Pointer to the input string to decrypt. The string is modified in place.
 * \param grid      The Playfair key grid.
 * \return          Pointer to the decrypted string (same as ciphertext).
 */
char *playfair_decrypt(char *ciphertext, const char grid[GRID_SIZE][GRID_SIZE]) {
    int out_pos = 0;

    for (int i = 0, len = strlen(ciphertext); i < len; i += 2) {
        char c1 = ciphertext[i], c2 = ciphertext[i + 1];

        int row1, col1, row2, col2;
        find_position(grid, c1, &row1, &col1);
        find_position(grid, c2, &row2, &col2);

        if (row1 == row2) {
            // Same row: move left
            ciphertext[out_pos++] = grid[row1][(col1 + GRID_SIZE - 1) % GRID_SIZE];
            ciphertext[out_pos++] = grid[row2][(col2 + GRID_SIZE - 1) % GRID_SIZE];
        } else if (col1 == col2) {
            // Same column: move up
            ciphertext[out_pos++] = grid[(row1 + GRID_SIZE - 1) % GRID_SIZE][col1];
            ciphertext[out_pos++] = grid[(row2 + GRID_SIZE - 1) % GRID_SIZE][col2];
        } else {
            // Rectangle: swap columns
            ciphertext[out_pos++] = grid[row1][col2];
            ciphertext[out_pos++] = grid[row2][col1];
        }
    }

    ciphertext[out_pos] = '\0';
    return ciphertext;
}
