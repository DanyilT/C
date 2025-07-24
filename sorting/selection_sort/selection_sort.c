//
// Created by Dany on 07/24/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Selection Sort Implementation in C
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50

void selection_sort(void *arr, int size, char type, int visualize);
void print_array(void *arr, int size, char type);
void print_array_with_highlight(void *arr, int size, char type, int sorted_boundary, int current, int min_index);

int main(int argc, char *argv[]) {
    int visualize = 0;
    if (argc > 1) if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--visualize") == 0) visualize = 1; // Enable visualization if -v or --visualize is passed

    int choice;
    printf(MAGENTA "Selection Sort\n");
    printf("==============\n" RESET);
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

    printf(CYAN "\n-- Selection Sort --\n" RESET);

    printf(YELLOW "\n-- Original Array\n" RESET DIM);
    print_array(arr, size, type);
    printf(RESET);

    printf(DIM "Sorting...\n" RESET);
    selection_sort(arr, size, type, visualize);

    printf(GREEN "\n-- Sorted Array\n" RESET BOLD);
    print_array(arr, size, type);
    printf(RESET);

    free(arr);
    return 0;
}

/**
 * Performs selection sort on an array of various types.
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
void selection_sort(void *arr, int size, char type, int visualize) {
    if (visualize) printf(BOLD "\nStep-by-step sorting:\n" RESET);

    for (int i = 0; i < size - 1; i++) {
        if (visualize) printf(CYAN "\nPass %d: Finding minimum in unsorted portion...\n" RESET, i + 1);

        // Find minimum element in remaining unsorted array
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (visualize) {
                printf("  Comparing with index %d -> ", j);
                print_array_with_highlight(arr, size, type, i, j, min_index);
            }

            switch (type) {
                case 'i': // Integer
                case 'f': // Float
                    if (((float*)arr)[j] < ((float*)arr)[min_index]) min_index = j;
                    break;
                case 'c': // Character
                    if (((char*)arr)[j] < ((char*)arr)[min_index]) min_index = j;
                    break;
                case 's': // String
                    if (strcmp(((char(*)[STRING_LENGTH])arr)[j], ((char(*)[STRING_LENGTH])arr)[min_index]) < 0) min_index = j;
                    break;
                default:
                    return; // Unsupported type
            }

            if (min_index == j && visualize) printf(YELLOW "    → New minimum found at index %d\n" RESET, min_index);
            else if (min_index != j && visualize) printf("    → No change\n");
        }

        // Swap the found minimum element with the first element
        if (min_index != i) {
            if (visualize) printf(GREEN "  ✓ Swapping index %d with index %d\n" RESET, i, min_index);

            switch (type) {
                case 'i':
                case 'f': {
                    float temp = ((float*)arr)[i];
                    ((float*)arr)[i] = ((float*)arr)[min_index];
                    ((float*)arr)[min_index] = temp;
                    break;
                }
                case 'c': {
                    char temp = ((char*)arr)[i];
                    ((char*)arr)[i] = ((char*)arr)[min_index];
                    ((char*)arr)[min_index] = temp;
                    break;
                }
                case 's': {
                    char temp[STRING_LENGTH];
                    strcpy(temp, ((char(*)[STRING_LENGTH])arr)[i]);
                    strcpy(((char(*)[STRING_LENGTH])arr)[i], ((char(*)[STRING_LENGTH])arr)[min_index]);
                    strcpy(((char(*)[STRING_LENGTH])arr)[min_index], temp);
                    break;
                }
                default:
                    return; // Unsupported type
            }
        } else if (min_index == i && visualize) {
            printf(RED "  ✗ No swap needed (minimum is already in correct position)\n" RESET);
        }

        if (visualize) {
            printf(BOLD"  Result after pass %d: " RESET, i + 1);
            print_array_with_highlight(arr, size, type, i + 1, -1, -1);
            printf("\n");
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
    print_array_with_highlight(arr, size, type, -1, -1, -1); // Call with no highlight
}

/**
 * Prints an array of various types with highlighting for sorted boundary, current element, and minimum element.
 *
 * Supported types:
 * - 'i' for int
 * - 'f' for float
 * - 'c' for char
 * - 's' for string (char[STRING_LENGTH]) - `STRING_LENGTH` is defined as 50.
 *
 * @param arr               Pointer to the array to print.
 * @param size              Number of elements in the array.
 * @param type              Data type of the array elements:
 *                              'i' for int, 'f' for float, 'c' for char, 's' for string (char[STRING_LENGTH]).
 * @param sorted_boundary   Index marking the boundary between sorted and unsorted portions (-1 for no highlight).
 * @param current           Index of the current element being compared (-1 for no highlight).
 * @param min_index         Index of the current minimum element (-1 for no highlight).
 * @return                  void
 */
void print_array_with_highlight(void *arr, int size, char type, int sorted_boundary, int current, int min_index) {
    printf("[");
    for (int i = 0; i < size; i++) {
        if (i < sorted_boundary && sorted_boundary != -1) printf(GREEN); // Sorted portion
        else if (i == current) printf(BLUE BOLD); // Current element being compared
        else if (i == min_index) printf(YELLOW BOLD); // Current minimum
        else if (sorted_boundary != -1) printf(DIM); // Unsorted portion

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

        if ((i < sorted_boundary && sorted_boundary != -1) || i == current || i == min_index || sorted_boundary != -1) printf(RESET);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}
