# String: A Dynamic Character String Abstract Data Type in C

## Overview

String ADT is a robust and feature-rich implementation of a dynamic, mutable string as an Abstract Data Type (ADT) in C. Designed for educational clarity and practical utility, it provides a flexible, resizable string structure capable of storing and manipulating character sequences efficiently. This project serves as a comprehensive example of data structure implementation in pure C, covering fundamental string operations, various search and comparison algorithms, and utility functions for manipulation and formatting.

## Table of Contents

- [Features](#features)
- [Function Overview](#function-overview)
  - [Core Management](#core-management)
  - [Content Manipulation](#content-manipulation)
  - [Content Validation & Comparison](#content-validation--comparison)
  - [String Formatting](#string-formatting)
  - [Advanced Utilities](#advanced-utilities)
- [How to Compile and Run](#how-to-compile-and-run)
- [Limitations](#limitations)
- [License](#license)
- [Author](#author)

## Features

- **Dynamic Sizing:** Automatically adjusts its allocated memory to accommodate varying string lengths, abstracting away low-level memory management for the user.
- **Core Operations:** Includes essential string manipulations like initialization, deep copying, character retrieval, and explicit memory deallocation.
- **Content Manipulation:** Provides robust methods for inserting, replacing, concatenating, discarding portions, and extracting slices (substrings).
- **Comparison & Search:** Implements various techniques for comparing strings (exact, case-insensitive, lexicographical), checking prefixes/suffixes, finding substrings, and counting occurrences.
- **Transformation & Utilities:** Offers functions for case conversion (to uppercase/lowercase), reversing, repeating, trimming specific characters, and aligning strings (left, center, right) within a given width.
- **Parsing & Conversion:** Supports converting integers to string representations in different bases (2-36) and parsing string representations back into integers.
- **Splitting & Joining:** Enables splitting strings into arrays of `String` objects based on a delimiter and joining arrays of strings back into a single `String`.
- **Content Validation:** Includes functions to check if string content is entirely uppercase, lowercase, alphabetic, numeric, alphanumeric, or composed solely of whitespace.
- **Memory Management:** Explicitly handles memory allocation and deallocation for internal string data through the `destroy` function to prevent memory leaks.
- **Header-Only Library:** Easy to integrate into other C projects by simply including the header file (`adt_String.h`).

## Function Overview

The `adt_String.h` header file exposes the following public API functions:

### Core Management

- `String init(const char *input)`: Initializes a new `String` object from a C-style string. Allocates memory and copies content.
- `String copy(String string)`: Creates a deep copy of an existing `String` object. Allocates new memory for the copy.
- `void destroy(String *string)`: **Deallocates the dynamically allocated memory** associated with a `String` object and sets its internal pointer to `NULL`. **Crucial for preventing memory leaks.**
- `char get(const String string, int index)`: Retrieves the character at a specified index. Returns `\0` for out-of-bounds access.

### Content Manipulation

- `String set(const String string, const String substring, int start, int end)`: Replaces a portion of a string (from `start` to `end`) with a `substring`. Returns a new `String`.
- `String replace(const String string, const String oldstring, const String newstring, int index)`: Replaces the first occurrence of `oldstring` with `newstring` in `string`, starting the search from `index`. Returns a new `String`.
- `String insert(const String string1, const String string2, int index)`: Inserts `string2` into `string1` at the specified `index`. Returns a new `String`.
- `String concat(const String string1, const String string2)`: Concatenates two `String` objects (`string2` appended to `string1`). Returns a new `String`.
- `String discard(const String string, int index, int quantity)`: Removes `quantity` characters from `string` starting at `index`. Returns a new `String`.
- `String slice(const String string, int start, int end)`: Extracts a slice (substring) from `string` (from `start` up to, but not including, `end`). Returns a new `String`.

### Content Validation & Comparison

- `bool isEqual(const String string1, const String string2)`: Compares two `String` objects for exact equality (case-sensitive).
- `bool isSimilar(const String string1, const String string2)`: Compares two `String` objects for similarity (case-insensitive for alphabetic characters).
- `int compare(const String string1, const String string2)`: Compares two `String` objects lexicographically. Returns `< 0`, `0`, or `> 0`.
- `bool startsWith(const String string, const String substring)`: Checks if a string starts with a given substring.
- `bool endsWith(const String string, const String substring)`: Checks if a string ends with a given substring.
- `bool contains(const String string, const String substring)`: Checks if a string contains a specified substring.
- `int find(const String string, const String substring, int index)`: Finds the first occurrence of a substring within a string, starting the search from `index`. Returns the starting index or `-1` if not found.
- `int count(const String string, const String substring)`: Counts the number of non-overlapping occurrences of a substring within a string.
- `bool isUpper(const String string)`: Checks if all characters in the string are uppercase alphabets.
- `bool isLower(const String string)`: Checks if all characters in the string are lowercase alphabets.
- `bool isAlphabet(const String string)`: Checks if all characters in the string are alphabetic (uppercase or lowercase).
- `bool isNumeric(const String string)`: Checks if all characters in the string are numeric digits ('0'-'9').
- `bool isAlphanum(const String string)`: Checks if all characters in the string are alphanumeric (alphabetic or numeric).
- `bool isWhitespace(const String string)`: Checks if all characters in the string are whitespace characters (` ' '`, `\t`, `\n`, `\r`, `\v`, `\f`).

### String Formatting

- `String reverse(const String string)`: Returns a new `String` object with the characters of the input string in reverse order.
- `String repeat(const String string, int times)`: Returns a new `String` object consisting of the input string repeated `times` number of times.
- `String toUpper(const String string)`: Returns a new `String` with all lowercase alphabetic characters converted to uppercase.
- `String toLower(const String string)`: Returns a new `String` with all uppercase alphabetic characters converted to lowercase.
- `String leftAlign(const String string, char padding, int length)`: Returns a new `String` left-aligned within `length`, padded with `padding` character.
- `String centerAlign(const String string, char padding, int length)`: Returns a new `String` centered within `length`, padded with `padding` character.
- `String rightAlign(const String string, char padding, int length)`: Returns a new `String` right-aligned within `length`, padded with `padding` character.
- `String trim(const String string, char padding)`: Returns a new `String` with leading and trailing occurrences of `padding` character removed.

### Advanced Utilities

- `String *split(const String string, char delimiter, int *size)`: Splits a `String` into a dynamically allocated array of `String` objects based on `delimiter`. The `size` of the array is returned via a pointer. **Requires freeing both the individual `String` objects in the array and the array itself.**
- `String join(const String *array, char delimiter, int size)`: Joins an array of `String` objects into a single `String` using `delimiter` between elements. Returns a new `String`.
- `int parse(const String number, const int base)`: Converts a `String` representation of a number (`number`) in a given `base` to an `int`. Supports bases 2-36.
- `String convert(int num, int base)`: Converts an `int` (`num`) to its `String` representation in a given `base`. Returns a new `String`.

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_String.h` header file and the `test_String.c` test file (or your own application file) in your project directory.

    _Note: `adt_String.h` is designed as a header-only library, meaning all function implementations are directly within the header, simplifying compilation._

2.  **Include the Header File**
    In your C program (e.g., `test_String.c`), include the header:

    ```c
    #include "adt_String.h"
    ```

3.  **Compile the Code**
    Use a C compiler like GCC. Since `adt_String.h` is header-only, you simply compile your main application file. No separate linking of library files is typically needed.

    For example, to compile `test_String.c`:

    ```bash
    gcc -o test_String test_String.c
    ```

    _(Optional: Add `-g` for debugging symbols if needed.)_

4.  **Run the Executable**
    After successful compilation, execute the compiled program from your terminal:

    ```bash
    ./test_String
    ```

5.  **Example Program**

    Here's a simple example demonstrating initialization, concatenation, and proper memory deallocation:

    ```c
    #include "adt_String.h"
    #include <stdio.h>
    #include <stdlib.h> // For EXIT_SUCCESS

    int main() {
        // Initialize String objects
        String greeting = init("Hello, ");
        String name = init("World!");
        String exclamation = init("!!!");

        // Concatenate strings
        String message = concat(greeting, name);
        String final_message = concat(message, exclamation);

        printf("Original greeting: \"%s\"\n", greeting.word);
        printf("Original name: \"%s\"\n", name.word);
        printf("Final message: \"%s\"\n", final_message.word);
        printf("Length of final message: %d\n", final_message.length);

        // Demonstrate a simple operation and then destroy
        String upper_name = toUpper(name);
        printf("Uppercase name: \"%s\"\n", upper_name.word);

        // --- IMPORTANT: Destroy all String objects to prevent memory leaks ---
        destroy(&greeting);
        destroy(&name);
        destroy(&exclamation);
        destroy(&message);       // message was a temporary result
        destroy(&final_message);
        destroy(&upper_name);    // upper_name was a temporary result

        // Example of splitting and joining, with proper destruction
        String csv_str = init("apple,banana,cherry");
        int num_parts;
        String *parts = split(csv_str, ',', &num_parts);

        printf("\nSplit parts:\n");
        for (int i = 0; i < num_parts; i++) {
            printf("  Part %d: \"%s\"\n", i, parts[i].word);
        }

        String joined_str = join(parts, '-', num_parts);
        printf("Joined string: \"%s\"\n", joined_str.word);

        // Destroy individual strings in the 'parts' array
        for (int i = 0; i < num_parts; i++) {
            destroy(&parts[i]);
        }
        free(parts); // Free the array itself (allocated by split)

        // Destroy the original and joined strings
        destroy(&csv_str);
        destroy(&joined_str);

        return EXIT_SUCCESS;
    }
    ```

## Limitations

- **Manual Memory Management:** While `destroy()` is provided, users must explicitly call `destroy()` for every `String` object created (either via `init()`, `copy()`, or returned by functions like `concat`, `slice`, `toUpper`, `split` etc.) to prevent memory leaks. Forgetting to call `destroy()` is the most common source of memory issues.
- **Return by Value:** Many functions return `String` objects by value. While convenient, this implies a copy of the `String` struct itself (pointers and length) is made. The underlying character array is typically reallocated for the new `String` being returned. This can be less efficient for very large strings compared to functions that modify strings in-place or pass pointers to results.
- **Basic Error Handling:** Error handling for invalid operations (e.g., out-of-bounds access for `get`) might return default values (`\0`) or -1, and critical memory allocation failures lead to `perror` and `exit(EXIT_FAILURE)`. A more robust production-grade library might use custom error codes, `errno`, or allow callers to define error callbacks.
- **No Iterator Support:** The ADT does not expose explicit iterator mechanisms like those found in C++ STL containers. Traversal and manipulation are done via direct index access or the provided helper functions.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Author

- **Name:** Zulqarnain Chishti
- **Email:** thisiszulqarnain@gmail.com
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
