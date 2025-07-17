//
// Created by Dany on 07/16/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// XOR Cipher Implementation in C
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Buffer for input (plaintext / ciphertext), can hold up to 255 characters (plus null terminator)
#define MAX_INPUT_LENGTH 256
#define MAX_KEY_LENGTH 100 // Maximum length for the key is 99 characters (plus null terminator)

typedef enum {
    KEY_TYPE_BYTE,
    KEY_TYPE_CHAR,
    KEY_TYPE_STRING,
    KEY_TYPE_BYTE_SEQUENCE
} key_type_t;

int xor_encrypt(unsigned char *plaintext, const void *key, int key_length);
int xor_decrypt(unsigned char *ciphertext, const void *key, int key_length);
void xor_brute_force(const char *ciphertext);
int convert_to_byte_key(const char *input);
int parse_byte_sequence(const char *input, unsigned char *bytes);
int validate_key(const void *key, const key_type_t key_type, const int key_length);
void generate_random_key(void *key, const key_type_t key_type, int *key_length);
void print_byte_sequence(const unsigned char *bytes, const int length);

int main(int argc, char **argv) {
    char text[MAX_INPUT_LENGTH];
    int key_length;
    unsigned char byte_key;
    char char_key;
    char string_key[MAX_KEY_LENGTH];
    unsigned char byte_sequence[MAX_KEY_LENGTH];
    key_type_t key_type = KEY_TYPE_BYTE; // Default key type

    printf("XOR Cipher\n");
    printf("==========\n");
    printf("This program can encrypt or decrypt text using the XOR cipher.\n");
    printf("Supports byte, character, string, or byte sequence keys.\n\n");

    // Check if key (argv[1]) and type (argv[2]/argv[3]) is provided as command line arguments
    if (argc == 2 || argc == 3 || argc == 4) {
        if (strcasecmp(argv[1], "rand") == 0 || strcasecmp(argv[1], "random") == 0 || strcasecmp(argv[1], "generate") == 0) {
            // Generate a random key based on the type or use default key_type
            for (int i = 2; i < argc; i++) {
                key_type = (strcasecmp(argv[i], "--byte") == 0 || strcasecmp(argv[i], "-b") == 0) ? KEY_TYPE_BYTE :
                           (strcasecmp(argv[i], "--char") == 0 || strcasecmp(argv[i], "-c") == 0) ? KEY_TYPE_CHAR :
                           (strcasecmp(argv[i], "--string") == 0 || strcasecmp(argv[i], "-s") == 0) ? KEY_TYPE_STRING :
                           (strcasecmp(argv[i], "--byte_sequence") == 0 || strcasecmp(argv[i], "-bs") == 0) ? KEY_TYPE_BYTE_SEQUENCE : key_type;
            }

            generate_random_key(key_type == KEY_TYPE_BYTE ? (void*) &byte_key :
                                key_type == KEY_TYPE_CHAR ? (void*) &char_key :
                                key_type == KEY_TYPE_STRING ? (void*) string_key :
                                key_type == KEY_TYPE_BYTE_SEQUENCE ? (void*) byte_sequence : NULL,
                                key_type, &key_length);

            switch (key_type) {
                case KEY_TYPE_BYTE:
                    printf("Generated random byte key: %u (0x%02X)\n", byte_key, byte_key);
                    break;
                case KEY_TYPE_CHAR:
                    printf("Generated random char key: '%c' (%d)\n", char_key, char_key);
                    break;
                case KEY_TYPE_STRING:
                    printf("Generated random string key: %s\n", string_key);
                    break;
                case KEY_TYPE_BYTE_SEQUENCE:
                    printf("Generated random byte sequence key: ");
                    print_byte_sequence(byte_sequence, key_length);
                    break;
            }
        } else {
            // If a key is provided
            int is_key_type_flag = 0;

            // Check if key type is provided as command line arguments
            for (int i = 2; i < argc; i++) {
                is_key_type_flag = strcasecmp(argv[i], "--byte") == 0 || strcasecmp(argv[i], "-b") == 0 || strcasecmp(argv[i], "--char") == 0 || strcasecmp(argv[i], "-c") == 0 || strcasecmp(argv[i], "--string") == 0 || strcasecmp(argv[i], "-s") == 0 || strcasecmp(argv[i], "--byte_sequence") == 0 || strcasecmp(argv[i], "-bs") == 0;
                if (is_key_type_flag) break;
            }

            if (is_key_type_flag) {
                for (int i = 2; i < argc; i++) {
                    key_type = (strcasecmp(argv[i], "--byte") == 0 || strcasecmp(argv[i], "-b") == 0) ? KEY_TYPE_BYTE :
                               (strcasecmp(argv[i], "--char") == 0 || strcasecmp(argv[i], "-c") == 0) ? KEY_TYPE_CHAR :
                               (strcasecmp(argv[i], "--string") == 0 || strcasecmp(argv[i], "-s") == 0) ? KEY_TYPE_STRING :
                               (strcasecmp(argv[i], "--byte_sequence") == 0 || strcasecmp(argv[i], "-bs") == 0) ? KEY_TYPE_BYTE_SEQUENCE : key_type;
                }

                switch (key_type) {
                    case KEY_TYPE_BYTE:
                        if (convert_to_byte_key(argv[1]) == -1) {
                            fprintf(stderr, "Invalid byte key format. Must be a number between 0 and 255 or binary (0b...) format or hex (0x...) format.\n");
                            return 1;
                        }
                        byte_key = convert_to_byte_key(argv[1]);
                        key_length = 1; // Byte key length is always 1
                        printf("Using byte key: %u (0x%02X)\n", byte_key, byte_key);
                        break;
                    case KEY_TYPE_CHAR:
                        char_key = argv[1][0];
                        key_length = 1; // Char key length is always 1
                        printf("Using char key: '%c' (%d)\n", char_key, char_key);
                        break;
                    case KEY_TYPE_STRING:
                        if (strlen(argv[1]) < MAX_KEY_LENGTH) {
                            strncpy(string_key, argv[1], MAX_KEY_LENGTH - 1);
                            string_key[MAX_KEY_LENGTH - 1] = '\0';
                            key_length = strlen(string_key); // String key length is the length of the string
                            printf("Using string key: %s\n", string_key);
                        } else {
                            fprintf(stderr, "String key is too long. Maximum length is %d characters.\n", MAX_KEY_LENGTH - 1);
                            return 1;
                        }
                        break;
                    case KEY_TYPE_BYTE_SEQUENCE:
                        key_length = parse_byte_sequence(argv[1], byte_sequence);
                        if (key_length != -1) {
                            // Successfully parsed byte sequence
                            printf("Using byte sequence key: ");
                            print_byte_sequence(byte_sequence, key_length);
                        } else {
                            fprintf(stderr, "Invalid byte sequence format.\n");
                            return 1;
                        }
                        break;
                }
            }

            // Automatically determine its type based on the input if no type is specified
            else {
                if (convert_to_byte_key(argv[1]) != -1) {
                    // If the key is a single byte (0-255)
                    byte_key = convert_to_byte_key(argv[1]);
                    key_type = KEY_TYPE_BYTE;
                    key_length = 1; // Byte key length is always 1
                    printf("Using byte key: %u (0x%02X)\n", byte_key, byte_key);
                } else if (strlen(argv[1]) == 1) {
                    // If the key is a single character
                    char_key = argv[1][0];
                    key_type = KEY_TYPE_CHAR;
                    key_length = 1; // Char key length is always 1
                    printf("Using char key: '%c' (%d)\n", char_key, char_key);
                } else {
                    // If the key is a string or byte sequence
                    key_length = parse_byte_sequence(argv[1], byte_sequence);
                    if (key_length != -1) {
                        // Successfully parsed byte sequence
                        key_type = KEY_TYPE_BYTE_SEQUENCE;
                        printf("Using byte sequence key: ");
                        print_byte_sequence(byte_sequence, key_length);
                    } else if (strlen(argv[1]) < MAX_KEY_LENGTH) {
                        // Treat as string key
                        strncpy(string_key, argv[1], MAX_KEY_LENGTH - 1);
                        string_key[MAX_KEY_LENGTH - 1] = '\0';
                        key_type = KEY_TYPE_STRING;
                        key_length = strlen(string_key); // String key length is the length of the string
                        printf("Using string key: %s\n", string_key);
                    } else {
                        fprintf(stderr, "Key is too long. Maximum length is %d characters.\n", MAX_KEY_LENGTH - 1);
                        return 1;
                    }
                }
            }
            validate_key(key_type == KEY_TYPE_BYTE ? (void*) &byte_key : key_type == KEY_TYPE_CHAR ? (void*) &char_key : key_type == KEY_TYPE_STRING ? (void*) string_key : key_type == KEY_TYPE_BYTE_SEQUENCE ? (void*) byte_sequence : NULL, key_type, key_length);
        }

    // Interactive mode
    } else {
        fprintf(stderr, "Usage: %s <key (or rand)> [--byte/-b | --char/-c | --string/-s | --byte_sequence/-bs] <<operation (e/d/bf)>\n", argv[0]);

        printf("Note: Type is gonna be determined automatically based on the input, or you can specify it explicitly: add a flag to the end of input like --byte/-b, --char/-c, --string/-s, or --byte_sequence/-bs (default random key type is byte).\n");
        printf("Enter key or press Enter to generate a random key: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0'; // Remove newline character

        // Determine key type based on input

        // Check if type flag is at the end of input (e.g. "key --string")
        char *type_flag = NULL;
        if (strstr(text, "--byte_sequence")) type_flag = "--byte_sequence";
        else if (strstr(text, "-bs")) type_flag = "-bs";
        else if (strstr(text, "--byte")) type_flag = "--byte";
        else if (strstr(text, "-b")) type_flag = "-b";
        else if (strstr(text, "--char")) type_flag = "--char";
        else if (strstr(text, "-c")) type_flag = "-c";
        else if (strstr(text, "--string")) type_flag = "--string";
        else if (strstr(text, "-s")) type_flag = "-s";

        if (type_flag) {
            // Set key_type
            key_type = (strcmp(type_flag, "--byte") == 0 || strcmp(type_flag, "-b") == 0) ? KEY_TYPE_BYTE :
                       (strcmp(type_flag, "--char") == 0 || strcmp(type_flag, "-c") == 0) ? KEY_TYPE_CHAR :
                       (strcmp(type_flag, "--string") == 0 || strcmp(type_flag, "-s") == 0) ? KEY_TYPE_STRING :
                       (strcmp(type_flag, "--byte_sequence") == 0 || strcmp(type_flag, "-bs") == 0) ? KEY_TYPE_BYTE_SEQUENCE : key_type;

            if (strlen(text) == strlen(type_flag)) {
                // Only type provided (for generate random key)
                text[0] = '\0'; // Clear text
            } else {
                // Type and key provided, remove type from text
                char *pos = strstr(text, type_flag);
                if (pos) {
                    *pos = '\0';
                    // Remove trailing spaces
                    size_t len = strlen(text);
                    while (len > 0 && isspace((unsigned char)text[len - 1])) {
                        text[len - 1] = '\0';
                        len--;
                    }
                }
            }
        }

        // If no key is provided, generate a random key
        if (strlen(text) == 0) {
            // If no key is provided, generate a random key
            generate_random_key(key_type == KEY_TYPE_BYTE ? (void*) &byte_key :
                                key_type == KEY_TYPE_CHAR ? (void*) &char_key :
                                key_type == KEY_TYPE_STRING ? (void*) string_key :
                                key_type == KEY_TYPE_BYTE_SEQUENCE ? (void*) byte_sequence : NULL,
                                key_type, &key_length);

            switch (key_type) {
                case KEY_TYPE_BYTE:
                    printf("Generated random byte key: %u (0x%02X)\n", byte_key, byte_key);
                    break;
                case KEY_TYPE_CHAR:
                    printf("Generated random char key: '%c' (%d)\n", char_key, char_key);
                    break;
                case KEY_TYPE_STRING:
                    printf("Generated random string key: %s\n", string_key);
                    break;
                case KEY_TYPE_BYTE_SEQUENCE:
                    printf("Generated random byte sequence key: ");
                    print_byte_sequence(byte_sequence, key_length);
                    break;
            }
        }

        // If a key type is provided
        else if (type_flag) {
            switch (key_type) {
                case KEY_TYPE_BYTE:
                    if (convert_to_byte_key(argv[1]) == -1) {
                        fprintf(stderr, "Invalid byte key format. Must be a number between 0 and 255 or binary (0b...) format or hex (0x...) format.\n");
                        return 1;
                    }
                    byte_key = convert_to_byte_key(text);
                    key_length = 1; // Byte key length is always 1
                    printf("Using byte key: %u (0x%02X)\n", byte_key, byte_key);
                    break;
                case KEY_TYPE_CHAR:
                    char_key = text[0];
                    key_length = 1; // Char key length is always 1
                    printf("Using char key: '%c' (%d)\n", char_key, char_key);
                    break;
                case KEY_TYPE_STRING:
                    if (strlen(text) < MAX_KEY_LENGTH) {
                        strncpy(string_key, text, MAX_KEY_LENGTH - 1);
                        string_key[MAX_KEY_LENGTH - 1] = '\0';
                        key_length = strlen(string_key); // String key length is the length of the string
                        printf("Using string key: %s\n", string_key);
                    } else {
                        fprintf(stderr, "String key is too long. Maximum length is %d characters.\n", MAX_KEY_LENGTH - 1);
                        return 1;
                    }
                    break;
                case KEY_TYPE_BYTE_SEQUENCE:
                    key_length = parse_byte_sequence(text, byte_sequence);
                    if (key_length != -1) {
                        // Successfully parsed byte sequence
                        printf("Using byte sequence key: ");
                        print_byte_sequence(byte_sequence, key_length);
                    } else {
                        fprintf(stderr, "Invalid byte sequence format.\n");
                        return 1;
                    }
                    break;
            }
        }

        // Automatically determine its type based on the input if no type is specified
        else {
            if (convert_to_byte_key(text) != -1) {
                // If the key is a single byte (0-255)
                byte_key = convert_to_byte_key(text);
                key_type = KEY_TYPE_BYTE;
                key_length = 1; // Byte key length is always 1
                printf("Using byte key: %u (0x%02X)\n", byte_key, byte_key);
            } else if (strlen(text) == 1) {
                // If the key is a single character
                char_key = text[0];
                key_type = KEY_TYPE_CHAR;
                key_length = 1; // Char key length is always 1
                printf("Using char key: '%c' (%d)\n", char_key, char_key);
            } else {
                // If the key is a string or byte sequence
                key_length = parse_byte_sequence(text, byte_sequence);
                if (key_length != -1) {
                    // Successfully parsed byte sequence
                    key_type = KEY_TYPE_BYTE_SEQUENCE;
                    printf("Using byte sequence key: ");
                    print_byte_sequence(byte_sequence, key_length);
                } else if (strlen(text) < MAX_KEY_LENGTH) {
                    // Treat as string key
                    strncpy(string_key, text, MAX_KEY_LENGTH - 1);
                    string_key[MAX_KEY_LENGTH - 1] = '\0';
                    key_type = KEY_TYPE_STRING;
                    key_length = strlen(string_key); // String key length is the length of the string
                    printf("Using string key: %s\n", string_key);
                } else {
                    fprintf(stderr, "Key is too long. Maximum length is %d characters.\n", MAX_KEY_LENGTH - 1);
                    return 1;
                }
            }
        }
        validate_key(key_type == KEY_TYPE_BYTE ? (void*) &byte_key : key_type == KEY_TYPE_CHAR ? (void*) &char_key : key_type == KEY_TYPE_STRING ? (void*) string_key : key_type == KEY_TYPE_BYTE_SEQUENCE ? (void*) byte_sequence : NULL, key_type, key_length);
    }

    // If operation (encryption / decryption) type is provided as command line arguments
    int operation = 0;
    if (argc == 3 || argc == 4) {
        for (int i = 2; i < argc; i++) {
            if (strcasecmp(argv[i], "e") == 0 || strcasecmp(argv[i], "encrypt") == 0 || strcasecmp(argv[i], "encryption") == 0) {
                operation = 1; // Encrypt
            } else if (strcasecmp(argv[i], "d") == 0 || strcasecmp(argv[i], "decrypt") == 0 || strcasecmp(argv[i], "decryption") == 0) {
                operation = 2; // Decrypt
            } else if (strcasecmp(argv[i], "bf") == 0 || strcasecmp(argv[i], "brute-force") == 0) {
                operation = 3; // Brute Force Decrypt
            }
        }
    }
    if (operation == 0) {
        // If no operation is provided, ask user for operation
        printf("Choose operation:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Brute Force Decrypt (byte/char keys only)\n");
        if (scanf("%d", &operation) != 1 || (operation < 1 || operation > 3)) {
            fprintf(stderr, "Invalid choice. Please enter 1, 2 or 3.\n");
            return 1;
        }
        while (getchar() != '\n'); // Clear input buffer
    }

    // Perform XOR operation (same for encryption and decryption)
    void *key_ptr = NULL;
    switch (key_type) {
        case KEY_TYPE_BYTE:
            key_ptr = &byte_key;
            break;
        case KEY_TYPE_CHAR:
            key_ptr = &char_key;
            break;
        case KEY_TYPE_STRING:
            key_ptr = string_key;
            break;
        case KEY_TYPE_BYTE_SEQUENCE:
            key_ptr = &byte_sequence;
            break;
    }

    printf("You chose to %s.\n", operation == 1 ? "encrypt" : operation == 2 ? "decrypt" : "brute force decrypt");
    printf("--------------------\n");

    // Get text input
    printf("Enter %s: ", operation == 1 ? "plaintext" : operation == 2 || operation == 3 ? "ciphertext (space(comma)-separated bytes)" : "text");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    // Replace the current XOR operation section with:
    if (operation == 1) {
        // Encryption
        int encrypted_length = xor_encrypt(text, key_ptr, key_length);

        printf("Encrypted bytes: ");
        print_byte_sequence(text, encrypted_length);
    } else if (operation == 2) {
        // Decryption - expect space(comma)-separated byte sequence (to pass parse_byte_sequence() in xor_decrypt())
        int decrypted_length = xor_decrypt(text, key_ptr, key_length);

        if (decrypted_length == -1) {
            fprintf(stderr, "Invalid byte sequence format. Use space(comma)-separated decimal values (e.g., 123,45,200) or binary (0b...) format or hex (0x...) format.\n");
            return 1;
        }

        printf("Decrypted text: %s\n", text);
        printf("Press Enter to continue...");
        while (getchar() != '\n'); // Wait for Enter key
        printf("Decrypted text (byte sequence representation): ");
        print_byte_sequence(text, decrypted_length);
    } else if (operation == 3) {
        // Brute Force Decrypt
        xor_brute_force(text);
    }

    return 0;
}

/**
 * Prints a byte sequence (or string) in decimal, hexadecimal and binary format.
 *
 * This function prints the byte sequence in three formats:
 * - Decimal: Each byte as an unsigned integer.
 * - Hexadecimal: Each byte as a two-digit hexadecimal value (0xXX).
 * - Binary: Each byte as an 8-bit binary value (0bXXXXXXXX).
 *
 * \param bytes     The byte sequence (or string) to print (as an array of unsigned char).
 * \param length    Length of the sequence/array/string.
 */
void print_byte_sequence(const unsigned char *bytes, const int length) {
    printf("(decimal: ");
    for (int i = 0; i < length; i++) {
        printf("%u", bytes[i]);
        if (i < length - 1) printf(",");
    }
    printf(") (hex: ");
    for (int i = 0; i < length; i++) {
        printf("0x%02X", bytes[i]);
        if (i < length - 1) printf(",");
    }
    printf(") (binary: ");
    for (int i = 0; i < length; i++) {
        printf("0b");
        for (int j = 7; j >= 0; j--) {
            printf("%d", (bytes[i] >> j) & 1);
        }
        if (i < length - 1) printf(",");
    }
    printf(")\n");
}

/**
 * Validates the key based on its type and length.
 *
 * Validates that:
 * - Byte key is exactly 1 byte long and in the range 0-255.
 * - Char key is exactly 1 character long and a printable ASCII character (33-126).
 * - String key is between 2 and MAX_KEY_LENGTH-1 characters long, containing only printable ASCII characters (33-126).
 * - Byte sequence key is between 2 and MAX_KEY_LENGTH-1 bytes long, containing values in the range 0-255.
 *
 * \param key           Pointer to the key to validate.
 * \param key_type      Type of the key (byte, char, string, or byte sequence).
 * \param key_length    Length of the key.
 * \return              1 if the key is valid, 0 otherwise.
 */
int validate_key(const void *key, const key_type_t key_type, const int key_length) {
    switch (key_type) {
        case KEY_TYPE_BYTE:
            if (key_length != 1) {
                fprintf(stderr, "Byte key must be exactly 1 byte long.\n");
                return 0;
            }
            if (*(unsigned char*)key < 0 || *(unsigned char*)key > 255) {
                fprintf(stderr, "Byte key must be in the range 0-255.\n");
                return 0;
            }
            break;
        case KEY_TYPE_CHAR:
            if (key_length != 1) {
                fprintf(stderr, "Char key must be exactly 1 character long.\n");
                return 0;
            }
            if (*(char*)key < 33 || *(char*)key > 126) {
                fprintf(stderr, "Char key must be a printable ASCII character (33-126).\n");
                return 0;
            }
            break;
        case KEY_TYPE_STRING:
            if (key_length < 2 || key_length >= MAX_KEY_LENGTH) {
                fprintf(stderr, "String key must be between 2 and %d characters long.\n", MAX_KEY_LENGTH - 1);
                return 0;
            }
            for (int i = 0; i < key_length; i++) {
                if (((char*)key)[i] < 33 || ((char*)key)[i] > 126) {
                    fprintf(stderr, "String key must contain printable ASCII characters (33-126).\n");
                    return 0;
                }
            }
            ((char*)key)[key_length] = '\0'; // Ensure null termination
            break;
        case KEY_TYPE_BYTE_SEQUENCE:
            if (key_length < 2 || key_length >= MAX_KEY_LENGTH) {
                printf("%i\n", key_length);
                fprintf(stderr, "Byte sequence key must be between 2 and %d bytes long.\n", MAX_KEY_LENGTH - 1);
                return 0;
            }
            for (int i = 0; i < key_length; i++) {
                if (((unsigned char*)key)[i] < 0 || ((unsigned char*)key)[i] > 255) {
                    fprintf(stderr, "Byte sequence key must contain values in the range 0-255.\n");
                    return 0;
                }
            }
            break;
    }
    return 1; // Key is valid
}

/**
 * Generates a random XOR key based on the specified key type.
 *
 * Generates a random XOR byte key (0-255).
 * Generates a random XOR printable character key (33-126).
 * Generates a random XOR string key with random length and random characters.
 * Generates a random XOR byte sequence with random length and random byte values.
 *
 * \param key           Pointer to store the generated key.
 * \param key_type      Type of the key to generate (byte, char, string, or byte sequence).
 * \param key_length    Pointer to store the generated key length (for sequences).
 * \return              void
 */
void generate_random_key(void *key, const key_type_t key_type, int *key_length) {
    srand(time(NULL)); // Seed random number generator

    switch (key_type) {
        case KEY_TYPE_BYTE:
            *key_length = 1; // Length of byte key is always 1
            *(unsigned char*)key = rand() % 256; // Random byte value (0-255)
            break;
        case KEY_TYPE_CHAR:
            *key_length = 1; // Length of char key is always 1
            *(char*)key = 33 + (rand() % 94); // Printable ASCII characters (33-126)
            break;
        case KEY_TYPE_STRING: {
            *key_length = (rand() % (MAX_KEY_LENGTH - 2)) + 2; // Generate random length between 2 and MAX_KEY_LENGTH-1
            ((char*)key)[*key_length] = '\0'; // Ensure null termination for string keys

            for (int i = 0; i < *key_length; i++) {
                ((char*)key)[i] = 33 + (rand() % 94); // Printable ASCII characters (33-126)
            }
            break;
        }
        case KEY_TYPE_BYTE_SEQUENCE: {
            *key_length = (rand() % (MAX_KEY_LENGTH - 2)) + 2; // Generate random length between 2 and MAX_KEY_LENGTH

            for (int i = 0; i < *key_length; i++) {
                ((unsigned char*)key)[i] = rand() % 256; // Random byte value (0-255)
            }
            break;
        }
    }
}

/**
 * Converts a binary byte input, hexadecimal string input, or decimal byte sequence input
 * to a key of type unsigned char.
 *
 * \param input Input string (binary, hex, or decimal).
 * \return      Converted unsigned char value, or -1 on error.
 */
int convert_to_byte_key(const char *input) {
    // Check for binary (prefix "0b")
    if (strncmp(input, "0b", 2) == 0) {
        int bit_count = 0;
        for (int i = 2; input[i] != '\0'; i++) {
            if (input[i] != '0' && input[i] != '1') return -1; // Invalid binary input
            bit_count++;
        }
        if (bit_count > 8) return -1; // Binary input too long for a byte
        return (int) strtol(input + 2, NULL, 2);
    }
    // Check for hexadecimal (prefix "0x")
    if (strncmp(input, "0x", 2) == 0) {
        for (int i = 2; input[i] != '\0'; i++) {
            if (!isxdigit(input[i])) return -1; // Invalid hex input
        }
        if (strlen(input) > 4) return -1; // Hex input too long for a byte
        return (int) strtol(input + 2, NULL, 16);
    }
    // Otherwise, treat as decimal
    if (0 < strlen(input) < 4) {
        // Check if input is a valid decimal number
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                return -1; // Invalid input
            }
        }
        int decimal = (int) strtol(input, NULL, 10);
        if (decimal < 0 || decimal > 255) {
            return -1; // Out of range for byte
        }
        return decimal;
    }
    return -1; // Invalid input
}

