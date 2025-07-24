# Bubble Sort

A generic bubble sort implementation in C that supports multiple data types including integers, floats, characters, and strings with optional visualization.

## Algorithm Description
Bubble sort repeatedly steps through the array, compares adjacent elements and swaps them if they are in the wrong order. The pass through the array is repeated until the array is sorted. The algorithm gets its name from the way smaller elements "bubble" to the top of the array.

## Features

- **Multi-type support**: Sort arrays of integers, floats, characters, or strings
- **User input**: Interactive program that accepts user-defined arrays
- **Generic implementation**: Uses void pointers for type-agnostic sorting
- **Memory management**: Proper dynamic memory allocation and cleanup
- **Early termination**: Stops when no swaps occur (array is already sorted)
- **Pass tracking**: Shows progress through each sorting pass
- **Visualization**: Optional step-by-step sorting visualization with `-v` or `--visualize` flag
- **Colored output**: Uses ANSI color codes for enhanced user experience (`ansi_colors.h`)

### Supported Data Types

1. **Integers** (`int`)
2. **Floats** (`float`)
3. **Characters** (`char`)
4. **Strings** (`char[STRING_LENGTH]`) - `#define STRING_LENGTH 50`

## Algorithm Complexity

### Time Complexity
- **Best Case**: $O(n)$, $\Omega(n)$ - Array is already sorted (with early termination)
- **Average Case**: $O(n^2)$, $\Theta(n^2)$ - Random order elements
- **Worst Case**: $O(n^2)$ - Array is sorted in reverse order

### Space Complexity
- $O(1)$ - In-place sorting algorithm, only uses constant extra space

## How it Works

1. **Start** with the first element of the array
2. **Compare** adjacent elements (arr[j] and arr[j+1])
3. **Swap** if they are in wrong order (arr[j] > arr[j+1] for ascending)
4. **Continue** through the array until the end
5. **Repeat** passes until no swaps are made
6. **Early termination** when array becomes sorted

After each pass, the largest unsorted element "bubbles up" to its correct position at the end.

## How to Use

1. **Compile the program**:
   ```bash
   gcc -o bubble_sort bubble_sort.c
   ```

2. **Run the program**:
   ```bash
   # Normal execution
   ./bubble_sort

   # With visualization
   ./bubble_sort -v
   ./bubble_sort --visualize
   ```

3. **Follow the prompts**:
   - Choose data type (1-4)
   - Enter array size
   - Input array elements

## Example Usage

### Normal Execution
```
Bubble Sort
===========
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 5
Enter 5 integers: 3 2 8 13 5

-- Bubble Sort --

-- Original Array
[3, 2, 8, 13, 5]
Sorting...

-- Sorted Array
[2, 3, 5, 8, 13]
```

### With Visualization
```
Bubble Sort
===========
Visualization enabled.
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 5
Enter 5 integers: 3 2 8 13 5

-- Bubble Sort --

-- Original Array
[3, 2, 8, 13, 5]
Sorting...

Step-by-step sorting:
Pass 1:
  Comparing indices 0 and 1 -> [3, 2, 8, 13, 5]
    ✓ Swapped -> [2, 3, 8, 13, 5]
  Comparing indices 1 and 2 -> [2, 3, 8, 13, 5]
    ✓ Swapped -> [2, 3, 8, 13, 5]
  Comparing indices 2 and 3 -> [2, 3, 8, 13, 5]
    ✓ Swapped -> [2, 3, 8, 13, 5]
  Comparing indices 3 and 4 -> [2, 3, 8, 13, 5]
    ✓ Swapped -> [2, 3, 8, 5, 13]
  End of pass 1: [2, 3, 8, 5, 13]

Pass 2:
  Comparing indices 0 and 1 -> [2, 3, 8, 5, 13]
    ✗ No swap needed
  Comparing indices 1 and 2 -> [2, 3, 8, 5, 13]
    ✗ No swap needed
  Comparing indices 2 and 3 -> [2, 3, 8, 5, 13]
    ✓ Swapped -> [2, 3, 5, 8, 13]
  End of pass 2: [2, 3, 5, 8, 13]

Pass 3:
  Comparing indices 0 and 1 -> [2, 3, 5, 8, 13]
    ✗ No swap needed
  Comparing indices 1 and 2 -> [2, 3, 5, 8, 13]
    ✗ No swap needed
  End of pass 3: [2, 3, 5, 8, 13]

Array is sorted! Early termination.

-- Sorted Array
[2, 3, 5, 8, 13]
```

## Implementation Details

- Uses `void*` pointers for generic array handling
- Dynamic memory allocation with `malloc()`
- Type-specific comparison and swapping logic
- String comparison using `strcmp()` for string arrays
- String copying using `strcpy()` for string swaps
- Input buffer clearing to handle multiple inputs
- Early termination optimization when array becomes sorted
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

#### `bubble_sort(void *arr, int size, char type, int visualize)`
Performs bubble sort on an array of specified type.

**Parameters**:
- `arr`: Pointer to the array to sort
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `visualize`: Flag to enable step-by-step visualization (1 = enable, 0 = disable)

**Returns**: void

#### `print_array(void *arr, int size, char type)`
Prints an array in a formatted manner.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')

**Returns**: void

#### `print_array_with_highlight(void *arr, int size, char type, int index[2])`
Prints an array with highlighting for two specific indices during comparison visualization.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `index`: Array containing two indices to highlight (-1 for no highlight)

**Returns**: void

## Command Line Options

- `-v`, `--visualize`: Enable step-by-step sorting visualization

## Advantages/Disadvantages

### Advantages
- **Simple implementation**: Easy to understand and code
- **In-place sorting**: Requires only constant extra memory
- **Stable algorithm**: Maintains relative order of equal elements
- **Adaptive**: Performs better on partially sorted arrays
- **Early termination**: Can detect when sorting is complete

### Disadvantages
- **Poor time complexity**: $O(n^2)$ average and worst case
- **Inefficient for large datasets**: Too many comparisons and swaps
- **Not suitable for production**: Better algorithms available
- **Many unnecessary comparisons**: Even when array becomes sorted early

### Comparison with Other Algorithms

| Algorithm      | Best Case     | Average Case  | Worst Case    | Space       | Stable |
|----------------|---------------|---------------|---------------|-------------|--------|
| Bubble Sort    | $O(n)$        | $O(n^2)$      | $O(n^2)$      | $O(1)$      | Yes    |
| Selection Sort | $O(n^2)$      | $O(n^2)$      | $O(n^2)$      | $O(1)$      | No     |
| Merge Sort     | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$      | Yes    |

## Use Cases

- **Educational purposes**: Teaching sorting algorithm concepts
- **Small datasets**: When simplicity is more important than efficiency
- **Nearly sorted arrays**: Benefits from early termination
- **Understanding algorithm behavior**: Visualization helps learn sorting

## License

MIT License - see [LICENSE](/LICENSE) file for details
