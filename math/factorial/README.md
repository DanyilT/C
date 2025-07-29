# Factorial Calculator

A recursive factorial calculator implementation in C with optional step-by-step visualization.

## Algorithm Description
Factorial calculates the product of all positive integers less than or equal to a given number. Mathematically, n! = n × (n-1) × (n-2) × ... × 2 × 1, with 0! = 1 by definition.

## Features

- **Recursive implementation**: Uses mathematical recursion for calculation
- **Command-line support**: Accept number as command-line argument
- **Interactive input**: Prompts for input if not provided via command line
- **Visualization**: Optional step-by-step calculation breakdown with `-v` flag
- **Error handling**: Validates input for negative numbers
- **Overflow warning**: Alerts users for potentially large results

## Algorithm Complexity

### Time Complexity
- **Best Case**: $O(1)$ - For n = 0 or n = 1
- **Average/Worst Case**: $O(n)$ - Linear recursive calls

### Space Complexity
- $O(n)$ - Recursive call stack depth

## Mathematical Definition
- $0! = 1$ (base case)
- $1! = 1$ (base case)
- $n! = n \times (n-1)!$ for $n > 1$ (recursive case)

## How to Use

1. **Compile the program**:
   ```bash
   gcc -o factorial factorial.c
   ```

2. **Run the program**:
   ```bash
   # Interactive mode
   ./factorial
   
   # With command-line argument
   ./factorial 5
   
   # With visualization
   ./factorial -v 5
   ./factorial 5 -v
   ```

3. **Follow the prompts** (if running interactively):
    - Enter a non-negative integer

## Example Usage

### Normal Execution
```
Factorial Calculator
====================
Enter a non-negative integer: 5

-- Factorial of 5 --
Calculating 5! recursively...

5! = 120
```

### With Visualization
```
Factorial Calculator
====================

-- Factorial of 5 --
Calculating 5! recursively...
5! = 5 × 4!
  4! = 4 × 3!
    3! = 3 × 2!
      2! = 2 × 1!
        1! = 1
      ↳2! = 2
    ↳3! = 6
  ↳4! = 24
↳5! = 120

5! = 120
```

## Implementation Details

- **Recursive approach**: Uses mathematical definition directly
- **Base cases**: Handles 0! = 1 and 1! = 1
- **Input validation**: Checks for negative numbers
- **Overflow protection**: Warns for numbers > 20
- **Command-line parsing**: Supports flexible argument order
- **Visual formatting**: Indented output shows recursion depth when `-v` flag is used

### Function Documentation

#### `factorial(int n)`
Calculates factorial using recursion.

**Parameters**:
- `n`: Non-negative integer to calculate factorial for

**Returns**: `long long` - The factorial of n

#### `print_factorial_steps(int n, int original_n)`
Prints step-by-step factorial calculation breakdown.

**Parameters**:
- `n`: Current number in recursion
- `original_n`: Original number for proper indentation

**Returns**: void

## Command Line Options

- `-v`: Enable step-by-step visualization
- `<number>`: Calculate factorial of specified number

## Limitations

- **Overflow**: Results larger than `long long` will overflow
- **Recommended limit**: Numbers ≤ 20 for reliable results
- **Memory**: Deep recursion may cause stack overflow for very large inputs

## Mathematical Properties

- $n! = n \times (n-1)!$
- $0! = 1$ by definition
- Growth rate: $n!$ grows faster than exponential functions
- Stirling's approximation: $n! \approx \sqrt{2\pi n} \left(\frac{n}{e}\right)^n$

## Use Cases

- **Mathematical calculations**: Computing permutations and combinations
- **Educational purposes**: Teaching recursion concepts
- **Probability theory**: Calculating arrangements and distributions
- **Algorithm analysis**: Understanding factorial growth rates

## License

MIT License - see [LICENSE](/LICENSE) file for details
