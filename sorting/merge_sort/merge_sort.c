//
// Created by Dany on 07/25/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Merge Sort Implementation in C
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50

void merge_sort(void *arr, int left, int right, char type, int *step, int visualize);
void print_array(void *arr, int size, char type);
void print_array_with_range(void *arr, int size, char type, int left, int right, int mid);

int main(int argc, char *argv[]) {
    int visualize = 0;
    if (argc > 1) if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--visualize") == 0) visualize = 1; // Enable visualization if -v or --visualize is passed

    int choice;
    printf(MAGENTA "Merge Sort\n");
    printf("==========\n" RESET);
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

    printf(CYAN "\n-- Merge Sort --\n" RESET);

    printf(YELLOW "\n-- Original Array\n" RESET DIM);
    print_array(arr, size, type);
    printf(RESET);

    printf(DIM "Sorting...\n" RESET);
    if (visualize) printf(BOLD "\nStep-by-step sorting:\n" RESET);
    int step = 1;
    merge_sort(arr, 0, size - 1, type, &step, visualize);

    printf(GREEN "\n-- Sorted Array\n" RESET BOLD);
    print_array(arr, size, type);
    printf(RESET);

    free(arr);
    return 0;
}

/**
 * Performs merge sort on an array of various types.
 *
 * Supported types:
 * - 'i' for int
 * - 'f' for float
 * - 'c' for char
 * - 's' for string (char[STRING_LENGTH]) - `STRING_LENGTH` is defined as 50.
 *
 * @param arr       Pointer to the array to sort.
 * @param left      Left boundary of the subarray.
 * @param right     Right boundary of the subarray.
 * @param type      Data type of the array elements:
 *                      'i' for int, 'f' for float, 'c' for char, 's' for string (char[STRING_LENGTH]).
 * @param step      Pointer to step counter for visualization.
 * @param visualize Flag to enable step-by-step visualization. (1 = enable, 0 = disable)
 * @return          void
 */
void merge_sort(void *arr, int left, int right, char type, int *step, int visualize) {

    if (left < right) {
        int mid = left + (right - left) / 2;

        if (visualize) {
            printf(CYAN "Step %d: Dividing array [%d-%d] at mid=%d -> " RESET, (*step)++, left, right, mid);
            print_array_with_range(arr, right + 1, type, left, right, mid);
        }

        // Recursively sort first and second halves
        merge_sort(arr, left, mid, type, step, visualize);
        merge_sort(arr, mid + 1, right, type, step, visualize);

        // Merge the sorted halves (inline)
        int n1 = mid - left + 1;
        int n2 = right - mid;
        void *left_arr = NULL, *right_arr = NULL; // Create temporary arrays

        switch (type) {
            case 'i':
            case 'f':
                left_arr = malloc(n1 * sizeof(float));
                right_arr = malloc(n2 * sizeof(float));
                for (int i = 0; i < n1; i++)
                    ((float*)left_arr)[i] = ((float*)arr)[left + i];
                for (int j = 0; j < n2; j++)
                    ((float*)right_arr)[j] = ((float*)arr)[mid + 1 + j];
                break;
            case 'c':
                left_arr = malloc(n1 * sizeof(char));
                right_arr = malloc(n2 * sizeof(char));
                for (int i = 0; i < n1; i++)
                    ((char*)left_arr)[i] = ((char*)arr)[left + i];
                for (int j = 0; j < n2; j++)
                    ((char*)right_arr)[j] = ((char*)arr)[mid + 1 + j];
                break;
            case 's':
                left_arr = malloc(n1 * STRING_LENGTH * sizeof(char));
                right_arr = malloc(n2 * STRING_LENGTH * sizeof(char));
                for (int i = 0; i < n1; i++)
                    strcpy(((char(*)[STRING_LENGTH])left_arr)[i], ((char(*)[STRING_LENGTH])arr)[left + i]);
                for (int j = 0; j < n2; j++)
                    strcpy(((char(*)[STRING_LENGTH])right_arr)[j], ((char(*)[STRING_LENGTH])arr)[mid + 1 + j]);
                break;
            default:
                return;
        }

        if (visualize) {
            printf(BLUE "Step %d: Merging subarrays [%d-%d] and [%d-%d] -> " RESET, (*step)++, left, mid, mid + 1, right);
            print_array_with_range(arr, right + 1, type, left, right, -1);
        }

        // Merge the temporary arrays back into arr[left..right]
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            int should_take_left = 0;
            switch (type) {
                case 'i':
                case 'f':
                    should_take_left = (((float*)left_arr)[i] <= ((float*)right_arr)[j]);
                    if (should_take_left)
                        ((float*)arr)[k] = ((float*)left_arr)[i++];
                    else
                        ((float*)arr)[k] = ((float*)right_arr)[j++];
                    break;
                case 'c':
                    should_take_left = (((char*)left_arr)[i] <= ((char*)right_arr)[j]);
                    if (should_take_left)
                        ((char*)arr)[k] = ((char*)left_arr)[i++];
                    else
                        ((char*)arr)[k] = ((char*)right_arr)[j++];
                    break;
                case 's':
                    should_take_left = (strcmp(((char(*)[STRING_LENGTH])left_arr)[i], ((char(*)[STRING_LENGTH])right_arr)[j]) <= 0);
                    if (should_take_left)
                        strcpy(((char(*)[STRING_LENGTH])arr)[k], ((char(*)[STRING_LENGTH])left_arr)[i++]);
                    else
                        strcpy(((char(*)[STRING_LENGTH])arr)[k], ((char(*)[STRING_LENGTH])right_arr)[j++]);
                    break;
                default:
                    return;
            }
            k++;
        }
        while (i < n1) {
            switch (type) {
                case 'i': ((int*)arr)[k] = ((int*)left_arr)[i]; break;
                case 'f': ((float*)arr)[k] = ((float*)left_arr)[i]; break;
                case 'c': ((char*)arr)[k] = ((char*)left_arr)[i]; break;
                case 's': strcpy(((char(*)[STRING_LENGTH])arr)[k], ((char(*)[STRING_LENGTH])left_arr)[i]); break;
                default: return;
            }
            i++; k++;
        }
        while (j < n2) {
            switch (type) {
                case 'i': ((int*)arr)[k] = ((int*)right_arr)[j]; break;
                case 'f': ((float*)arr)[k] = ((float*)right_arr)[j]; break;
                case 'c': ((char*)arr)[k] = ((char*)right_arr)[j]; break;
                case 's': strcpy(((char(*)[STRING_LENGTH])arr)[k], ((char(*)[STRING_LENGTH])right_arr)[j]); break;
                default: return;
            }
            j++; k++;
        }

        if (visualize) {
            printf(GREEN "    ✓ Merged -> " RESET);
            print_array_with_range(arr, right + 1, type, left, right, -1);
        }

        free(left_arr);
        free(right_arr);
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
