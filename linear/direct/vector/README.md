## Vector: A Dynamic Array Abstract Data Type in C

### Overview

Vector is a robust and feature-rich implementation of a dynamic array as an Abstract Data Type (ADT) in C. Designed for educational clarity and practical utility, it provides a flexible, resizable array structure capable of storing integer elements. This project serves as a comprehensive example of data structure implementation in pure C, covering fundamental array operations, various search and sort algorithms, and functional programming paradigms.

## Table of Contents

- [Features](#features)
- [Function Overview](#function-overview)
  - [Core Management](#core-management)
  - [Element Manipulation](#element-manipulation)
  - [Data Transformation & Utilities](#data-transformation--utilities)
  - [Search Algorithms](#search-algorithms)
  - [Sorting Algorithms](#sorting-algorithms)
  - [Functional Programming](#functional-programming-inspired)
- [How to Compile and Run](#how-to-compile-and-run)
- [Limitations](#limitations)
- [License](#license)
- [Author](#author)

## Features

- **Dynamic Sizing:** Automatically expands its capacity as more elements are added.
- **Core Operations:** Includes essential array manipulations like initialization, appending, inserting, retrieving, setting, and removing elements.
- **Search Algorithms:** Implements various search techniques for both sorted and unsorted data.
- **Sorting Algorithms:** Provides implementations of common sorting algorithms, allowing for comparison and analysis.
- **Functional Helpers:** Incorporates functions inspired by functional programming (map, filter, any, all) for convenient data transformation and analysis.
- **Memory Management:** Explicitly handles memory allocation and deallocation to prevent leaks.
- **Header-Only Library:** Easy to integrate into other C projects by simply including the header file.

---

## Functions Overview

The `adt_Vector.h` header file exposes the following public API functions:

### Core Management

- `Vector init(const int capacity)`: Initializes a new `Vector` with a specified initial capacity.
- `Vector copy(const Vector *vector)`: Creates a deep copy of the `Vector`.
- `Vector slice(const Vector *vector, const int start, const int end)`: Creates a new `Vector` containing a portion (slice) of the original.
- `Vector join(const Vector *front, const Vector *rear)`: Concatenates two `Vectors` into a new one.
- `void clear(Vector *vector)`: Resets the `Vector`'s length to 0, but retains its allocated capacity.
- `void destroy(Vector *vector)`: Deallocates all memory associated with the `Vector`.
- `bool isEmpty(const Vector *vector)`: Checks if the `Vector` contains no elements.
- `void traverse(const Vector *vector)`: Prints the elements, length, and capacity of the `Vector`.

### Element Manipulation

- `int get(const Vector *vector, const int index)`: Retrieves the element at a specific index.
- `void set(Vector *vector, const int value, const int index)`: Sets the element at a specific index to a new value.
- `void replace(Vector *vector, const int newVal, const int oldVal, const int index)`: Replaces the first occurrence of `oldVal` with `newVal`, starting the search from `index`.
- `void append(Vector *vector, const int value)`: Adds an element to the end of the `Vector`.
- `void insert(Vector *vector, const int value, const int index)`: Inserts an element at a specific index, shifting subsequent elements.
- `void pop(Vector *vector, const int value)`: Removes the first occurrence of `value` from the vector.
- `int discard(Vector *vector, const int index)`: Removes and returns the element at a specific index.

### Data Transformation & Utilities

- `Vector populate(const int *array, const int length)`: Populates a new `Vector` from a C-style array.
- `void fill(Vector *vector, const int quantity, const int value)`: Fills the list with a specified quantity of a given value.
- `void reverse(Vector *vector)`: Reverses the order of elements in-place.
- `void random(Vector *vector, const int quantity, const int min, const int max)`: Fills the list with random integers within a specified range.
- `void shuffle(Vector *vector)`: Randomly shuffles the elements in the `Vector` using Fisher-Yates algorithm.

### Search Algorithms

- `int linearSearch(const Vector *vector, const int value, const int index)`: Finds an element by iterating sequentially from a starting index.
- `int binarySearch(const Vector *vector, const int value, const int index)`: Efficiently finds an element in a sorted list by repeatedly dividing the search interval in half.
- `int ternarySearch(const Vector *vector, const int value, const int index)`: Similar to binary search but divides the array into three parts.
- `int interpolationSearch(const Vector *vector, const int value, const int index)`: An improvement over binary search for uniformly distributed sorted data.
- `int jumpSearch(const Vector *vector, const int value, const int index)`: Reduces search time by jumping through fixed-size blocks.

### Sorting Algorithms

- `void bubbleSort(Vector *vector)`: Simple comparison-based sort, repeatedly steps through the list.
- `void selectionSort(Vector *vector)`: Finds the minimum element from the unsorted part and puts it at the beginning.
- `void insertionSort(Vector *vector)`: Builds the final sorted array one item at a time.
- `void countSort(Vector *vector)`: Non-comparison sort, effective for integer data within a limited range.
- `void radixSort(Vector *vector)`: Sorts non-negative integers by processing digits from least to most significant.
- `void mergeSort(Vector *vector)`: Divide and conquer algorithm, recursively divides and merges sorted halves.
- `void quickSort(Vector *const vector)`: Divide and conquer algorithm, picks a pivot and partitions the array around it.
- `void heapSort(Vector *vector)`: Builds a max-heap and repeatedly extracts the maximum element.

### Functional Programming

- `void map(Vector *vector, int (*func)(int))`: Applies a function to each element, transforming it in-place.
- `void filter(Vector *vector, bool (*func)(int))`: Retains only elements for which a predicate function returns true.
- `bool any(const Vector *vector)`: Returns true if at least one element is non-zero (truthy).
- `bool all(const Vector *vector)`: Returns true if all elements are non-zero (truthy).
- `int max(const Vector *vector)`: Returns the maximum value in the list.
- `int min(const Vector *vector)`: Returns the minimum value in the list.
- `int sum(const Vector *vector)`: Calculates the sum of all elements.
- `int prod(const Vector *vector)`: Calculates the product of all elements.
- `int count(const Vector *vector, const int value)`: Counts occurrences of a specific value.
- `bool contains(const Vector *vector, const int value)`: Checks if the list contains a specific value.

---

## How to Compile and Run

1.  **Download the Library**

    To begin using the library, ensure you have the `adt_Vector.h` header file and the `test_Vector.c` test file in your project directory.

    _Note: `adt_Vector.h` is a header-only library, meaning all function implementations are directly in the header._

2.  **Include the Header File**

    In your C program (e.g., `test_Vector.c`), include the header:

    ```c
    #include "adt_Vector.h"
    ```

3.  **Compile the Code**

    Since `adt_Vector.h` is a header-only library, you just need to compile your main application file (e.g., `test_Vector.c`) and link against the math library. For example, if you're using GCC, compile your program like this:

    ```bash
    gcc -o test_Vector test_Vector.c
    ```

    _This command will compile your source file (`test_Vector.c`) and link it with the necessary math functions to produce the final executable (`test_Vector`)._

4.  **Run the Executable**

    After successful compilation, run the program from the terminal:

    ```bash
    ./test_Vector
    ```

5.  **Example Program**

    Here's an example that demonstrates initialization, mutation, traversal, replacement, sorting, and destruction:

    ```c
    #include "adt_Vector.h"
    #include <stdio.h>

    int main() {
        Vector myVect = init(5);

        append(&myVect, 10);
        append(&myVect, 20);
        append(&myVect, 5);
        append(&myVect, 20);  // duplicate

        printf("Original vector: ");
        traverse(myVect);    // [ 10  20   5  20 ] : 4/5

        replace(&myVect, 25, 20, 0);  // Replace first 20 with 25
        printf("After replacing first 20 with 25: ");
        traverse(myVect);    // [ 10  25   5  20 ] : 4/5

        bubbleSort(&myVect);
        printf("Sorted vector: ");
        traverse(myVect);    // [  5  10  20  25 ] : 4/5

        destroy(&myVect);
        return 0;
    }
    ```

---

## Limitations

- **Fixed Data Type (Integers Only):** This implementation is specifically designed to store `int` type elements. Modifying it to store other data types (e.g., `float`, `char`, or custom structs) would require changing the `typedef` and `sizeof` operations throughout the code.
- **Basic Error Handling:** Error handling is primarily done via `return -1` for `get`/`pop`/`discard` on invalid operations, or `perror` and `exit(EXIT_FAILURE)` for critical memory allocation failures. A more robust production-grade library might use custom error codes, `errno`, or pass error information back to the caller for more flexible handling.
- **No Iterator Support:** The ADT does not expose explicit iterator mechanisms like those found in C++ STL containers. Traversal and manipulation are done via direct index access or the provided helper functions.
- **Complexity Trade-offs:** While various algorithms are provided, the implementation prioritizes clarity and directness, not necessarily the absolute most optimized version of each algorithm (e.g., in-place merge sort is more complex than one using auxiliary arrays).

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name:** Zulqarnain Chishti
- **Email:** thisiszulqarnain@gmail.com
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
