# Fibonacci Sequence Generator

A recursive Fibonacci sequence generator implementation in C with optional step-by-step visualization and option to change the start point of the sequence.

## Algorithm Description
The Fibonacci sequence is a series of numbers where each number is the sum of the two preceding ones. The sequence typically starts with 1 and 1: 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...

## Features

- **Recursive implementation**: Uses mathematical recursion for calculation
- **Command-line support**: Accept parameters as command-line arguments
- **Interactive input**: Prompts for input if not provided via command line
- **Visualization**: Optional step-by-step calculation breakdown with `-v` flag
- **Error handling**: Validates input for negative numbers
- **Overflow warning**: Alerts users for potentially large results
- **Set start point**: Allows to skip nth first numbers in the sequence
- **Flexible input**: Support for single number (count) or two (start-count) generation

## Algorithm Complexity

### Time Complexity
- **Best Case**: $O(1)$ - For n = 0 or n = 1
- **Average/Worst Case**: $O(2^n)$ - Exponential due to overlapping subproblems

### Space Complexity
- $O(n)$ - Recursive call stack depth

## Mathematical Definition
- $F(0) = 0$ (base case)
- $F(1) = 1$ (base case)  
- $F(n) = F(n-1) + F(n-2)$ for $n > 1$ (recursive case)

## How to Use

1. **Compile the program**:
   ```bash
   gcc -o fibonacci fibonacci.c
   ```

2. **Run the program**:
   ```bash
   # Interactive mode
   ./fibonacci
   
   # Fibonacci sequence for 10 numbers
   ./fibonacci 10
   
   # Fibonacci sequence for 10 numbers starting from 5th number (can use any number separator)
   ./fibonacci 5:10
   
   # With visualization
   ./fibonacci -v 7
   ./fibonacci 3:6 -v
   ```

3. **Follow the prompts** (if running interactively):
    - Enter a single number count only or two numbers for start and count
    - Use space or any separator between numbers (e.g., `5:10`, `5 10`, `5,10`)

## Example Usage

### Only with Count Number
```
Fibonacci Sequence Generator
============================
Enter how many elements in the sequence to generate (count), or a start point and a count (start:count): 10

-- Fibonacci Sequence (from 1, 10 elements)--
Generating sequence F(1) to F(10)! recursively...

Fibonacci Sequence: [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
```

### Start and Count Numbers
```
Fibonacci Sequence Generator
============================
Enter how many elements in the sequence to generate (count), or a start point and a count (start:count): 5:10

-- Fibonacci Sequence (from 5, 10 elements)--
Generating sequence F(5) to F(14)! recursively...

Fibonacci Sequence: [5, 8, 13, 21, 34, 55, 89, 144, 233, 377]
```

### With Visualization
```
Fibonacci Sequence Generator
============================
Enter how many elements in the sequence to generate (count), or a start point and a count (start:count): 7

-- Fibonacci Sequence (from 1, 7 elements)--
Generating sequence F(1) to F(7)! recursively...

Step by Step:
F(1) = 0+0 = 1
F(2) = 1+0 = 1
F(3) = 1+1 = 2
F(4) = 2+1 = 3
F(5) = 3+2 = 5
F(6) = 5+3 = 8
F(7) = 8+5 = 13

Fibonacci Sequence: [1, 1, 2, 3, 5, 8, 13]
```

## Implementation Details

- **Recursive approach**: Uses mathematical definition directly
- **Base cases**: Handles F(0) = 0 and F(1) = 1
- **Input validation**: Checks for negative numbers
- **Flexible parsing**: Supports various input formats
- **Command-line parsing**: Handles multiple argument combinations
- **Visual formatting**: Shows step-by-step calculation when `-v` flag is used

### Function Documentation

#### `fibonacci(int n)`
Calculates nth Fibonacci number using recursion.

**Parameters**:
- `n`: Non-negative integer position in sequence

**Returns**: `long long` - The nth Fibonacci number

#### `generate_fibonacci_sequence(int start, int count, long long *sequence)`
Generates a Fibonacci sequence starting from `start` for `count` elements.

**Parameters**:
- `start`: Starting position in the Fibonacci sequence
- `count`: Number of elements to generate
- `sequence`: Pointer to an array to store the generated sequence

**Returns**: void

#### `print_fibonacci_steps(int n, int original_n)`
Prints step-by-step Fibonacci calculation breakdown.

**Parameters**:
- `n`: Current number in recursion
- `original_n`: Original number for proper formatting

**Returns**: void

#### `parse_input(char *input, int *start, int *count)`
Parses input string to extract start and count values.

**Parameters**:
- `input`: Input string containing start and count
- `start`: Pointer to store start value
- `count`: Pointer to store count value

**Returns**: `int` - 1 if one number is provided, 2 if two numbers are provided, 0 if parsing fails

## Command Line Options

- `-v`: Enable step-by-step visualization
- `<number>`: Generate Fibonacci sequence for `number` elements
- `<n1:n2>`: Generate Fibonacci sequence for `n2` elements, starting from `n1`

## Limitations

- **Performance**: Exponential time complexity makes large numbers slow
- **Overflow**: Results larger than `long long` will overflow
- **Recommended limit**: Numbers ≤ 40 for reasonable performance
- **Memory**: Deep recursion may cause stack overflow

## Mathematical Properties

- **Golden Ratio**: $\lim_{n \to \infty} \frac{F(n+1)}{F(n)} = \phi = \frac{1+\sqrt{5}}{2}$
- **Binet's Formula**: $F(n) = \frac{\phi^n - \psi^n}{\sqrt{5}}$ where $\psi = \frac{1-\sqrt{5}}{2}$
- **Growth Rate**: Exponential growth approximately $\phi^n$

## Optimization Notes

This implementation uses naive recursion for educational purposes. For production use, consider:
- **Memoization**: Store calculated values to avoid recomputation
- **Dynamic Programming**: Bottom-up approach with $O(n)$ time
- **Matrix Exponentiation**: $O(\log n)$ time complexity
- **Iterative approach**: $O(n)$ time, $O(1)$ space

## Use Cases

- **Mathematical education**: Teaching recursion and sequence concepts
- **Algorithm analysis**: Understanding exponential complexity
- **Pattern recognition**: Natural phenomena modeling
- **Computer graphics**: Spiral and geometric patterns

## License

MIT License - see [LICENSE](/LICENSE) file for details
