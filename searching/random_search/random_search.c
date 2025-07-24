//
// Created by Dany on 07/24/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Random Search Implementation in C
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50
#define MAX_ATTEMPTS 1000

int random_search(void *arr, int size, char type, void *target, int visualize);
void print_array(void *arr, int size, char type);
void print_array_with_highlight(void *arr, int size, char type, int highlight_index);

int main(int argc, char *argv[]) {
    srand(time(NULL)); // Initialize random seed

    int visualize = 0;
    if (argc > 1) if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--visualize") == 0) visualize = 1; // Enable visualization if -v or --visualize is passed

    int choice;
    printf(MAGENTA "Random Search\n");
    printf("=============\n" RESET);
    if (visualize) printf(BG_YELLOW "Visualization enabled." RESET "\n");
    printf("Choose data type:\n");
    printf("1. Integers\n");
    printf("2. Floats\n");
    printf("3. Characters\n");
    printf("4. Strings\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    int size;
    printf("Enter array size: ");
    scanf("%d", &size);

    char type = 0;
    void *arr = NULL;
    void *target = NULL;

    switch(choice) {
        // For integers
        case 1: {
            type = 'i';
            arr = malloc(size * sizeof(int));
            target = malloc(sizeof(int));

            printf("Enter %d integers: ", size);
            for (int i = 0; i < size; i++) scanf("%*[^0-9]%d", &((int*)arr)[i]);
            while (getchar() != '\n'); // Clear input buffer

            printf("Enter target integer: ");
            scanf("%d", (int*) target);
            break;
        }
        // For floats
        case 2: {
            type = 'f';
            arr = malloc(size * sizeof(float));
            target = malloc(sizeof(float));

            printf("Enter %d floats: ", size);
            for (int i = 0; i < size; i++) scanf("%*[^0-9.]%f", &((float*)arr)[i]);
            while (getchar() != '\n'); // Clear input buffer

            printf("Enter target float: ");
            scanf("%f", (float*) target);
            break;
        }
        // For characters
        case 3: {
            type = 'c';
            arr = malloc(size * sizeof(char));
            target = malloc(sizeof(char));

            printf("Enter %d characters: ", size);
            for (int i = 0; i < size; i++) scanf(" %c", &((char*)arr)[i]);
            while (getchar() != '\n'); // Clear input buffer

            printf("Enter target character: ");
            scanf(" %c", (char*) target);
            break;
        }
        // For strings
        case 4: {
            type = 's';
            arr = malloc(size * STRING_LENGTH * sizeof(char));
            target = malloc(STRING_LENGTH * sizeof(char));

            printf("Enter %d strings: ", size);
            for (int i = 0; i < size; i++) scanf("%s", ((char(*)[STRING_LENGTH])arr)[i]);
            while (getchar() != '\n'); // Clear input buffer

            printf("Enter target string: ");
            scanf("%s", (char*)target);
            break;
        }
        // Invalid choice
        default:
            printf(RED "Invalid choice!\n" RESET);
            return 1;
    }

    printf(CYAN "\n-- Random Search --\n" RESET);
    printf("Array: " DIM);
    print_array(arr, size, type);
    printf(RESET);

    int result = random_search(arr, size, type, target, visualize);
    switch (type) {
        case 'i':
            if (result > -1)
                printf(GREEN "Integer %d found at index %d" BOLD " (arr[%d] == %d)\n" RESET, *(int*)target, result, result, ((int*)arr)[result]);
            else
                printf(RED "Integer %d not found after %d attempts\n" RESET, *(int*)target, -result);
            break;
        case 'f':
            if (result > -1)
                printf(GREEN "Float %.2f found at index %d" BOLD " (arr[%d] == %.2f)\n" RESET, *(float*)target, result, result, ((float*)arr)[result]);
            else
                printf(RED "Float %.2f not found after %d attempts\n" RESET, *(float*)target, -result);
            break;
        case 'c':
            if (result > -1)
                printf(GREEN "Character '%c' found at index %d" BOLD " (arr[%d] == '%c')\n" RESET, *(char*)target, result, result, ((char*)arr)[result]);
            else
                printf(RED "Character '%c' not found after %d attempts\n" RESET, *(char*)target, -result);
            break;
        case 's':
            if (result > -1)
                printf(GREEN "String \"%s\" found at index %d" BOLD " (arr[%d] == \"%s\")\n" RESET, (char*)target, result, result, ((char(*)[STRING_LENGTH])arr)[result]);
            else
                printf(RED "String \"%s\" not found after %d attempts\n" RESET, (char*)target, -result);
            break;
        default:
            if (result > -1)
                printf(GREEN "Element found at index %d" BOLD " (arr[%d])\n" RESET, result, result);
            else
                printf(RED "Element not found after %d attempts\n" RESET, -result);
    }

    free(arr);
    free(target);
    return 0;
}

/**
 * Performs a random search on an array of various types.
 *
 * Supported types:
 * - 'i' for int
 * - 'f' for float
 * - 'c' for char
 * - 's' for string (char[STRING_LENGTH]) - `STRING_LENGTH` is defined as 50.
 *
 * @param arr       Pointer to the array to search.
 * @param size      Number of elements in the array.
 * @param type      Data type of the array elements:
 *                      'i' for int, 'f' for float, 'c' for char, 's' for string (char[STRING_LENGTH]).
 * @param target    Pointer to the target value to search for.
 * @param visualize Flag to enable step-by-step visualization. (1 = enable, 0 = disable)
 * @return          Index of the found element, -1 if not found after MAX_ATTEMPTS, -2 for unknown type.
 */
int random_search(void *arr, int size, char type, void *target, int visualize) {
    if (visualize) printf(BOLD "\nStep-by-step search:\n" RESET);

    int attempts = 0, *checked = calloc(size, sizeof(int)); // Track checked indices
    while (attempts < MAX_ATTEMPTS) {
        int random_index = rand() % size;
        attempts++;

        if (visualize) {
            printf("Attempt %d: Checking random index %d -> ", attempts, random_index);
            print_array_with_highlight(arr, size, type, random_index);
        }

        switch (type) {
            case 'i': // Integer
                if (((int *)arr)[random_index] == *(int *)target) {
                    if (visualize) printf(GREEN "✓ Match found!\n" RESET);
                    free(checked); // Free allocated memory for checked indices
                    return random_index; // Return index of found element
                }
                break;
            case 'f': // Float
                if (((float *)arr)[random_index] == *(float *)target) {
                    if (visualize) printf(GREEN "✓ Match found!\n" RESET);
                    free(checked); // Free allocated memory for checked indices
                    return random_index; // Return index of found element
                }
                break;
            case 'c': // Character
                if (((char *)arr)[random_index] == *(char *)target) {
                    if (visualize) printf(GREEN "✓ Match found!\n" RESET);
                    free(checked); // Free allocated memory for checked indices
                    return random_index; // Return index of found element
                }
                break;
            case 's': // String
                if (strcmp(((char (*)[STRING_LENGTH])arr)[random_index], target) == 0) {
                    if (visualize) printf(GREEN "✓ Match found!\n" RESET);
                    free(checked); // Free allocated memory for checked indices
                    return random_index; // Return index of found element
                }
                break;
            default:
                free(checked); // Free allocated memory for checked indices
                return -2; // Unknown type
        }

        if (visualize && checked[random_index]) printf(YELLOW "~ Already checked this index\n" RESET);
        else if (visualize && !checked[random_index]) printf(RED "✗ No match\n" RESET);

        checked[random_index] = 1;

        // If all indices have been checked, break early
        int all_checked = 1;
        for (int i = 0; i < size; i++) {
            if (!checked[i]) {
                all_checked = 0;
                break;
            }
        }
        if (all_checked) {
            free(checked);
            return -attempts; // Element not found (All indices checked)
        }
    }

    free(checked);
    return -1; // Element not found (after MAX_ATTEMPTS)
}

/**
 * Prints an array of various types without highlighting.
 *
 * Supported types:
 * - 'i' for int
 * - 'f' for float
 * - 'c' for char
 * - 's' for string (char[STRING_LENGTH]) - `STRING_LENGTH` is defined as 50.
 *
 * @param arr       Pointer to the array to print.
 * @param size      Number of elements in the array.
 * @param type      Data type of the array elements:
 *                      'i' for int, 'f' for float, 'c' for char, 's' for string (char[STRING_LENGTH]).
 * @return          void
 */
void print_array(void *arr, int size, char type) {
    print_array_with_highlight(arr, size, type, -1); // Call with no highlight
}

/**
 * Prints an array of various types with an option to highlight a specific index.
 *
 * Supported types:
 * - 'i' for int
 * - 'f' for float
 * - 'c' for char
 * - 's' for string (char[STRING_LENGTH]) - `STRING_LENGTH` is defined as 50.
 *
 * @param arr       Pointer to the array to print.
 * @param size      Number of elements in the array.
 * @param type      Data type of the array elements:
 *                      'i' for int, 'f' for float, 'c' for char, 's' for string (char[STRING_LENGTH]).
 * @param highlight_index   Index of the element to highlight (optional, -1 for no highlight).
 * @return          void
 */
void print_array_with_highlight(void *arr, int size, char type, int highlight_index) {
    printf("[");
    for (int i = 0; i < size; i++) {
        if (i == highlight_index) printf(YELLOW BOLD);

        switch (type) {
            case 'i':
                printf("%d", ((int *)arr)[i]);
                break;
            case 'f':
                printf("%.2f", ((float *)arr)[i]);
                break;
            case 'c':
                printf("'%c'", ((char *)arr)[i]);
                break;
            case 's':
                printf("\"%s\"", ((char (*)[STRING_LENGTH])arr)[i]);
                break;
            default:
                printf("Unknown type");
                return;
        }

        if (i == highlight_index) printf(RESET);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}
