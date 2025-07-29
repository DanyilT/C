//
// Created by Dany on 07/25/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Recursive Fibonacci Sequence Generator in C
//

#include <stdio.h>
#include <stdlib.h>

long long fibonacci(int n);
void generate_fibonacci_sequence(int start, int count, long long *sequence);
void print_fibonacci_steps(long long *sequence, int start, int count);
int parse_input(char *input, int *start, int *count);

int main(int argc, char *argv[]) {
    int start = 1, count = -1;
    int visualize = 0;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'v') {
            visualize = 1;
        } else {
            // Try to parse as number(s)
            parse_input(argv[i], &start, &count);
        }
    }

    printf("Fibonacci Sequence Generator\n");
    printf("============================\n");

    // If no count provided via command line, prompt user
    if (count == -1) {
        printf("Enter how many elements in the sequence to generate (count), or a start point and a count (start:count): ");
        char *input = malloc(2 * sizeof(int) + sizeof(char));
        scanf("%s", input);
        if (parse_input(input, &start, &count) == 0) {
            printf("Error: Invalid input format! Use 'start-count' or 'start:count' for using start point, or just 'number' for Fibonacci sequence with start from first element (1, 1, 2, ...).\n");
            return 1;
        }
        free(input);
    }

    if (count > 50) {
        printf("⚠ Warning: Large positions may cause overflow.\n");
    }

    printf("\n-- Fibonacci Sequence (from %d, %d elements)--\n", start, count);
    if (count == 1) {
        printf("Calculating F(%d)! recursively...\n", start);
    } else {
        printf("Generating sequence F(%d) to F(%d)! recursively...\n", start, start + count - 1);
    }

    // Allocate memory for sequence
    long long *sequence = malloc(count * sizeof(long long));
    if (sequence == NULL) {
        printf("Error: Memory allocation failed!\n");
        return 1;
    }

    // Generate the sequence
    generate_fibonacci_sequence(start, count, sequence);

    // Print step-by-step calculations if requested
    if (visualize) print_fibonacci_steps(sequence, start, count);

    // Print the final sequence
    printf("\nFibonacci Sequence: [");
    for (int i = 0; i < count; i++) {
        printf("%lld", sequence[i]);
        if (i < count - 1) printf(", ");
    }
    printf("]\n");

    // Cleanup
    free(sequence);

    return 0;
}

/**
 * Calculates the nth Fibonacci number using recursion.
 * F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)
 *
 * @param n The position in the Fibonacci sequence
 * @return  The nth Fibonacci number
 */
long long fibonacci(int n) {
    // Base cases
    if (n == 0) return 0;
    if (n == 1) return 1;

    // Recursive case: F(n) = F(n-1) + F(n-2)
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/**
 * Generates a Fibonacci sequence using recursion and stores it in an array.
 *
 * @param start     Starting position in the sequence
 * @param count     Number of elements to generate
 * @param sequence  Array to store the generated sequence
 */
void generate_fibonacci_sequence(int start, int count, long long *sequence) {
    if (count <= 0) return;
    sequence[0] = fibonacci(start);
    generate_fibonacci_sequence(start + 1, count - 1, sequence + 1);
}

/**
 * Prints the generated Fibonacci sequence.
 *
 * @param sequence Array containing the Fibonacci numbers
 * @param start    Starting position in the sequence
 * @param count    Number of elements in the sequence
 */
void print_fibonacci_steps(long long *sequence, int start, int count) {
    if (count == 1) {
        printf("\nF(%d) = %lld\n", start, sequence[0]);
    } else {
        printf("\nStep by Step:\n");
        for (int i = 0; i < count; i++) {
            printf("F(%d) = %lld+%lld = %lld\n", start + i, i > 0 ? sequence[i - 1] : 0, i > 1 ? sequence[i - 2] : 0, sequence[i]);
        }
    }
}

/**
 * Parse a start and count from string input (formats: "start-count", "start:count", etc.).
 * Or parse a single number (format: "number").
 *
 * @param input String containing range
 * @param start Pointer to store start value
 * @param count Pointer to store count value
 * @return      1 if single number parsed, 2 if range parsed, 0 if invalid
 */
int parse_input(char *input, int *start, int *count) {
    int n1 = -1, n2 = -1;

    // Try to parse two-integer separated by any non-digit character (e.g., space, colon, dash)
    if (sscanf(input, "%d%*[^0-9]%d", &n1, &n2) == 2) {
        if (n1 >= 0 && n2 >= 0) {
            *start = n1;
            *count = n2;
            return 2;
        }
    }

    // Try to parse single integer (set count, leave start unchanged)
    if (sscanf(input, "%d", &n1) == 1 && n1 >= 0) {
        *count = n1;
        return 1;
    }

    return 0;
}
