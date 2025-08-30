# Map: A Dynamic Hash Map ADT in C

## Overview

The Map ADT is a dynamic, header-only C library providing a hash-map implementation that stores integer values associated with string keys. It uses **separate chaining** to handle collisions, where each bucket in the map points to a linked list of key-value pairs. This design ensures robust performance by minimizing key clustering. The library includes automatic resizing to maintain an optimal load factor, ensuring efficient lookups, insertions, and deletions.

---

## Table of Contents

- [Features](#features)
- [Function Overview](#function-overview)
  - [Core Management](#core-management)
  - [Operations](#operations)
  - [Queries](#queries)
  - [Diagnostics](#diagnostics)
- [How to Compile and Run](#how-to-compile-and-run)
- [Limitations](#limitations)
- [License](#license)
- [Author](#author)

---

## Features

- **Header-Only Design:** The entire library is contained within a single `adt_Map.h` file, making it easy to integrate.
- **Dynamic Capacity:** The map automatically **resizes** by doubling its capacity when the load factor exceeds 0.75, preventing performance degradation.
- **Collision Handling:** Uses a **separate chaining** approach with linked lists, which is a simple and effective method for resolving hash collisions.
- **Deep Copying:** The `copy` function creates a full, independent duplicate of the map, including all string keys and values.
- **Flexible Hashing:** Includes two hash functions (FNV-1a and djb2), allowing the user to choose the preferred algorithm by uncommenting the relevant code.
- **Robust API:** Provides a comprehensive set of functions for key-value management, including `put`, `get`, and `pop`.

---

## Function Overview

The `adt_Map.h` header file exposes the following API functions:

### Core Management

- `Map *init(const int capacity)`: Initializes a new map with the specified `capacity`. Returns `NULL` on failure or if the capacity is invalid.
- `Map *copy(const Map *table)`: Creates a deep copy of the given map.
- `void clear(Map *table)`: Removes all key-value pairs from the table without deallocating the table itself.
- `void destroy(Map *table)`: Frees all memory associated with the map, including keys and entries.

### Operations

- `void put(Map *table, const char *key, const int value)`: Inserts a new key-value pair. If the key already exists, its value is updated.
- `int pop(Map *table, const char *key)`: Removes a key-value pair and returns the associated value. Returns `-1` if the key is not found.

### Queries

- `int get(const Map *table, const char *key)`: Retrieves the value for a given key. Returns `-1` if the key is not found.
- `bool contains(const Map *table, const char *key)`: Checks for the existence of a key in the table.
- `Entry *items(const Map *table)`: Returns a dynamically allocated array of all key-value pairs. The caller is responsible for freeing this memory.

### Diagnostics

- `void traverse(const Map *table)`: Prints all key-value pairs to the console.
- `void describe(const Map *table)`: Displays the internal structure of the map, showing each bucket and its chained entries.

---

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_Map.h` file and a corresponding test program (e.g., `test_Map.c`) in the same directory.

2.  **Include the Header File**
    Add the following directive to your source file:

    ```c
    #include "adt_Map.h"
    ```

3.  **Compile the Code**
    Use any standard C compiler to compile your program. Example using GCC:

    ```bash
    gcc -o test_Map test_Map.c
    ```

4.  **Run the Executable**
    After successful compilation:

    ```bash
    ./test_Map
    ```

5.  **Example Usage**

    ```c
    #include "adt_Map.h"
    #include <stdio.h>

    int main() {
        Map *table = init(8);
        put(table, "apple", 1);
        put(table, "banana", 2);
        put(table, "orange", 3);

        printf("Value for 'apple': %d\n", get(table, "apple"));

        printf("Is 'banana' in the table? %s\n", contains(table, "banana") ? "Yes" : "No");

        pop(table, "banana");
        printf("Value for 'banana' after pop: %d\n", get(table, "banana"));

        printf("Current table contents:\n");
        traverse(table);

        destroy(table);
        return 0;
    }
    ```

---

## Limitations

- **String Key Duplication:** The `put` function uses `strdup` to create a new copy of the key string, which allocates memory and can impact performance for large numbers of insertions.
- **Manual Deallocation Required:** The caller is responsible for invoking `destroy` to prevent memory leaks. This is also true for the `items` function, whose returned array must be freed manually.
- **Not Thread-Safe:** This is a single-threaded implementation without internal synchronization primitives.
- **Value Type:** The current implementation only supports `int` values. To support other types, you would need to modify the `Entry` struct and the function signatures.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name:** Zulqarnain Chishti
- **Email:** [thisiszulqarnain@gmail.com](mailto:thisiszulqarnain@gmail.com)
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
