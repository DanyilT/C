# Merge Sort

A generic merge sort implementation in C that supports multiple data types including integers, floats, characters, and strings with optional visualization.

## Algorithm Description
Merge sort is a divide-and-conquer algorithm that divides the input array into two halves, recursively sorts both halves, and then merges the sorted halves back together. It's one of the most efficient stable sorting algorithms.

## Features

- **Multi-type support**: Sort arrays of integers, floats, characters, or strings
- **User input**: Interactive program that accepts user-defined arrays
- **Generic implementation**: Uses void pointers for type-agnostic sorting
- **Memory management**: Proper dynamic memory allocation and cleanup
- **Divide-and-conquer**: Recursive approach with efficient merging
- **Visualization**: Optional step-by-step sorting visualization with `-v` or `--visualize` flag
- **Colored output**: Uses ANSI color codes for enhanced user experience (`ansi_colors.h`)

### Supported Data Types

1. **Integers** (`int`)
2. **Floats** (`float`)
3. **Characters** (`char`)
4. **Strings** (`char[STRING_LENGTH]`) - `#define STRING_LENGTH 50`

## Algorithm Complexity

### Time Complexity
- **Best Case**: $O(n \log n)$, $\Omega(n \log n)$ - Always divides and merges consistently
- **Average Case**: $O(n \log n)$, $\Theta(n \log n)$ - Consistent performance regardless of input
- **Worst Case**: $O(n \log n)$ - Same as best case (logarithmic depth, linear merge)

### Space Complexity
- $O(n)$ - Requires additional space for temporary arrays during merging

## How it Works

1. **Divide** the array into two halves recursively until each subarray has one element
2. **Conquer** by recursively sorting both halves
3. **Merge** the sorted halves back together in sorted order
4. **Combine** results to get the final sorted array

The algorithm uses a recursive approach where the base case is when the subarray has only one element (already sorted).

## How to Use

1. **Compile the program**:
   ```bash
   gcc -o merge_sort merge_sort.c
   ```

2. **Run the program**:
   ```bash
   # Normal execution
   ./merge_sort

   # With visualization
   ./merge_sort -v
   ./merge_sort --visualize
   ```

3. **Follow the prompts**:
   - Choose data type (1-4)
   - Enter array size
   - Input array elements

## Example Usage

### Normal Execution
```
Merge Sort
==========
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 5
Enter 5 integers: 3 2 8 13 5

-- Merge Sort --

-- Original Array
[3, 2, 8, 13, 5]
Sorting...

-- Sorted Array
[2, 3, 5, 8, 13]
```

### With Visualization
```
Merge Sort
==========
Visualization enabled.
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 5
Enter 5 integers: 3 2 8 13 5

-- Merge Sort --

-- Original Array
[3, 2, 8, 13, 5]
Sorting...

Step-by-step sorting:
Step 1: Dividing array [0-4] at mid=2 -> [3, 2, 8, 13, 5]
Step 2: Dividing array [0-2] at mid=1 -> [3, 2, 8]
Step 3: Dividing array [0-1] at mid=0 -> [3, 2]
Step 4: Merging subarrays [0-0] and [1-1] -> [3, 2]
    ✓ Merged -> [2, 3]
Step 5: Merging subarrays [0-1] and [2-2] -> [2, 3, 8]
    ✓ Merged -> [2, 3, 8]
Step 6: Dividing array [3-4] at mid=3 -> [2, 3, 8, 13, 5]
Step 7: Merging subarrays [3-3] and [4-4] -> [2, 3, 8, 13, 5]
    ✓ Merged -> [2, 3, 8, 5, 13]
Step 8: Merging subarrays [0-2] and [3-4] -> [2, 3, 8, 5, 13]
    ✓ Merged -> [2, 3, 5, 8, 13]

-- Sorted Array
[2, 3, 5, 8, 13]
```

## Implementation Details

- Uses `void*` pointers for generic array handling
- Dynamic memory allocation with `malloc()` for temporary arrays
- Recursive divide-and-conquer approach
- Type-specific comparison logic during merging
- String comparison using `strcmp()` for string arrays
- String copying using `strcpy()` for string operations
- Step counter for visualization tracking
- Command-line argument parsing for visualization mode
- ANSI color codes for enhanced visual feedback

### Include & Define Statements

```c
#include <stdio.h>    // Standard input/output functions (printf, scanf)
#include <stdlib.h>   // Memory allocation functions (malloc, free)
#include <string.h>   // String manipulation functions (strcmp, strcpy)
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50   // Maximum length for string elements in arrays
```

### Function Documentation

#### `merge_sort(void *arr, int left, int right, char type, int *step, int visualize)`
Performs merge sort on an array of specified type using divide-and-conquer approach.

**Parameters**:
- `arr`: Pointer to the array to sort
- `left`: Starting index of the subarray to sort
- `right`: Ending index of the subarray to sort
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `step`: Pointer to step counter for visualization
- `visualize`: Flag to enable step-by-step visualization (1 = enable, 0 = disable)

**Returns**: void

#### `print_array(void *arr, int size, char type)`
Prints an array in a formatted manner.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')

**Returns**: void

#### `print_array_with_range(void *arr, int size, char type, int left, int right, int mid)`
Prints an array with highlighting for a specific range and mid-point during divide-and-conquer visualization.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `left`: Left index of the range to highlight (-1 for no highlight)
- `right`: Right index of the range to highlight (-1 for no highlight)
- `mid`: Index of the mid-point to highlight (-1 for no highlight)

**Returns**: void

## Command Line Options

- `-v`, `--visualize`: Enable step-by-step sorting visualization

## Advantages/Disadvantages

### Advantages
- **Optimal time complexity**: $O(n \log n)$ for all cases
- **Stable algorithm**: Maintains relative order of equal elements
- **Predictable performance**: Consistent time complexity regardless of input
- **Parallelizable**: Divide-and-conquer approach allows for parallel implementation
- **Works well with large datasets**: Efficient for big data sorting

### Disadvantages
- **Extra space required**: $O(n)$ space complexity for temporary arrays
- **Not in-place**: Requires additional memory allocation
- **Overhead for small arrays**: Recursive calls add overhead for small datasets
- **Cache performance**: May have poor cache locality due to non-contiguous access

### Comparison with Other Algorithms

| Algorithm      | Best Case     | Average Case  | Worst Case    | Space       | Stable |
|----------------|---------------|---------------|---------------|-------------|--------|
| Merge Sort     | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$      | Yes    |
| Bubble Sort    | $O(n)$        | $O(n^2)$      | $O(n^2)$      | $O(1)$      | Yes    |
| Selection Sort | $O(n^2)$      | $O(n^2)$      | $O(n^2)$      | $O(1)$      | No     |

## Use Cases

- **Large datasets**: When efficiency is crucial for big data
- **Stable sorting required**: When relative order of equal elements must be preserved
- **Guaranteed performance**: When consistent $O(n \log n)$ time is needed
- **External sorting**: When data doesn't fit entirely in memory
- **Parallel processing**: When sorting can be distributed across multiple processors

## License

MIT License - see [LICENSE](/LICENSE) file for details
