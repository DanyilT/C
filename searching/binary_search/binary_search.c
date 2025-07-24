//
// Created by Dany on 07/24/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Binary Search Implementation in C
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50

int binary_search(void *arr, int size, char type, void *target, int visualize);
void print_array(void *arr, int size, char type);
void print_array_with_range(void *arr, int size, char type, int left, int right, int mid);
void sort_array(void *arr, int size, char type);

int main(int argc, char *argv[]) {
    int visualize = 0;
    if (argc > 1) if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--visualize") == 0) visualize = 1; // Enable visualization if -v or --visualize is passed

    int choice;
    printf(MAGENTA "Binary Search\n");
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
        // Note: Using a 2D array for strings, where each string is of fixed length `STRING_LENGTH`.
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

    printf(YELLOW "\n-- Sorting Array --\n" RESET);
    printf("Original Array: " DIM);
    print_array(arr, size, type);
    printf(RESET);

    sort_array(arr, size, type);
    printf("Sorted Array: " DIM);
    print_array(arr, size, type);
    printf(RESET);

    printf(CYAN "\n-- Binary Search --\n" RESET);
    int result = binary_search(arr, size, type, target, visualize);

    switch (type) {
        case 'i':
            if (result != -1)
                printf(GREEN "Integer %d found at index %d" BOLD " (arr[%d] == %d)\n" RESET, *(int*)target, result, result, ((int*)arr)[result]);
            else
                printf(RED "Integer %d not found\n" RESET, *(int*)target);
            break;
        case 'f':
            if (result != -1)
                printf(GREEN "Float %.2f found at index %d" BOLD " (arr[%d] == %.2f)\n" RESET, *(float*)target, result, result, ((float*)arr)[result]);
            else
                printf(RED "Float %.2f not found\n" RESET, *(float*)target);
            break;
        case 'c':
            if (result != -1)
                printf(GREEN "Character '%c' found at index %d" BOLD " (arr[%d] == '%c')\n" RESET, *(char*)target, result, result, ((char*)arr)[result]);
            else
                printf(RED "Character '%c' not found\n" RESET, *(char*)target);
            break;
        case 's':
            if (result != -1)
                printf(GREEN "String \"%s\" found at index %d" BOLD " (arr[%d] == \"%s\")\n" RESET, (char*)target, result, result, ((char(*)[STRING_LENGTH])arr)[result]);
            else
                printf(RED "String \"%s\" not found\n" RESET, (char*)target);
            break;
        default:
            if (result != -1)
                printf(GREEN "Element found at index %d" BOLD " (arr[%d])\n" RESET, result, result);
            else
                printf(RED "Element not found\n" RESET);
    }

    free(arr);
    free(target);
    return 0;
}

/**
 * Performs a binary search on a sorted array of various types.
 *
 * Supported types:
 * - 'i' for int
 * - 'f' for float
 * - 'c' for char
 * - 's' for string (char[STRING_LENGTH]) - `STRING_LENGTH` is defined as 50.
 *
 * @param arr       Pointer to the sorted array.
 * @param size      Number of elements in the array.
 * @param type      Data type of the array elements:
 *                      'i' for int, 'f' for float, 'c' for char, 's' for string (char[STRING_LENGTH]).
 * @param target    Pointer to the target value to search for.
 * @param visualize Flag to enable step-by-step visualization. (1 = enable, 0 = disable)
 * @return          Index of found element, -1 if not found, -2 for unknown type.
 */
