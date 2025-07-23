//
// Created by Dany on 07/23/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Rail Fence Cipher Implementation in C
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Buffer for input (plaintext / ciphertext), can hold up to 255 characters (plus null terminator)
#define MAX_INPUT_LENGTH 256
#define MIN_RAILS 2
#define MAX_RAILS 100

int rail_fence_encrypt(char *plaintext, const int rails);
int rail_fence_decrypt(char *ciphertext, const int rails);
void rail_fence_brute_force(const char *ciphertext);
void visualize_rail_fence(const char *text, const int rails, const int is_encrypt);
int validate_rails(const int rails, const int text_length);
void generate_random_rails(int *rails);

int main(int argc, char **argv) {
    char text[MAX_INPUT_LENGTH];
    int rails = 0; // key

    printf("Rail Fence Cipher\n");
    printf("=================\n");

    // Check if rails count is provided as command line arguments
    if (argc == 2 || argc == 3 || argc == 4) {
        if (strcasecmp(argv[1], "rand") == 0 || strcasecmp(argv[1], "random") == 0 || strcasecmp(argv[1], "generate") == 0) {
            // Generate random number of rails
            generate_random_rails(&rails);
            printf("Generated random rails count (key): %d\n", rails);
        } else {
            // Parse rails count
            char *endptr;
            rails = (int) strtol(argv[1], &endptr, 10);
            if (*endptr != '\0' || rails < MIN_RAILS || rails > MAX_RAILS) {
                fprintf(stderr, "Invalid rails count. Must be between %d and %d.\n", MIN_RAILS, MAX_RAILS);
                return 1;
            }
            printf("Using rails count (key): %d\n", rails);
        }
    }
    else {
        fprintf(stderr, "Usage: %s <rails (or rand)> <operation (e/d/bf)> [visualize]\n", argv[0]);

        // Interactive mode
        printf("Enter number of rails (%d-%d) or press Enter to generate random: ", MIN_RAILS, MAX_RAILS);
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0'; // Remove newline character

        // If no rails count is provided, generate a random one
        if (strlen(text) == 0) {
            generate_random_rails(&rails);
            printf("Generated random rails count (key): %d\n", rails);
        } else {
            char *endptr;
            rails = (int) strtol(text, &endptr, 10);
            if (*endptr != '\0' || rails < MIN_RAILS || rails > MAX_RAILS) {
                fprintf(stderr, "Invalid rails count. Must be between %d and %d.\n", MIN_RAILS, MAX_RAILS);
                return 1;
            }
            printf("Using rails count (key): %d\n", rails);
        }
    }

    // If operation (encryption / decryption / brute-force) type is provided as command line arguments
    int operation = 0;
    int visualize = 0;
    if (argc == 3 || argc == 4) {
        if (strcasecmp(argv[2], "e") == 0 || strcasecmp(argv[2], "encrypt") == 0 || strcasecmp(argv[2], "encryption") == 0) {
            operation = 1; // Encrypt
        } else if (strcasecmp(argv[2], "d") == 0 || strcasecmp(argv[2], "decrypt") == 0 || strcasecmp(argv[2], "decryption") == 0) {
            operation = 2; // Decrypt
        } else if (strcasecmp(argv[2], "bf") == 0 || strcasecmp(argv[2], "brute-force") == 0) {
            operation = 3; // Brute Force Decrypt
        } else if (strcasecmp(argv[2], "v") == 0 || strcasecmp(argv[2], "visualize") == 0) {
            visualize = 1; // Visualize Rail Fence
            // Check for operation in argv[3]
            if (argc == 4) {
                if (strcasecmp(argv[3], "e") == 0 || strcasecmp(argv[3], "encrypt") == 0 || strcasecmp(argv[3], "encryption") == 0) {
                    operation = 1; // Encrypt
                } else if (strcasecmp(argv[3], "d") == 0 || strcasecmp(argv[3], "decrypt") == 0 || strcasecmp(argv[3], "decryption") == 0) {
                    operation = 2; // Decrypt
                } else {
                    fprintf(stderr, "Invalid operation for visualization. Use 'e' for encrypt or 'd' for decrypt.\n");
                    return 1;
                }
            }
        } else {
            fprintf(stderr, "Invalid operation. Use 'e' for encrypt, 'd' for decrypt, or 'bf' for brute force decrypt.\n");
            return 1;
        }
        if (argc == 4) {
            if (strcasecmp(argv[3], "v") == 0 || strcasecmp(argv[3], "visualize") == 0) {
                visualize = 1; // Visualize Rail Fence
            }
        }
    }
    if (operation == 0) {
        // If no operation is provided, ask user for operation
        printf("Choose operation:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Brute Force Decrypt\n");
        if (scanf("%d", &operation) != 1 || (operation < 1 || operation > 3)) {
            fprintf(stderr, "Invalid choice. Please enter 1, 2 or 3.\n");
            return 1;
        }
        while (getchar() != '\n'); // Clear input buffer
    }

    printf("You chose to %s.\n", operation == 1 ? "encrypt" : operation == 2 ? "decrypt" : "brute force decrypt");
    printf("--------------------\n");

    // Get text input
    printf("Enter %s: ", operation == 1 ? "plaintext" : operation == 2 || operation == 3 ? "ciphertext" : "text");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    // Validate rails count against text length
    if (operation != 3) {
        if (!validate_rails(rails, strlen(text))) {
            return 1;
        }
    }

    if (visualize && operation != 3) visualize_rail_fence(text, rails, operation == 1 ? 1 : 0); // Visualize the rail fence pattern

    // Perform Rail Fence operation
    if (operation == 1) {
        // Encryption
        rail_fence_encrypt(text, rails);
        printf("Encrypted text: %s\n", text);
    } else if (operation == 2) {
        // Decryption
        rail_fence_decrypt(text, rails);
        printf("Decrypted text: %s\n", text);
    } else if (operation == 3) {
        // Brute Force Decrypt
        rail_fence_brute_force(text);
    }

    return 0;
}