/**
 * Parses a space(comma)-separated string of byte values into a byte array.
 *
 * Handles binary (0b), hexadecimal (0x), and decimal formats.
 *
 * \param input Input string with comma-separated byte values.
 * \param bytes Buffer to store the parsed bytes. (Must be pre-allocated with sufficient size.)
 * \return      Number of bytes parsed, or -1 on error.
 */
int parse_byte_sequence(const char *input, unsigned char *bytes) {
    char *input_copy = malloc(strlen(input) + 1);
    strcpy(input_copy, input);

    char *token;
    int count = 0;
    char token_with_prefix[32]; // Buffer for adding prefixes

    // Check if input starts with binary prefix
    if (strncmp(input, "0b", 2) == 0) {
        // Handle binary input - can be continuous or space-separated
        char *binary_part = input_copy + 2; // Skip "0b" prefix

        // If continuous binary string, split into 8-bit chunks
        if (strchr(binary_part, ' ') == NULL && strchr(binary_part, ',') == NULL) {
            int len = strlen(binary_part);
            for (int i = 0; i < len && count < MAX_KEY_LENGTH; i += 8) {
                if (i + 8 <= len) {
                    strncpy(token_with_prefix + 2, binary_part + i, 8);
                    token_with_prefix[0] = '0';
                    token_with_prefix[1] = 'b';
                    token_with_prefix[10] = '\0';
                } else {
                    break; // Skip incomplete byte
                }

                int value = convert_to_byte_key(token_with_prefix); // Returns -1 on error
                if (value == -1) {
                    free(input_copy);
                    return -1; // Invalid binary input
                }
                bytes[count] = (unsigned char) value;
                count++;
            }
        } else {
            // Space or comma-separated binary tokens
            token = strtok(binary_part, " ,");
            while (token != NULL && count < MAX_KEY_LENGTH) {
                if (strncmp(token, "0b", 2) == 0) {
                    strcpy(token_with_prefix, token);
                } else {
                    // Add "0b" prefix if not present
                    strcpy(token_with_prefix, "0b");
                    strcat(token_with_prefix, token);
                }

                int value = convert_to_byte_key(token_with_prefix); // Returns -1 on error
                if (value == -1) {
                    free(input_copy);
                    return -1; // Invalid binary input
                }
                bytes[count] = (unsigned char) value;
                count++;
                token = strtok(NULL, " ,");
            }
        }
    }
    // Check if input starts with hex prefix
    else if (strncmp(input, "0x", 2) == 0) {
        // Handle hex input - can be continuous or space-separated
        char *hex_part = input_copy + 2; // Skip "0x" prefix

        // If continuous hex string, split into 2-character chunks
        if (strchr(hex_part, ' ') == NULL && strchr(hex_part, ',') == NULL) {
            int len = strlen(hex_part);
            for (int i = 0; i < len && count < MAX_KEY_LENGTH; i += 2) {
                if (i + 2 <= len) {
                    strncpy(token_with_prefix + 2, hex_part + i, 2);
                    token_with_prefix[0] = '0';
                    token_with_prefix[1] = 'x';
                    token_with_prefix[4] = '\0';
                } else {
                    break; // Skip incomplete byte
                }

                int value = convert_to_byte_key(token_with_prefix); // Returns -1 on error
                if (value == -1) {
                    free(input_copy);
                    return -1; // Invalid hex input
                }
                bytes[count] = (unsigned char) value;
                count++;
            }
        } else {
            // Space or comma-separated hex tokens
            token = strtok(hex_part, " ,");
            while (token != NULL && count < MAX_KEY_LENGTH) {
                if (strncmp(token, "0x", 2) == 0) {
                    strcpy(token_with_prefix, token);
                } else {
                    // Add "0x" prefix if not present
                    strcpy(token_with_prefix, "0x");
                    strcat(token_with_prefix, token);
                }

                int value = convert_to_byte_key(token_with_prefix); // Returns -1 on error
                if (value == -1) {
                    free(input_copy);
                    return -1; // Invalid hex input
                }
                bytes[count] = (unsigned char) value;
                count++;
                token = strtok(NULL, " ,");
            }
        }
    }
    // Handle decimal input (space-separated or comma-separated)
    else {
        token = strtok(input_copy, " ,");
        while (token != NULL && count < MAX_KEY_LENGTH) {
            int value = convert_to_byte_key(token); // Returns -1 on error
            if (value == -1) {
                free(input_copy);
                return -1; // Invalid decimal input
            }
            bytes[count] = (unsigned char) value;
            count++;
            token = strtok(NULL, " ,");
        }
    }

    free(input_copy);
    return count;
}