int binary_search(void *arr, int size, char type, void *target, int visualize) {
    if (visualize) printf(BOLD "\nStep-by-step search:\n" RESET);

    int start = 0, end = size - 1, step = 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        int cmp = 0;

        if (visualize) {
            printf("Step %d: mid=%d (%d-%d) -> ", step++, mid, start, end);
            print_array_with_range(arr, size, type, start, end, mid);
        }

        switch (type) {
            case 'i': // Integer
                cmp = ((int*)arr)[mid] - *(int*)target;
                break;
            case 'f': // Float
                if (((float*)arr)[mid] < *(float*)target) cmp = -1;
                else if (((float*)arr)[mid] > *(float*)target) cmp = 1;
                else cmp = 0;
                break;
            case 'c': // Character
                cmp = ((char*)arr)[mid] - *(char*)target;
                break;
            case 's': // String
                cmp = strcmp(((char(*)[STRING_LENGTH])arr)[mid], target);
                break;
            default:
                return -2; // Unknown type
        }

        if (cmp == 0 && visualize) printf(GREEN "✓ Match found!\n" RESET);
        else if (cmp < 0 && visualize) printf(BLUE "Target is greater, search right half\n" RESET);
        else if (cmp > 0 && visualize) printf(BLUE "Target is smaller, search left half\n" RESET);

        if (cmp == 0) return mid;
        if (cmp < 0) start = mid + 1; else end = mid - 1;
    }
    return -1; // Element not found
}

/**
 * Prints an array of various types.
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
    print_array_with_range(arr, size, type, -1, -1, -1); // Call with no highlighting
}

/**
 * Prints an array of various types with highlighting for a specific range and mid-point.
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
 * @param left      Left index of the range to highlight. (optional, -1 for no highlight)
 * @param right     Right index of the range to highlight. (optional, -1 for no highlight)
 * @param mid       Index of the mid-point to highlight. (optional, -1 for no highlight)
 * @return          void
 */
void print_array_with_range(void *arr, int size, char type, int left, int right, int mid) {
    printf("[");
    for (int i = 0; i < size; i++) {
        if (i < left || (i > right && right != -1)) printf(DIM);
        else if (i == mid) printf(YELLOW BOLD);
        else if ((i >= left && left != -1) && i <= right) printf(UNDERLINE);

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

        if (left != -1 || right != -1 || mid != -1) printf(RESET);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

/**
 * Bubble Sort
 *
 * Sorts array using bubble sort algorithm.
 *
 * Supported types:
* - 'i' for int
 * - 'f' for float
 * - 'c' for char
 * - 's' for string (char[STRING_LENGTH]) - `STRING_LENGTH` is defined as 50.
 *
 * @param arr   Pointer to the array to sort.
 * @param size  Number of elements in the array.
 * @param type  Data type of the array elements:
 *                  'i' for int, 'f' for float, 'c' for char, 's' for string (char[STRING_LENGTH]).
 * @return      void
 */
void sort_array(void *arr, int size, char type) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            int should_swap = 0;

            switch (type) {
                case 'i':
                case 'f':
                    if (((float*)arr)[j] > ((float*)arr)[j + 1]) {
                        // Swap elements
                        float temp = ((float*)arr)[j];
                        ((float*)arr)[j] = ((float*)arr)[j + 1];
                        ((float*)arr)[j + 1] = temp;
                    }
                    break;
                case 'c':
                    if (((char*)arr)[j] > ((char*)arr)[j + 1]) {
                        // Swap elements
                        char temp = ((char*)arr)[j];
                        ((char*)arr)[j] = ((char*)arr)[j + 1];
                        ((char*)arr)[j + 1] = temp;
                    }
                    break;
                case 's':
                    if (strcmp(((char(*)[STRING_LENGTH])arr)[j], ((char(*)[STRING_LENGTH])arr)[j + 1]) > 0) {
                        // Swap elements
                        char temp[STRING_LENGTH];
                        strcpy(temp, ((char(*)[STRING_LENGTH])arr)[j]);
                        strcpy(((char(*)[STRING_LENGTH])arr)[j], ((char(*)[STRING_LENGTH])arr)[j + 1]);
                        strcpy(((char(*)[STRING_LENGTH])arr)[j + 1], temp);
                    }
                    break;
                default: return;
            }
        }
    }
}
