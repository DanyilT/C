# Linear Search

A generic linear search implementation in C that supports multiple data types including integers, floats, characters, and strings.

## Algorithm Description
Linear search checks every element in the array sequentially until the target element is found or the entire array is traversed.

## Features

- **Multi-type support**: Search through arrays of integers, floats, characters, or strings
- **User input**: Interactive program that accepts user-defined arrays and search targets
- **Generic implementation**: Uses void pointers for type-agnostic searching
- **Memory management**: Proper dynamic memory allocation and cleanup

### Supported Data Types

1. **Integers** (`int`)
2. **Floats** (`float`)
3. **Characters** (`char`)
4. **Strings** (`char[STRING_LENGTH]`) - `#define STRING_LENGTH 50` 

## Algorithm Complexity

### Time Complexity
- **Best Case**: $O(1)$, $\Omega(1)$ - Element found at first position
- **Average Case**: $O(n)$, $\Theta(n)$- Element found in middle
- **Worst Case**: $O(n)$ - Element not found or at last position

### Space Complexity
- $O(1)$ - Only uses constant extra space

## How it Works

1. Start from the first element
2. Compare each element with the target
3. If match found, return the index
4. If end of array reached without match, return -1

## How to Use

1. **Compile the program**:
   ```bash
   gcc -o linear_search linear_search.c
   ```

2. **Run the program**:
   ```bash
   ./linear_search
   ```

3. **Follow the prompts**:
    - Choose data type (1-4)
    - Enter array size
    - Input array elements
    - Enter target element to search

## Example Usage

- Array: [64, 34, 25, 12, 22, 11, 90]
- Target: 22
- Result: Found at index 4

```
Linear Search
=============
Choose data type:
1. Integers
2. Floats  
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 5
Enter 5 integers: 2 3 5 8 13
Enter target integer: 8

-- Search --
Array: [2, 3, 5, 8, 13]
Integer 8 found at index 3 (arr(3) == 8)
```

## Implementation Details

- Uses `void*` pointers for generic array handling
- Dynamic memory allocation with `malloc()`
- Proper type casting for different data types
- String comparison using `strcmp()` for string arrays
- Input buffer clearing to handle multiple inputs

### Include & Define Statements

```c
#include <stdio.h>    // Standard input/output functions (printf, scanf)
#include <stdlib.h>   // Memory allocation functions (malloc, free)
#include <string.h>   // String manipulation functions (strcmp)
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50  // Maximum length for string elements in arrays
```

### Function Documentation

#### `linear_search(void *arr, int size, char type, void *target)`
Performs linear search on an array of specified type.

**Parameters**:
- `arr`: Pointer to the array to search
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `target`: Pointer to the target value

**Returns**: Index of found element, -1 if not found, -2 for unknown type

#### `print_array(void *arr, int size, char type)`
Prints an array in a formatted manner.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')

## License

MIT License - see [LICENSE](/LICENSE) file for details
