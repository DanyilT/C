//
// Created by Dany on 07/24/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Bubble Sort Implementation in C
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50

void bubble_sort(void *arr, int size, char type, int visualize);
void print_array(void *arr, int size, char type);
void print_array_with_highlight(void *arr, int size, char type, int index[2]);

int main(int argc, char *argv[]) {
    int visualize = 0;
    if (argc > 1) if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--visualize") == 0) visualize = 1; // Enable visualization if -v or --visualize is passed

    int choice;
    printf(MAGENTA "Bubble Sort\n");
    printf("===========\n" RESET);
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

    printf(CYAN "\n-- Bubble Sort --\n" RESET);

    printf(YELLOW "\n-- Original Array\n" RESET DIM);
    print_array(arr, size, type);
    printf(RESET);

    printf(DIM "Sorting...\n" RESET);
    bubble_sort(arr, size, type, visualize);

    printf(GREEN "\n-- Sorted Array\n" RESET BOLD);
    print_array(arr, size, type);
    printf(RESET);

    free(arr);
    return 0;
}

/**
 * Performs bubble sort on an array of various types.
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
void bubble_sort(void *arr, int size, char type, int visualize) {
    if (visualize) printf(BOLD "\nStep-by-step sorting:\n" RESET);

    for (int i = 0; i < size - 1; i++) {
        if (visualize) printf(CYAN "Pass %d:\n" RESET, i + 1);

        int swapped = 0;
        for (int j = 0; j < size - i - 1; j++) {
            if (visualize) {
                printf("  Comparing indices %d and %d -> ", j, j + 1);
                print_array_with_highlight(arr, size, type, (int []) {j, j + 1});
            }

            switch (type) {
                case 'i': // Integer
                case 'f': // Float
                    if (((float*)arr)[j] > ((float*)arr)[j + 1]) {
                        swapped = 1;
                        // Swap elements
                        float temp = ((float*)arr)[j];
                        ((float*)arr)[j] = ((float*)arr)[j + 1];
                        ((float*)arr)[j + 1] = temp;
                    }
                    break;
                case 'c': // Character
                    if (((char*)arr)[j] > ((char*)arr)[j + 1]) {
                        swapped = 1;
                        // Swap elements
                        char temp = ((char*)arr)[j];
                        ((char*)arr)[j] = ((char*)arr)[j + 1];
                        ((char*)arr)[j + 1] = temp;
                    }
                    break;
                case 's': // String
                    if (strcmp(((char(*)[STRING_LENGTH])arr)[j], ((char(*)[STRING_LENGTH])arr)[j + 1]) > 0) {
                        swapped = 1;
                        // Swap elements
                        char temp[STRING_LENGTH];
                        strcpy(temp, ((char(*)[STRING_LENGTH])arr)[j]);
                        strcpy(((char(*)[STRING_LENGTH])arr)[j], ((char(*)[STRING_LENGTH])arr)[j + 1]);
                        strcpy(((char(*)[STRING_LENGTH])arr)[j + 1], temp);
                    }
                    break;
                default:
                    return; // Unknown type
            }

            if (swapped && visualize) {
                printf(GREEN "    ✓ Swapped -> " RESET);
                print_array_with_highlight(arr, size, type, (int []) {j, j + 1});
            } else if (!swapped && visualize) {
                printf(RED "    ✗ No swap needed\n" RESET);
            }
        }

        if (visualize) {
            printf("  End of pass %d: ", i + 1);
            print_array(arr, size, type);
            printf("\n");
        }

        // If no swapping occurred, array is sorted
        if (!swapped) {
            if (visualize) printf(GREEN "Array is sorted! Early termination.\n" RESET);
            break;
        }
    }
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
    print_array_with_highlight(arr, size, type, (int []) {-1, -1}); // Call with no highlight
}

/**
 * Prints an array of various types with highlighting for two specific indices.
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
 * @param index     First and second index to highlight (-1 for no highlight).
 * @return          void
 */
void print_array_with_highlight(void *arr, int size, char type, int index[2]) {
    printf("[");
    for (int i = 0; i < size; i++) {
        if (i == index[0] || i == index[1]) printf(YELLOW BOLD);

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

        if (i == index[0] || i == index[1]) printf(RESET);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}