/**
 * Validates the rails count (key) based on constraints and text length.
 *
 * Validates that:
 * - Rails count (key) is between MIN_RAILS and MAX_RAILS.
 * - Rails count (key) is not greater than text length (for meaningful encryption).
 *
 * \param rails         Number of rails to validate. (key)
 * \param text_length   Length of the text (0 for basic validation).
 * \return              1 if valid, 0 otherwise.
 */
int validate_rails(const int rails, const int text_length) {
    if (rails < MIN_RAILS || rails > MAX_RAILS) {
        fprintf(stderr, "Rails count must be between %d and %d.\n", MIN_RAILS, MAX_RAILS);
        return 0;
    }

    if (text_length > 0 && rails >= text_length) {
        fprintf(stderr, "Rails count (%d) must be less than text length (%d) for meaningful encryption.\n", rails, text_length);
        return 0;
    }

    return 1; // Valid
}

/**
 * Generates a random number of rails between MIN_RAILS and MAX_RAILS. (key)
 *
 * \param rails Pointer to store the generated rails count.
 */
void generate_random_rails(int *rails) {
    srand(time(NULL)); // Seed random number generator
    *rails = MIN_RAILS + (rand() % (MAX_RAILS - MIN_RAILS + 1));
}

/**
 * Visualizes the rail fence encryption process by showing the zigzag pattern.
 *
 * Displays how letters are placed on different rails during encryption.
 *
 * \param text      The text to visualize.
 * \param rails     Number of rails to use. (key)
 * \param is_encrypt True for encryption visualization, false for decryption. (1/0)
 * \return          void
 */
