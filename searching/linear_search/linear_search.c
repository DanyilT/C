//
// Created by Dany on 07/24/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Linear Search Implementation in C
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50

int linear_search(void *arr, int size, char type, void *target);
void print_array(void *arr, int size, char type);

int main() {
    int choice;
    printf("Linear Search\n");
    printf("=============\n");
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
            printf("Invalid choice!\n");
            return 1;
    }

    printf(CYAN "\n-- Search --\n" RESET);
    printf("Array: " DIM);
    print_array(arr, size, type);
    printf(RESET);

    int result = linear_search(arr, size, type, target);
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
 * Performs a linear search on an array of various types.
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
 * @return          Index of the found element, -1 if not found, -2 for unknown type.
 */
int linear_search(void *arr, int size, char type, void *target) {
    for (int i = 0; i < size; i++) {
        switch (type) {
            case 'i': // Integer
                if (((int *)arr)[i] == *(int *)target) return i; // Return index of found element
                break;
            case 'f': // Float
                if (((float *)arr)[i] == *(float *)target) return i; // Return index of found element
                break;
            case 'c': // Character
                if (((char *)arr)[i] == *(char *)target) return i; // Return index of found element
                break;
            case 's': // String
                if (strcmp(((char (*)[STRING_LENGTH])arr)[i], target) == 0) return i; // Return index of found element
                break;
            default:
                return -2; // Unknown type
        }
    }
    return -1;  // Element not found
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
