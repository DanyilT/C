//
// Created by Dany on 07/24/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Bogo Sort Implementation in C
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50
#define MAX_SHUFFLES 1000000

void bogo_sort(void *arr, int size, char type, int visualize);
int is_sorted(void *arr, int size, char type, char order);
void shuffle_array(void *arr, int size, char type);
void print_array(void *arr, int size, char type);

int main(int argc, char *argv[]) {
    srand(time(NULL)); // Initialize random seed

    int visualize = 0;
    if (argc > 1) if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--visualize") == 0) visualize = 1; // Enable visualization if -v or --visualize is passed

    int choice;
    printf(MAGENTA "Bogo Sort\n");
    printf("=========\n" RESET);
    if (visualize) printf(BG_YELLOW "Visualization enabled." RESET "\n");
    printf(RED "⚠ WARNING: " YELLOW "Bogo Sort is extremely inefficient! Use small arrays only.\n" RESET);
    printf("Choose data type:\n");
    printf("1. Integers\n");
    printf("2. Floats\n");
    printf("3. Characters\n");
    printf("4. Strings\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    int size;
    printf("Enter array size (recommended ≤ 5): ");
    scanf("%d", &size);

    if (size > 10) {
        printf(YELLOW "⚠ Array size > 10 may take extremely long time!\n" RESET);
        printf("Continue anyway? (y/n): ");
        char confirm;
        scanf(" %c", &confirm);
        if (confirm != 'y' && confirm != 'Y') {
            printf("Operation cancelled.\n");
            return 0;
        }
    }

    char type = 0;
    void *arr = NULL;

    switch(choice) {
        // For integers
        case 1: {
            type = 'i';
            arr = malloc(size * sizeof(int));

            printf("Enter %d integers: ", size);
            for (int i = 0; i < size; i++) scanf("%*[^0-9]%d", &((int*)arr)[i]);
            while (getchar() != '\n'); // Clear input buffer
            break;
        }
        // For floats
        case 2: {
            type = 'f';
            arr = malloc(size * sizeof(float));

            printf("Enter %d floats: ", size);
            for (int i = 0; i < size; i++) scanf("%*[^0-9.]%f", &((float*)arr)[i]);
            while (getchar() != '\n'); // Clear input buffer
            break;
        }
        // For characters
        case 3: {
            type = 'c';
            arr = malloc(size * sizeof(char));

            printf("Enter %d characters: ", size);
            for (int i = 0; i < size; i++) scanf(" %c", &((char*)arr)[i]);
            while (getchar() != '\n'); // Clear input buffer
            break;
        }
        // For strings
        case 4: {
            type = 's';
            arr = malloc(size * STRING_LENGTH * sizeof(char));

            printf("Enter %d strings: ", size);
            for (int i = 0; i < size; i++) scanf("%s", ((char(*)[STRING_LENGTH])arr)[i]);
            while (getchar() != '\n'); // Clear input buffer
            break;
        }
        // Invalid choice
        default:
            printf(RED "Invalid choice!\n" RESET);
            return 1;
    }

    printf(CYAN "\n-- Bogo Sort --\n" RESET);

    printf(YELLOW "\n-- Original Array\n" RESET DIM);
    print_array(arr, size, type);
    printf(RESET);

    if (is_sorted(arr, size, type, 'a')) {
        printf(GREEN "Array is already sorted!\n" RESET);
    } else {
        printf(DIM "Sorting...\n" RESET);
        bogo_sort(arr, size, type, visualize);
    }

    if (is_sorted(arr, size, type, 'a')) printf(GREEN "\n-- Sorted Array\n" RESET BOLD); else printf(RED "\n-- Not Sorted Array\n" RESET DIM);
    print_array(arr, size, type);
    printf(RESET);

    free(arr);
    return 0;
}

/**
 * Performs bogo sort on an array of various types.
 * Randomly shuffles the array until it becomes sorted.
 *
 * Supported types:
 * - 'i' for int
 * - 'f' for float
 * - 'c' for char
 * - 's' for string (char[STRING_LENGTH]) - `STRING_LENGTH` is defined as 50.
 *
 * @param arr       Pointer to the array to sort.
 * @param size      Number of elements in the array.
 * @param type      Data type of the array elements:
 *                      'i' for int, 'f' for float, 'c' for char, 's' for string (char[STRING_LENGTH]).
 * @param visualize Flag to enable step-by-step visualization. (1 = enable, 0 = disable)
 * @return          void
 */
void bogo_sort(void *arr, int size, char type, int visualize) {
    if (visualize) printf(BOLD "\nStep-by-step sorting:\n" RESET);

    int shuffle_count = 0;
    while (!is_sorted(arr, size, type, 'a') && shuffle_count < MAX_SHUFFLES) {
        shuffle_array(arr, size, type);
        shuffle_count++;

        if (visualize) {
            printf("Shuffle %d: ", shuffle_count);
            print_array(arr, size, type);
            if (is_sorted(arr, size, type, 'a')) printf(GREEN "    ✓ SORTED!\n" RESET); else printf(RED "    ✗ Not sorted\n" RESET);
        }

        // For very large shuffle counts, show progress periodically
        if (!visualize && shuffle_count % 10000 == 0) {
            printf("Shuffles attempted: %d...\n", shuffle_count);
        }
    }

    if (shuffle_count >= MAX_SHUFFLES) {
        printf(RED "  ⚠ Maximum shuffles (%d) reached! Array may not be sorted.\n" RESET, MAX_SHUFFLES);
    } else {
        printf(GREEN "  ✓ Array sorted after %d shuffle%s!\n" RESET, shuffle_count, shuffle_count == 1 ? "" : "s");
    }
}

/**
 * Checks if an array is sorted in ascending order.
 *
 * Supported types:
 * - 'i' for int
 * - 'f' for float
 * - 'c' for char
 * - 's' for string (char[STRING_LENGTH]) - `STRING_LENGTH` is defined as 50.
 *
 * @param arr       Pointer to the array to check.
 * @param size      Number of elements in the array.
 * @param type      Data type of the array elements:
 *                      'i' for int, 'f' for float, 'c' for char, 's' for string (char[STRING_LENGTH]).
 * @param order     Sorting order ('a' for ascending, 'd' for descending).
 * @return          1 if sorted, 0 if not sorted.
 */
int is_sorted(void *arr, int size, char type, char order) {
    for (int i = 0; i < size - 1; i++) {
        switch (type) {
            case 'i': // Integer
                if (order == 'a') if (((int *)arr)[i] > ((int *)arr)[i + 1]) return 0;
                if (order == 'd') if (((int *)arr)[i] < ((int *)arr)[i + 1]) return 0;
                break;
            case 'f': // Float
                if (order == 'a') if (((float *)arr)[i] > ((float *)arr)[i + 1]) return 0;
                if (order == 'd') if (((float *)arr)[i] < ((float *)arr)[i + 1]) return 0;
                break;
            case 'c': // Character
                if (order == 'a') if (((char *)arr)[i] > ((char *)arr)[i + 1]) return 0;
                if (order == 'd') if (((char *)arr)[i] < ((char *)arr)[i + 1]) return 0;
                break;
            case 's': // String
                if (order == 'a') if (strcmp(((char (*)[STRING_LENGTH])arr)[i], ((char (*)[STRING_LENGTH])arr)[i + 1]) > 0) return 0;
                if (order == 'd') if (strcmp(((char (*)[STRING_LENGTH])arr)[i], ((char (*)[STRING_LENGTH])arr)[i + 1]) < 0) return 0;
                break;
            default:
                return 0; // Unknown type
        }
    }
    return 1; // Array is sorted
}

/**
 * Randomly shuffles an array using Fisher-Yates shuffle algorithm.
 *
 * Set the seed for random number generation using `srand(time(NULL))` before calling this function.
 *
 * Supported types:
 * - 'i' for int
 * - 'f' for float
 * - 'c' for char
 * - 's' for string (char[STRING_LENGTH]) - `STRING_LENGTH` is defined as 50.
 *
 * @param arr       Pointer to the array to shuffle.
 * @param size      Number of elements in the array.
 * @param type      Data type of the array elements:
 *                      'i' for int, 'f' for float, 'c' for char, 's' for string (char[STRING_LENGTH]).
 * @return          void
 */
void shuffle_array(void *arr, int size, char type) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // Swap elements at positions i and j
        switch (type) {
            case 'i': {
                int temp = ((int *)arr)[i];
                ((int *)arr)[i] = ((int *)arr)[j];
                ((int *)arr)[j] = temp;
                break;
            }
            case 'f': {
                float temp = ((float *)arr)[i];
                ((float *)arr)[i] = ((float *)arr)[j];
                ((float *)arr)[j] = temp;
                break;
            }
            case 'c': {
                char temp = ((char *)arr)[i];
                ((char *)arr)[i] = ((char *)arr)[j];
                ((char *)arr)[j] = temp;
                break;
            }
            case 's': {
                char temp[STRING_LENGTH];
                strcpy(temp, ((char (*)[STRING_LENGTH])arr)[i]);
                strcpy(((char (*)[STRING_LENGTH])arr)[i], ((char (*)[STRING_LENGTH])arr)[j]);
                strcpy(((char (*)[STRING_LENGTH])arr)[j], temp);
                break;
            }
            default:
                return; // Unknown type
        }
    }
}

/**
 * Prints an array of various types without any special formatting.
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
    printf("[");
    for (int i = 0; i < size; i++) {
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

        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}