void visualize_rail_fence(const char *text, const int rails, const int is_encrypt) {
    int text_length = strlen(text);

    if (rails <= 1 || text_length == 0) {
        printf("Cannot visualize: invalid parameters\n");
        return;
    }

    // Create a 2D array to represent the rails
    char **rail_grid = malloc(rails * sizeof(char*));
    for (int i = 0; i < rails; i++) {
        rail_grid[i] = malloc((text_length + 1) * sizeof(char));
        memset(rail_grid[i], '.', text_length); // Fill with dots
        rail_grid[i][text_length] = '\0';
    }

    if (is_encrypt) {
        printf("Encryption Visualization:\n");
        printf("=========================\n");
        printf("Text: %s\n", text);
        printf("Rails: %d\n\n", rails);

        // Place characters on rails following the zigzag pattern
        int current_rail = 0;
        int direction = 1; // 1 for down, -1 for up

        for (int i = 0; i < text_length; i++) {
            rail_grid[current_rail][i] = text[i];

            // Change direction at the top and bottom rails
            if (current_rail == 0) {
                direction = 1;
            } else if (current_rail == rails - 1) {
                direction = -1;
            }

            current_rail += direction;
        }

        printf("Zigzag pattern:\n");
        for (int i = 0; i < rails; i++) {
            printf("Rail %d: %s\n", i + 1, rail_grid[i]);
        }

        // Show the reading order
        printf("\nReading order (left to right, rail by rail):\n");
        for (int i = 0; i < rails; i++) {
            printf("Rail %d: ", i + 1);
            for (int j = 0; j < text_length; j++) {
                if (rail_grid[i][j] != '.') {
                    printf("%c", rail_grid[i][j]);
                }
            }
            printf("\n");
        }
    } else {
        printf("Decryption Visualization:\n");
        printf("=========================\n");
        printf("Ciphertext: %s\n", text);
        printf("Rails: %d\n\n", rails);

        // First, mark the positions where characters should be placed
        int current_rail = 0;
        int direction = 1;

        for (int i = 0; i < text_length; i++) {
            rail_grid[current_rail][i] = '*'; // Mark position

            if (current_rail == 0) {
                direction = 1;
            } else if (current_rail == rails - 1) {
                direction = -1;
            }

            current_rail += direction;
        }

        printf("Marked positions for characters:\n");
        for (int i = 0; i < rails; i++) {
            printf("Rail %d: %s\n", i + 1, rail_grid[i]);
        }

        // Fill the marked positions with ciphertext characters
        int text_index = 0;
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < text_length; j++) {
                if (rail_grid[i][j] == '*' && text_index < text_length) {
                    rail_grid[i][j] = text[text_index++];
                } else if (rail_grid[i][j] == '*') {
                    rail_grid[i][j] = '.';
                }
            }
        }

        printf("\nFilled with ciphertext characters:\n");
        for (int i = 0; i < rails; i++) {
            printf("Rail %d: %s\n", i + 1, rail_grid[i]);
        }

        // Show the reading order (zigzag pattern)
        printf("\nReading in zigzag order:\n");
        current_rail = 0;
        direction = 1;

        for (int i = 0; i < text_length; i++) {
            printf("Position %d: Rail %d -> %c\n", i + 1, current_rail + 1, rail_grid[current_rail][i]);

            if (current_rail == 0) {
                direction = 1;
            } else if (current_rail == rails - 1) {
                direction = -1;
            }

            current_rail += direction;
        }
    }

    // Free allocated memory
    for (int i = 0; i < rails; i++) {
        free(rail_grid[i]);
    }
    free(rail_grid);

    printf("\n");
}

/**
 * Encrypts the given plaintext using the Rail Fence cipher and saves the result in the same string.
 *
 * Creates a zigzag pattern across the specified number of rails, then reads off linearly.
 *
 * \param plaintext Pointer to the input plaintext string. The string is modified in place.
 * \param rails     Number of rails to use for encryption. (key)
 * \return          Length of encrypted data.
 */
int rail_fence_encrypt(char *plaintext, const int rails) {
    int len = strlen(plaintext);
    if (len == 0 || rails <= 1) return len; // No encryption needed for empty string or single rail

    // Create rail matrix
    char rail[MAX_RAILS][MAX_INPUT_LENGTH];

    // Initialize with null characters (to mark empty positions, and avoid garbage values)
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            rail[i][j] = '\0';
        }
    }

    // Fill the rail matrix in zigzag pattern
    int current_rail = 0;
    int direction = 1; // 1 for down, -1 for up

    for (int i = 0; i < len; i++) {
        rail[current_rail][i] = plaintext[i];

        // Change direction at top and bottom rails
        if (current_rail == 0) {
            direction = 1;
        } else if (current_rail == rails - 1) {
            direction = -1;
        }

        current_rail += direction;
    }

    // Read off the rails linearly
    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != '\0') {
                plaintext[index++] = rail[i][j];
            }
        }
    }

    plaintext[index] = '\0';
    return index;
}

