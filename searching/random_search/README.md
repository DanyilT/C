# Random Search

A generic random search implementation in C that supports multiple data types including integers, floats, characters, and strings with optional visualization.

## Algorithm Description
Random search randomly selects indices in the array and checks if the element at that index matches the target. It continues until the target is found or maximum attempts are reached or checked all indices.

## Features

- **Multi-type support**: Search through arrays of integers, floats, characters, or strings
- **Duplicate tracking**: Tracks already checked indices during visualization
- **Maximum attempts**: Limits search to prevent infinite loops (`MAX_ATTEMPTS = 1000`)
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
- **Best Case**: $O(1)$, $\Omega(1)$ - Element found on first random attempt
- **Average Case**: $O(n)$, $\Theta(n)$ - Expected number of attempts for uniform distribution
- **Worst Case**: $O(\infty)$ - Potentially infinite (limited by MAX_ATTEMPTS)

### Space Complexity
- $O(n)$ - Uses array to track checked indices

## How it Works

1. **Initialize** random seed with current time
2. **Generate** random index between 0 and size-1
3. **Check** if element at random index matches target
4. **Track** checked indices, to mark them as visited
5. **Repeat** until element found or maximum attempts reached
6. **Early termination** if all indices have been checked

## How to Use

1. **Compile the program**:
   ```bash
   gcc -o random_search random_search.c
   ```

2. **Run the program**:
   ```bash
   # Normal execution
   ./random_search
   
   # With visualization
   ./random_search -v
   ./random_search --visualize
   ```

3. **Follow the prompts**:
   - Choose data type (1-4)
   - Enter array size
   - Input array elements
   - Enter target element to search

## Example Usage

### Normal Execution
```
Random Search
=============
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 10
Enter 10 integers: 1 1 2 3 5 8 13 21 34 55
Enter target integer: 8

-- Random Search --
Array: [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
Integer 8 found at index 5 (arr[5] == 8)
```

### With Visualization
```
Random Search
=============
Visualization enabled.
Choose data type:
1. Integers
2. Floats
3. Characters
4. Strings
Enter your choice (1-4): 1
Enter array size: 10
Enter 10 integers: 1 1 2 3 5 8 13 21 34 55
Enter target integer: 8

-- Random Search --
Array: [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]

Step-by-step search:
Attempt 1: Checking random index 5 -> [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
✓ Match found!

Integer 8 found at index 5 (arr[5] == 8)
```

## Implementation Details

- Uses `void*` pointers for generic array handling
- Dynamic memory allocation with `malloc()`
- Duplicate index tracking with `calloc()` for checked array
- Random number generation with `rand()` and `srand(time(NULL))`
- Proper type casting for different data types
- String comparison using `strcmp()` for string arrays
- Input buffer clearing to handle multiple inputs
- Command-line argument parsing for visualization mode
- ANSI color codes for enhanced visual feedback

### Include & Define Statements

```c
#include <stdio.h>    // Standard input/output functions (printf, scanf)
#include <stdlib.h>   // Memory allocation functions (malloc, free) and random functions (rand, srand)
#include <string.h>   // String manipulation functions (strcmp)
#include <time.h>     // Time functions for random seed (time)
#include "ansi_colors.h" // Include ANSI color codes for console output (custom header file)

#define STRING_LENGTH 50   // Maximum length for string elements in arrays
#define MAX_ATTEMPTS 1000  // Maximum number of random attempts before giving up
```

### Function Documentation

#### `random_search(void *arr, int size, char type, void *target, int visualize)`
Performs random search on an array of specified type.

**Parameters**:
- `arr`: Pointer to the array to search
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `target`: Pointer to the target value
- `visualize`: Flag to enable step-by-step visualization (1 = enable, 0 = disable)

**Returns**: Index of found element, -1 if not found after MAX_ATTEMPTS, -2 for unknown type, If chacked all indices without finding the target, returns negative attempts count.

#### `print_array(void *arr, int size, char type)`
Prints an array in a formatted manner.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')

#### `print_array_with_highlight(void *arr, int size, char type, int highlight_index)`
Prints an array with highlighting for a specific index for visualization.

**Parameters**:
- `arr`: Pointer to the array to print
- `size`: Number of elements in the array
- `type`: Data type identifier ('i', 'f', 'c', 's')
- `highlight_index`: Index of the element to highlight (-1 for no highlight)

## Command Line Options

- `-v`, `--visualize`: Enable step-by-step search visualization

## Advantages/Disadvantages

### Advantages
- **First match found**: Can find a target on the first attempt
- **Simple implementation**: Easy to understand and code
- **No preprocessing required**: Works on unsorted arrays
- **Can be parallelized**: Multiple random searches can run concurrently
- **Good for sparse target distribution**: Effective when target appears frequently

### Disadvantages
- **Unpredictable performance**: No guaranteed time complexity
- **Inefficient for dense searches**: May check same index multiple times (but if checked all indices, quits)
- **Not suitable for critical applications**: Unreliable completion time
- **Worst performance for missing elements**: May never terminate without limits

## Use Cases

- **Testing and debugging**: Quick search for development purposes
- **Distributed systems**: When coordination overhead is high
- **Large sparse datasets**: When target is likely to be found quickly
- **Educational purposes**: Demonstrating randomized algorithms
- **Prototyping**: Fast implementation for proof of concept
- **Fun**: 😅

## License

MIT License - see [LICENSE](/LICENSE) file for details
