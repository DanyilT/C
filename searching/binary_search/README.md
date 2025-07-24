# Binary Search

A generic binary search implementation in C that supports multiple data types including integers, floats, characters, and strings with automatic sorting and optional visualization.

## Algorithm Description
Binary search efficiently finds a target element in a sorted array by repeatedly dividing the search interval in half. If the target value is less than the middle element, it searches the left half; otherwise, it searches the right half.

## Features

- **Multi-type support**: Search through arrays of integers, floats, characters, or strings
- **Automatic sorting**: Uses ___Bubble Sort___ to ensure array is sorted before searching
- **User input**: Interactive program that accepts user-defined arrays and search targets
- **Generic implementation**: Uses void pointers for type-agnostic searching
- **Memory management**: Proper dynamic memory allocation and cleanup
- **Visualization**: Optional step-by-step search visualization with `-v` or `--visualize` flag
- **Colored output**: Uses ANSI color codes for enhanced user experience (`ansi_colors.h`)

### Supported Data Types

1. **Integers** (`int`)
2. **Floats** (`float`)
3. **Characters** (`char`)
4. **Strings** (`char[STRING_LENGTH]`) - `#define STRING_LENGTH 50`

## Algorithm Complexity

### Time Complexity
- **Best Case**: $O(1)$, $\Omega(1)$ - Element found at middle position
- **Average Case**: $O(\log n)$, $\Theta(\log n)$ - Element found after several divisions
- **Worst Case**: $O(\log n)$ - Element not found or at boundary

### Space Complexity
- $O(1)$ - Only uses constant extra space (iterative implementation)

## How it Works

1. **Sort the array** (using ___bubble sort___)
2. **Initialize** start = 0, end = size - 1
3. **Calculate** middle index: mid = start + (end - start) / 2
4. **Compare** middle element with target:
   - If equal: return middle index
   - If target is smaller: search start half (end = mid - 1)
   - If target is larger: search end half (start = mid + 1)
5. **Repeat** until element found or search space exhausted

## How to Use

1. **Compile the program**:
   ```bash
   gcc -o binary_search binary_search.c
   ```

2. **Run the program**:
   ```bash
   # Normal execution
   ./binary_search
   
   # With visualization
   ./binary_search -v
   ./binary_search --visualize
   ```

3. **Follow the prompts**:
   - Choose data type (1-4)
   - Enter array size
   - Input array elements
   - Enter target element to search

## Example Usage

### Normal Execution
```
Binary Search
=============
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 7
Enter 7 integers: 2 3 5 8 13 1 1
Enter target integer: 8

-- Sorting Array --
Original Array: [2, 3, 5, 8, 13, 1, 1]
Sorted Array: [1, 1, 2, 3, 5, 8, 13]

-- Binary Search --
Integer 8 found at index 5 (arr[5] == 8)
```

### With Visualization
```
Binary Search
=============
Visualization enabled
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 7
Enter 7 integers: 2 3 5 8 13 1 1
Enter target integer: 8

-- Sorting Array --
Original Array: [2, 3, 5, 8, 13, 1, 1]
Sorted Array: [1, 1, 2, 3, 5, 8, 13]

-- Binary Search --

Step-by-step search:
Step 1: mid=3 (0-6) -> [1, 1, 2, 3, 5, 8, 13]
Target is greater, search right half
Step 2: mid=5 (4-6) -> [1, 1, 2, 3, 5, 8, 13]
✓ Match found!
Integer 8 found at index 5 (arr[5] == 8)
```

## Implementation Details

- **Prerequisite**: Array must be sorted (automatically sorted using ___bubble sort___)
- Uses `void*` pointers for generic array handling
- Dynamic memory allocation with `malloc()`
- Proper type casting for different data types
- String comparison using `strcmp()` for string arrays
- Input buffer clearing to handle multiple inputs
- Command-line argument parsing for visualization mode
- ANSI color codes for enhanced visual feedback

### Include & Define Statements

```c
#include <stdio.h>    // Standard input/output functions (printf, scanf)
#include <stdlib.h>   // Memory allocation functions (malloc, free)
#include <string.h>   // String manipulation functions (strcmp)
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50  // Maximum length for string elements in arrays
```

### Function Documentation

#### `binary_search(void *arr, int size, char type, void *target, int visualize)`
Performs binary search on a sorted array of specified type.

**Parameters**:
- `arr`: Pointer to the sorted array to search
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `target`: Pointer to the target value
- `visualize`: Flag to enable step-by-step visualization (1 = enable, 0 = disable)

**Returns**: Index of found element, -1 if not found, -2 for unknown type

#### `sort_array(void *arr, int size, char type)`
Sorts an array using ___bubble sort___ algorithm.

**Parameters**:
- `arr`: Pointer to the array to sort
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')

#### `print_array(void *arr, int size, char type)`
Prints an array in a formatted manner.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')

#### `print_array_with_range(void *arr, int size, char type, int left, int right, int mid)`
Prints an array with highlighting for visualization.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `left`: Left boundary of search range (-1 for no highlight)
- `right`: Right boundary of search range (-1 for no highlight)
- `mid`: Middle index to highlight (-1 for no highlight)

### Command Line Options

- `-v`, `--visualize`: Enable step-by-step search visualization

## Advantages/Disadvantages

### Advantages over Linear Search
- **Faster**: $O(\log n)$ vs $O(n)$ time complexity
- **Efficient for large datasets**: Scales much better
- **Predictable performance**: Consistent logarithmic behavior

### Disadvantages
- **Requires sorted array**: Additional sorting overhead
- **More complex**: Implementation is more involved than linear search
- **Not suitable for small arrays**: Overhead might not be worth it

## License

MIT License - see [LICENSE](/LICENSE) file for details
