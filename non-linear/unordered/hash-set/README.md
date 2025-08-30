# Set: A Dynamic Hash Set ADT in C

## Overview

The Set ADT is a dynamic, header-only C library providing an implementation of hash set for integers. It uses a hash table with **open addressing** and **double hashing** to handle collisions, ensuring efficient element storage and retrieval. This design allows for automatic resizing to maintain a high level of performance as the set grows. The library provides a rich API for common set operations, including unions, intersections, differences, and various relational checks.

---

## Table of Contents

- [Features](#features)
- [Function Overview](#function-overview)
  - [Core Management](#core-management)
  - [Element Operations](#element-operations)
  - [Set Theory Operations](#set-theory-operations)
  - [Relational Checks](#relational-checks)
  - [Diagnostics](#diagnostics)
- [How to Compile and Run](#how-to-compile-and-run)
- [Limitations](#limitations)
- [License](#license)
- [Author](#author)

---

## Features

- **Header-Only Design:** The entire library is contained within a single `adt_Set.h` file, making it easy to integrate.
- **Dynamic Capacity:** The set automatically **resizes** by doubling its capacity when the load factor exceeds 0.75, preventing performance degradation.
- **Collision Handling:** Uses a **double hashing** approach for robust collision resolution, which probes for a new location using a secondary hash function.
- **Element States:** Employs `EMPTY`, `OCCUPIED`, and `DELETED` states for buckets, which is crucial for correct probing behavior during insertions and deletions.
- **Deep Copying:** The `copy` function creates a full, independent duplicate of the set.
- **Comprehensive API:** Provides a wide range of functions for set manipulation and comparison, including standard set theory operations.

---

## Function Overview

The `adt_Set.h` header file exposes the following API functions:

### Core Management

- `Set *init(const int capacity)`: Initializes a new set with the specified `capacity`. Returns `NULL` on failure or if the capacity is invalid.
- `Set *copy(const Set *set)`: Creates a deep copy of the given set.
- `void clear(Set *set)`: Removes all elements from the set without deallocating the underlying memory.
- `void destroy(Set *set)`: Frees all memory associated with the set.

### Element Operations

- `void insert(Set *set, const int key)`: Adds an integer key to the set. Does nothing if the key already exists.
- `void discard(Set *set, const int key)`: Removes an integer key from the set. Does nothing if the key is not found.
- `bool contains(const Set *set, const int key)`: Checks for the existence of an integer key in the set.

### Set Theory Operations

- `Set *unionOf(const Set *set1, const Set *set2)`: Computes and returns a new set containing all unique elements from `set1` and `set2`.
- `Set *intersectionOf(const Set *set1, const Set *set2)`: Computes and returns a new set containing elements common to both `set1` and `set2`.
- `Set *differenceOf(const Set *set1, const Set *set2)`: Computes and returns a new set containing elements from `set1` that are not in `set2`.
- `Set *symmetricDifferenceOf(const Set *set1, const Set *set2)`: Computes and returns a new set containing elements unique to each set.

### Relational Checks

- `bool isEqual(const Set *set1, const Set *set2)`: Checks if both sets contain the same elements.
- `bool isSubset(const Set *subset, const Set *set)`: Checks if `subset` is a subset of `set`.
- `bool isProperSubset(const Set *subset, const Set *set)`: Checks if `subset` is a proper subset of `set`.
- `bool isSuperset(const Set *superset, const Set *set)`: Checks if `superset` is a superset of `set`.
- `bool isProperSuperset(const Set *superset, const Set *set)`: Checks if `superset` is a proper superset of `set`.
- `bool isDisjoint(const Set *set1, const Set *set2)`: Checks if the sets have no common elements.

### Diagnostics

- `void traverse(const Set *set)`: Prints all elements of the set to the console.
- `void describe(const Set *set)`: Displays the internal structure of the hash table for debugging purposes.

---

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_Set.h` file and a corresponding test program (e.g., `test_Set.c`) in the same directory.

2.  **Include the Header File**
    Add the following directive to your source file:

    ```c
    #include "adt_Set.h"
    ```

3.  **Compile the Code**
    Use any standard C compiler to compile your program. Example using GCC:

    ```bash
    gcc -o test_Set test_Set.c
    ```

4.  **Run the Executable**
    After successful compilation:

    ```bash
    ./test_Set
    ```

5.  **Example Usage**

    ```c
    #include "adt_Set.h"
    #include <stdio.h>

    int main() {
        Set *set1 = init(8);
        insert(set1, 10);
        insert(set1, 20);
        insert(set1, 30);

        Set *set2 = init(8);
        insert(set2, 30);
        insert(set2, 40);

        Set *union_set = unionOf(set1, set2);
        printf("Union of sets: ");
        traverse(union_set);

        printf("Is {10, 20} a subset of set1? %s\n", isSubset(init(2), set1) ? "Yes" : "No");

        destroy(set1);
        destroy(set2);
        destroy(union_set);

        return 0;
    }
    ```

---

## Limitations

- **Integer Elements Only:** This implementation is limited to storing and manipulating `int` data.
- **Manual Deallocation Required:** The caller is responsible for invoking `destroy()` on all sets to prevent memory leaks.
- **No Thread Safety:** This is a single-threaded implementation without internal synchronization primitives.
- **Hashing Algorithm:** The primary hash function uses floating-point arithmetic, which might be slower than pure integer-based hashing and could introduce minor precision issues, although generally negligible for typical integer keys.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name:** Zulqarnain Chishti
- **Email:** [thisiszulqarnain@gmail.com](mailto:thisiszulqarnain@gmail.com)
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
