# Bogo Sort

A generic bogo sort implementation in C that supports multiple data types including integers, floats, characters, and strings with optional visualization.

## Algorithm Description
Bogo sort (also known as permutation sort, stupid sort, or monkey sort) is a highly inefficient sorting algorithm that works by randomly shuffling the array until it happens to be in sorted order. It's primarily used for educational purposes to demonstrate how NOT (or no not) to sort data.

## Features

- **Multi-type support**: Sort arrays of integers, floats, characters, or strings
- **User input**: Interactive program that accepts user-defined arrays
- **Generic implementation**: Uses void pointers for type-agnostic sorting
- **Memory management**: Proper dynamic memory allocation and cleanup
- **Fisher-Yates shuffle**: Uses proper random shuffling algorithm
- **Safety limits**: Maximum shuffle limit to prevent infinite loops
- **Warning system**: Alerts users about inefficiency for larger arrays
- **Visualization**: Optional step-by-step sorting visualization with `-v` or `--visualize` flag
- **Colored output**: Uses ANSI color codes for enhanced user experience (`ansi_colors.h`)

### Supported Data Types

1. **Integers** (`int`)
2. **Floats** (`float`)
3. **Characters** (`char`)
4. **Strings** (`char[STRING_LENGTH]`) - `#define STRING_LENGTH 50`

## Algorithm Complexity

### Time Complexity
- **Best Case**: $O(n)$, $\Omega(n)$ - Array is already sorted (just check)
- **Average Case**: $O(n!)$, $\Theta(n!)$ - Expected number of permutations
- **Worst Case**: $O(\infty)$ - Theoretically unbounded (may never terminate)

### Space Complexity
- $O(1)$ - In-place sorting algorithm, only uses constant extra space

## How it Works

1. **Check** if the array is already sorted
2. If not sorted, **randomly shuffle** the entire array
3. **Repeat** steps 1-2 until the array becomes sorted
4. **Terminate** when sorted or maximum shuffle limit reached

The algorithm relies purely on chance and has no intelligent strategy for sorting.

## How to Use

1. **Compile the program**:
   ```bash
   gcc -o bogo_sort bogo_sort.c
   ```

2. **Run the program**:
   ```bash
   # Normal execution
   ./bogo_sort

   # With visualization
   ./bogo_sort -v
   ./bogo_sort --visualize
   ```

3. **Follow the prompts**:
   - Choose data type (1-4)
   - Enter array size (recommended ≤ 5)
     - If larger, a warning will be displayed - `Continue... (y/n)`
   - Input array elements

## Example Usage

### Normal Execution
```
Bogo Sort
=========
⚠  WARNING: Bogo Sort is extremely inefficient! Use small arrays only.
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size (recommended ≤ 5): 5
Enter 5 integers: 3 2 8 13 5

-- Bogo Sort --

-- Original Array
[3, 2, 8, 13, 5]
Sorting...
   ✓ Array sorted after 1 shuffle!

-- Sorted Array
[2, 3, 5, 8, 13]
```

### With Visualization
```
Bogo Sort
=========
Visualization enabled.
⚠  WARNING: Bogo Sort is extremely inefficient! Use small arrays only.
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size (recommended ≤ 5): 5
Enter 5 integers: 3 2 8 13 5

-- Bogo Sort --

-- Original Array
[3, 2, 8, 13, 5]
Sorting...

Step-by-step sorting:
Shuffle 1: [2, 3, 5, 8, 13]
    ✓ SORTED!
  ✓ Array sorted after 1 shuffle!

-- Sorted Array
[2, 3, 5, 8, 13]
```

## Implementation Details

- Uses `void*` pointers for generic array handling
- Dynamic memory allocation with `malloc()`
- Fisher-Yates shuffle algorithm for proper randomization
- Type-specific comparison for sorted checking
- String comparison using `strcmp()` for string arrays
- String copying using `strcpy()` for string operations
- Maximum shuffle limit (`MAX_SHUFFLES = 1,000,000`) to prevent infinite loops
- Progress reporting for long-running sorts
- Warning system for arrays larger than recommended size
- Command-line argument parsing for visualization mode

### Include & Define Statements

```c
#include <stdio.h>    // Standard input/output functions (printf, scanf)
#include <stdlib.h>   // Memory allocation functions (malloc, free)
#include <string.h>   // String manipulation functions (strcmp, strcpy)
#include <time.h>     // Time functions for random seed (time, srand)
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50     // Maximum length for string elements in arrays
#define MAX_SHUFFLES 1000000 // Maximum number of shuffle attempts before giving up
```

### Function Documentation

#### `bogo_sort(void *arr, int size, char type, int visualize)`
Performs bogo sort by randomly shuffling until array is sorted.

**Parameters**:
- `arr`: Pointer to the array to sort
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `visualize`: Flag to enable step-by-step visualization (1 = enable, 0 = disable)

**Returns**: void

#### `is_sorted(void *arr, int size, char type, char order)`
Checks if an array is sorted in ascending order.

**Parameters**:
- `arr`: Pointer to the array to check
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `order`: Sort order ('a' for ascending, 'd' for descending)

**Returns**: 1 if sorted, 0 if not sorted

#### `shuffle_array(void *arr, int size, char type)`
Randomly shuffles array using Fisher-Yates algorithm.

**Parameters**:
- `arr`: Pointer to the array to shuffle
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')

**Returns**: void

#### `print_array(void *arr, int size, char type)`
Prints an array in a formatted manner.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')

**Returns**: void

## Command Line Options

- `-v`, `--visualize`: Enable step-by-step sorting visualization

## Advantages/Disadvantages

### Advantages
- **First attempt**: Can gess the correct order on the first try
- **Simple to understand**: Conceptually the simplest sorting algorithm
- **Minimal code**: Very few lines of implementation
- **In-place**: Requires only constant extra space
- **Educational value**: Perfect example of what NOT to do (or do? 😅)

### Disadvantages
- **Extremely inefficient**: Worst possible time complexity
- **Unpredictable runtime**: May never finish for large arrays
- **Not practical**: Should never be used in production
- **Poor scalability**: Becomes unusable with even small increases in array size

### Comparison with Other Algorithms

| Algorithm      | Best Case     | Average Case  | Worst Case    | Space  |
|----------------|---------------|---------------|---------------|--------|
| Bogo Sort      | $O(n)$        | $O((n+1)!)$   | $O(\infty)$   | $O(1)$ |
| Bubble Sort    | $O(n)$        | $O(n^2)$      | $O(n^2)$      | $O(1)$ |
| Selection Sort | $O(n^2)$      | $O(n^2)$      | $O(n^2)$      | $O(1)$ |
| Merge Sort     | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ |

## Use Cases

- **Educational purposes**: Teaching algorithm efficiency concepts
- **Demonstrating bad algorithms**: Example of how NOT to solve problems
- **Humor/Entertainment**: Programming jokes and demonstrations
- **Theoretical computer science**: Worst-case algorithm analysis
- **Never for production**: Absolutely not suitable for real applications

## Fun Facts

- Also known as "Monkey Sort" (infinite monkeys theorem reference)
- Average case is $(n)!$ shuffles, which grows exponentially
- It's technically a valid sorting algorithm, just an extremely bad one (or good one? 🙄)
- Sometimes used in humor to demonstrate the importance of algorithm choice

## License

MIT License - see [LICENSE](/LICENSE) file for details
