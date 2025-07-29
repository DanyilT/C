//
// Created by Dany on 07/25/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// Recursive Factorial Calculator in C
//

#include <stdio.h>
#include <stdlib.h>

long long factorial(int n);
void print_factorial_steps(int n, int original_n);

int main(int argc, char *argv[]) {
    int number = -1;
    int visualize = 0;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'v') {
            visualize = 1;
        } else {
            // Try to parse as number
            char *endptr;
            int parsed = (int) strtol(argv[i], &endptr, 10);
            if (*endptr == '\0' && parsed >= 0) number = parsed;
        }
    }

    printf("Factorial Calculator\n");
    printf("====================\n");

    // If number not provided via command line, prompt user
    if (number == -1) {
        printf("Enter a non-negative integer: ");
        scanf("%d", &number);

        if (number < 0) {
            printf("Error: Factorial is not defined for negative numbers!\n");
            return 1;
        }
    }

    if (number > 20) {
        printf("⚠ Warning: Large numbers may cause overflow.\n");
    }

    printf("\n-- Factorial of %d --\n", number);
    printf("Calculating %d! recursively...\n", number);

    if (visualize) print_factorial_steps(number, number);

    long long result = factorial(number);
    printf("\n%d! = %lld\n", number, result);

    return 0;
}

/**
 * Calculates factorial of n using recursion.
 *
 * @param n The number to calculate factorial for
 * @return  The factorial of n
 */
long long factorial(int n) {
    // Base case: 0! = 1, 1! = 1
    if (n <= 1) return 1;

    // Recursive case: n! = n * (n-1)!
    return n * factorial(n - 1);
}

/**
 * Prints the step-by-step breakdown of factorial calculation.
 *
 * @param n The current number in recursion
 * @param original_n The original number for formatting
 */
void print_factorial_steps(int n, int original_n) {
    // Print indentation based on recursion depth
    for (int i = 0; i < (original_n - n); i++) {
        printf("  ");
    }

    if (n <= 1) {
        printf("%d! = 1\n", n);
        return;
    }

    printf("%d! = %d × %d!\n", n, n, n - 1);
    print_factorial_steps(n - 1, original_n);

    // Print the return value on the way back up
    for (int i = 0; i < (original_n - n); i++) {
        printf("  ");
    }
    printf("↳%d! = %lld\n", n, factorial(n));
}