/**
 * Encrypts the given plaintext using the XOR cipher and saves the result in the same string (array).
 *
 * Each character in the input string is XORed with the key.
 * Saves ciphertext as a byte sequence in the same string.
 * Note: XOR is symmetric, so the same function can work for both encryption and decryption.
 *
 * \param plaintext     Pointer to the input (plaintext) string. The string is modified in place.
 * \param key           Pointer to the key (byte, char, string or byte sequence).
 * \param key_length    Length of the key (for string or byte sequence).
 * \return              Length of encrypted data (length of byte sequence).
 */
int xor_encrypt(unsigned char *plaintext, const void *key, int key_length) {
    int ciphertext_length = strlen((char *) plaintext);

    for (int i = 0; i < ciphertext_length; i++) {
        plaintext[i] ^= ((unsigned char*) key)[i % key_length]; // `[i % key_length]` if key is a string or byte sequence, wraps around if necessary
    }
    return ciphertext_length;
}

/**
 * Decrypts the given ciphertext (byte sequence input) using the XOR cipher and saves the result in the same string (array).
 *
 * Each character in the input string is XORed with the key.
 * Saves decrypted text as a byte sequence in the same string.
 * Note: XOR is symmetric, so the same function can work for both encryption and decryption.
 *
 * \param ciphertext    Pointer to the input (ciphertext) string. The string is modified in place.
 * \param key           Pointer to the key (byte, char, string or byte sequence).
 * \param key_length    Length of the key (for string or byte sequence).
 * \return              Length of decrypted data (length of byte sequence) or -1 on error.
 */