/**
 * Decrypts the given ciphertext using the Rail Fence cipher and saves the result in the same string.
 *
 * Recreates the rail pattern and fills it with the ciphertext, then reads in zigzag order.
 *
 * \param ciphertext Pointer to the input ciphertext string. The string is modified in place.
 * \param rails     Number of rails used for encryption. (key)
 * \return          Length of decrypted data.
 */
int rail_fence_decrypt(char *ciphertext, const int rails) {
    int len = strlen(ciphertext);
    if (len == 0 || rails <= 1) return len; // No decryption needed for empty string or single rail

    // Create rail matrix
    char rail[MAX_RAILS][MAX_INPUT_LENGTH];

    // Initialize with null characters (to mark empty positions, and avoid garbage values)
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            rail[i][j] = '\0';
        }
    }

    // Mark the positions in zigzag pattern
    int current_rail = 0;
    int direction = 1; // 1 for down, -1 for up

    for (int i = 0; i < len; i++) {
        rail[current_rail][i] = '*'; // Mark position

        if (current_rail == 0) {
            direction = 1;
        } else if (current_rail == rails - 1) {
            direction = -1;
        }

        current_rail += direction;
    }

    // Fill the marked positions with ciphertext
    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '*' && index < len) {
                rail[i][j] = ciphertext[index++];
            }
        }
    }

    // Read off in zigzag pattern
    current_rail = 0;
    direction = 1;
    index = 0;

    for (int i = 0; i < len; i++) {
        ciphertext[index++] = rail[current_rail][i];

        if (current_rail == 0) {
            direction = 1;
        } else if (current_rail == rails - 1) {
            direction = -1;
        }

        current_rail += direction;
    }

    ciphertext[index] = '\0';
    return index;
}

/**
 * Performs brute force decryption on the given ciphertext using Rail Fence cipher.
 *
 * Tries all possible numbers of rails from MIN_RAILS to MAX_RAILS or text length.
 *
 * \param ciphertext Pointer to the input ciphertext.
 */
void rail_fence_brute_force(const char *ciphertext) {
    int len = strlen(ciphertext);

    if (len < 2) {
        printf("Text too short for brute force analysis.\n");
        return;
    }

    printf("Display options:\n");
    printf("1. Only potentially meaningful results\n");
    printf("2. All results\n");
    printf("Choose display option (1 or 2): ");

    int display_choice;
    if (scanf("%d", &display_choice) != 1 || (display_choice != 1 && display_choice != 2)) {
        fprintf(stderr, "Invalid choice. Please enter 1 or 2.\n");
        return;
    }
    while (getchar() != '\n'); // Clear input buffer

    printf("Brute force decryption results:\n");
    printf("==============================\n");

    int max_rails = (len < MAX_RAILS) ? len - 1 : MAX_RAILS;
    int found_results = 0;

    for (int rails = MIN_RAILS; rails <= max_rails; rails++) {
        char temp[MAX_INPUT_LENGTH];
        strcpy(temp, ciphertext);

        rail_fence_decrypt(temp, rails);

        // Check if result looks meaningful (contains common words or patterns)
        int meaningful = 0;
        if (display_choice == 1) {
            // Simple heuristic: check for common English patterns
            meaningful = (strstr(temp, "the") != NULL || strstr(temp, "and") != NULL ||
                         strstr(temp, "ing") != NULL || strstr(temp, "tion") != NULL ||
                         strstr(temp, "THE") != NULL || strstr(temp, "AND") != NULL);
        }

        if (display_choice == 2 || meaningful) {
            printf("Rails %2d: %s", rails, temp);
            if (meaningful) printf(" [POTENTIALLY MEANINGFUL]");
            printf("\n");
            if (meaningful) found_results++;
        }
    }

    if (display_choice == 1 && found_results == 0) {
        printf("No potentially meaningful results found.\n");
        printf("Try option 2 to see all results, or the text might not be Rail Fence encrypted.\n");
    }

    printf("\nTotal rails tested: %d\n", max_rails - MIN_RAILS + 1);
    if (display_choice == 1) {
        printf("Potentially meaningful results: %d\n", found_results);
    }
}
