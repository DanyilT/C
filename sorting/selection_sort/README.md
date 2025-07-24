# Selection Sort

A generic selection sort implementation in C that supports multiple data types including integers, floats, characters, and strings with optional visualization.

## Algorithm Description
Selection sort divides the input array into two parts: a sorted portion at the beginning and an unsorted portion at the end. The algorithm repeatedly finds the minimum element from the unsorted portion and moves it to the end of the sorted portion.

## Features

- **Multi-type support**: Sort arrays of integers, floats, characters, or strings
- **User input**: Interactive program that accepts user-defined arrays
- **Generic implementation**: Uses void pointers for type-agnostic sorting
- **Memory management**: Proper dynamic memory allocation and cleanup
- **Progress tracking**: Shows sorted vs unsorted portions and minimum finding process
- **Visualization**: Optional step-by-step sorting visualization with `-v` or `--visualize` flag
- **Colored output**: Uses ANSI color codes for enhanced user experience (`ansi_colors.h`)

### Supported Data Types

1. **Integers** (`int`)
2. **Floats** (`float`)
3. **Characters** (`char`)
4. **Strings** (`char[STRING_LENGTH]`) - `#define STRING_LENGTH 50`

## Algorithm Complexity

### Time Complexity
- **Best Case**: $O(n^2)$, $\Omega(n^2)$ - Always performs same number of comparisons
- **Average Case**: $O(n^2)$, $\Theta(n^2)$ - Consistent performance regardless of input
- **Worst Case**: $O(n^2)$ - Same as best case (no input dependency)

### Space Complexity
- $O(1)$ - In-place sorting algorithm, only uses constant extra space

## How it Works

1. **Start** with the first position as the sorted boundary
2. **Find** the minimum element in the unsorted portion
3. **Swap** the minimum element with the first unsorted element
4. **Move** the sorted boundary one position to the right
5. **Repeat** until all elements are in the sorted portion

After each pass, one more element is placed in its final sorted position.

## How to Use

1. **Compile the program**:
   ```bash
   gcc -o selection_sort selection_sort.c
   ```

2. **Run the program**:
   ```bash
   # Normal execution
   ./selection_sort

   # With visualization
   ./selection_sort -v
   ./selection_sort --visualize
   ```

3. **Follow the prompts**:
   - Choose data type (1-4)
   - Enter array size
   - Input array elements

## Example Usage

### Normal Execution
```
Selection Sort
==============
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 5
Enter 5 integers: 3 2 8 13 5

-- Selection Sort --

-- Original Array
[3, 2, 8, 13, 5]
Sorting...

-- Sorted Array
[2, 3, 5, 8, 13]
```

### With Visualization
```
Selection Sort
==============
Visualization enabled.
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 5
Enter 5 integers: 3 2 8 13 5

-- Selection Sort --

-- Original Array
[3, 2, 8, 13, 5]
Sorting...

Step-by-step sorting:
Pass 1: Finding minimum in unsorted portion...
  Comparing with index 1 -> [3, 2, 8, 13, 5]
    → New minimum found at index 1
  Comparing with index 2 -> [3, 2, 8, 13, 5]
    → No change
  Comparing with index 3 -> [3, 2, 8, 13, 5]
    → No change
  Comparing with index 4 -> [3, 2, 8, 13, 5]
    → No change
  ✓ Swapping index 0 with index 1
  Result after pass 1: [2, 3, 8, 13, 5]

Pass 2: Finding minimum in unsorted portion...
  Comparing with index 2 -> [2, 3, 8, 13, 5]
    → No change
  Comparing with index 3 -> [2, 3, 8, 13, 5]
    → No change
  Comparing with index 4 -> [2, 3, 8, 13, 5]
    → No change
  ✗ No swap needed (minimum is already in correct position)
  Result after pass 2: [2, 3, 8, 13, 5]

Pass 3: Finding minimum in unsorted portion...
  Comparing with index 3 -> [2, 3, 8, 13, 5]
    → No change
  Comparing with index 4 -> [2, 3, 8, 13, 5]
    → New minimum found at index 4
  ✓ Swapping index 2 with index 4
  Result after pass 3: [2, 3, 5, 13, 8]

Pass 4: Finding minimum in unsorted portion...
  Comparing with index 4 -> [2, 3, 5, 13, 8]
    → New minimum found at index 4
  ✓ Swapping index 3 with index 4
  Result after pass 4: [2, 3, 5, 8, 13]


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
- Visual distinction between sorted and unsorted portions
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

#### `selection_sort(void *arr, int size, char type, int visualize)`
Performs selection sort on an array of specified type.

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

#### `print_array_with_highlight(void *arr, int size, char type, int sorted_boundary, int current, int min_index)`
Prints an array with highlighting for sorted boundary, current element, and minimum element.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `sorted_boundary`: Index marking boundary between sorted and unsorted portions (-1 for no highlight)
- `current`: Index of current element being compared (-1 for no highlight)
- `min_index`: Index of current minimum element (-1 for no highlight)

**Returns**: void

## Command Line Options

- `-v`, `--visualize`: Enable step-by-step sorting visualization

## Advantages/Disadvantages

### Advantages
- **Simple implementation**: Easy to understand and code
- **In-place sorting**: Requires only constant extra memory
- **Consistent performance**: Time complexity doesn't depend on input order
- **Minimum swaps**: Makes at most $n-1$ swaps (good for expensive write operations)
- **Works well with small datasets**: Simplicity can outweigh efficiency concerns

### Disadvantages
- **Poor time complexity**: $O(n^2)$ for all cases
- **Not stable**: May change relative order of equal elements
- **Not adaptive**: Doesn't benefit from partially sorted arrays
- **Many comparisons**: Always performs same number of comparisons regardless of input

### Comparison with Other Algorithms

| Algorithm      | Best Case     | Average Case  | Worst Case    | Space       | Stable | Swaps         |
|----------------|---------------|---------------|---------------|-------------|--------|---------------|
| Selection Sort | $O(n^2)$      | $O(n^2)$      | $O(n^2)$      | $O(1)$      | No     | $O(n)$        |
| Bubble Sort    | $O(n)$        | $O(n^2)$      | $O(n^2)$      | $O(1)$      | Yes    | $O(n^2)$      |
| Merge Sort     | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$      | Yes    | $O(n \log n)$ |

## Use Cases

- **Educational purposes**: Teaching sorting algorithm concepts
- **Small datasets**: When simplicity is more important than efficiency
- **Memory-constrained environments**: When extra space is not available
- **Write-expensive operations**: When swapping is costly (e.g., large objects)

## License

MIT License - see [LICENSE](/LICENSE) file for details