int xor_decrypt(unsigned char *ciphertext, const void *key, int key_length) {
    int byte_count = parse_byte_sequence((char *) ciphertext, ciphertext);
    if (byte_count == -1) {
        return -1; // Invalid input format
    }

    for (int i = 0; i < byte_count; i++) {
        ciphertext[i] ^= ((unsigned char*) key)[i % key_length]; // `[i % key_length]` if key is a string or byte sequence, wraps around if necessary
    }
    ciphertext[byte_count] = '\0';
    return byte_count;
}

/**
* Performs brute force decryption on the given ciphertext using XOR cipher.
 *
 * Tries different key types and lengths based on user selection:
 * - Byte keys: All values (0-255)
 * - Char keys: All printable ASCII characters (32-126)
 *
 * \param ciphertext Pointer to the input ciphertext (byte sequence format).
 */
void xor_brute_force(const char *ciphertext) {
    unsigned char encrypted_bytes[MAX_INPUT_LENGTH];
    int byte_count = parse_byte_sequence(ciphertext, encrypted_bytes);

    if (byte_count == -1) {
        fprintf(stderr, "Invalid byte sequence format for brute force.\n");
        return;
    }

    printf("Brute force decryption options:\n");
    printf("1. Byte keys (0-255)\n");
    printf("2. Char keys (printable ASCII 32-126)\n");
    printf("Choose option (1 or 2): ");

    int choice;
    if (scanf("%d", &choice) != 1 || (choice < 1 || choice > 3)) {
        fprintf(stderr, "Invalid choice. Please enter 1 or 2.\n");
        return;
    }
    while (getchar() != '\n'); // Clear input buffer

    printf("Display options:\n");
    printf("1. Only printable results\n");
    printf("2. All results (including non-printable)\n");
    printf("Choose display option (1 or 2): ");

    int display_choice;
    if (scanf("%d", &display_choice) != 1 || (display_choice != 1 && display_choice != 2)) {
        fprintf(stderr, "Invalid choice. Please enter 1 or 2.\n");
        return;
    }
    while (getchar() != '\n'); // Clear input buffer

    printf("Brute force decryption results:\n");
    printf("==============================\n");

    int start_key, end_key;
    if (choice == 1) {
        // Byte keys: 0-255
        start_key = 0;
        end_key = 255;
        printf("Trying all byte keys (0-255):\n");
    } else {
        // Char keys: printable ASCII 32-126
        start_key = 32;
        end_key = 126;
        printf("Trying all printable ASCII char keys (32-126):\n");
    }

    int found_results = 0;
    int total_results = 0;

    for (int key = start_key; key <= end_key; key++) {
        unsigned char temp[MAX_INPUT_LENGTH];
        memcpy(temp, encrypted_bytes, byte_count); // Copy original encrypted data

        // Decrypt with current key
        for (int i = 0; i < byte_count; i++) {
            temp[i] ^= key;
        }
        temp[byte_count] = '\0';

        total_results++;

        // Check if result contains only printable characters
        int printable = 1;
        for (int i = 0; i < byte_count; i++) {
            if (temp[i] < 32 || temp[i] > 126) {
                printable = 0;
                break;
            }
        }

        // Display based on user's choice
        if (display_choice == 1) {
            // Only show printable results
            if (printable) {
                printf("Key %3d (0x%02X, '%c'): %s\n",
                        key, key, (key >= 32 && key <= 126) ? key : '?', (char *) temp);
                found_results++;
            }
        } else {
            // Show all results
            printf("Key %3d (0x%02X, '%c'): ", key, key, (key >= 32 && key <= 126) ? key : '?');

            if (printable) {
                printf("%s [PRINTABLE]\n", (char *) temp);
                found_results++;
            } else {
                printf("[");
                for (int i = 0; i < byte_count; i++) {
                    printf("%u", temp[i]);
                    if (i < byte_count - 1) printf(",");
                }
                printf("] [NON-PRINTABLE]\n");
            }
        }
    }

    // Display summary
    if (display_choice == 1) {
        if (found_results == 0) {
            printf("No results with printable characters found.\n");
            printf("The key might be outside the %s range or the text might contain non-printable characters.\n", choice == 1 ? "byte (0-255)" : "printable ASCII (32-126)");
        } else {
            printf("\nFound %d potential (printable) result(s) out of %d total attempts.\n", found_results, total_results);
        }
    } else {
        printf("\nTotal results: %d\n", total_results);
        printf("Printable results: %d\n", found_results);
        printf("Non-printable results: %d\n", total_results - found_results);
    }
}
