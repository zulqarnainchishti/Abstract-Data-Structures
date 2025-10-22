# DisjointSet: A Union-Find ADT in C

## Overview

Disjoint Set, also known as the Union-Find data structure, is a crucial ADT for managing a collection of sets where every element belongs to exactly one set. Implemented in pure C, it provides an extraordinarily efficient way to perform two fundamental operations: Union (merging two sets) and Find (determining an element's set representative). Its performance is achieved through sophisticated array-based optimizations, making it indispensable for algorithms like Kruskal's for Minimum Spanning Trees, graph connectivity problems, and maze generation.

---

## Table of Contents

- [Features](#features)
- [Function Overview](#function-overview)
  - [Core Management](#core-management)
  - [Set Operations](#set-operations)
  - [Utility Functions](#utility-functions)
- [Performance](#performance)
- [How to Compile and Run](#how-to-compile-and-run)
- [Limitations](#limitations)
- [License](#license)
- [Author](#author)

---

## Features

- **Near Constant Time Operations**: Achieves **amortized time complexity** of $O(\alpha(n))$ for both `find` and `unite`, where $\alpha(n)$ is the **inverse Ackermann function**, which is practically constant ($\leq 4$) for any realistic input size.
- **Optimized Implementation**: Incorporates the two most critical optimizations for DSU:
  1.  **Path Compression** (in `find`): Flattens the set tree structure during lookups.
  2.  **Union by Rank** (in `unite`): Maintains shallow tree structures by merging the smaller set into the larger one.
- **Array-Based Efficiency**: Uses simple arrays for parent and rank tracking, leveraging the speed of contiguous memory access.
- **Header-Only Design**: The entire ADT is contained within a single header file (`adt_DisjointSet.h`), simplifying integration into C projects.
- **Clear Documentation**: Each public function is thoroughly documented with descriptions, parameters, and return values.

---

## Function Overview

The `adt_DisjointSet.h` header file exposes the following public API functions for managing the set universe:

### Core Management

- `DisjointSet *init(int n)`: Initializes a new DSU structure for a universe of $n$ elements (indexed $0$ to $n-1$), where each element starts in its own distinct set.
- `DisjointSet *copy(const DisjointSet *source)`: Creates a **deep copy** of an existing DSU structure, duplicating the `parent` and `rank` arrays.
- `void clear(DisjointSet *dsu)`: Resets the DSU to its initial state, making every element its own representative again.
- `void destroy(DisjointSet *dsu)`: Frees all dynamic memory allocated for the DSU structure.

### Set Operations

- `int find(DisjointSet *dsu, int i)`: Returns the **representative** (root) of the set containing element `i`. This operation performs **Path Compression**.
- `bool unite(DisjointSet *dsu, int i, int j)`: Merges the sets containing elements `i` and `j`. This operation uses **Union-by-Rank**. Returns `true` if a merge occurred, `false` otherwise.
- `bool connected(DisjointSet *dsu, int i, int j)`: Checks if elements `i` and `j` belong to the same set by comparing their representatives.

### Utility Functions

- `void traverse(const DisjointSet *dsu)`: Prints the internal state of the DSU, showing the parent, rank, and final root for every element.

---

## Performance

The Disjoint Set structure is one of the most efficient data structures known. Its performance is measured using **amortized analysis** because `find` operations occasionally take longer (when path compression occurs), but they make subsequent operations much faster.

| Operation                    | Time Complexity (Amortized) | Notes                                                         |
| :--------------------------- | :-------------------------- | :------------------------------------------------------------ |
| `init`, `clear`              | $O(N)$                      | Requires initial array population.                            |
| `find`, `unite`, `connected` | $O(\alpha(N))$              | Practically $O(1)$ due to Path Compression and Union-by-Rank. |

Where $\alpha(N)$ is the **inverse Ackermann function**, a function that grows extremely slowly (e.g., $\alpha(N) \le 4$ for all $N < 2^{2^{65536}}$).

---

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_DisjointSet.h` header file and your testing C file (e.g., `test_DisjointSet.c`) in your project directory.

2.  **Include the Header File**
    In your C program, include the header file:

    ```c
    #include "adt_DisjointSet.h"
    ```

3.  **Compile the Code**
    Since `adt_DisjointSet.h` is a header-only ADT, you can compile your main file directly. For example, using GCC:

    ```bash
    gcc -o test_DisjointSet test_DisjointSet.c
    ```

4.  **Run the Executable**
    Execute the compiled program from your terminal:

    ```bash
    ./test_DisjointSet
    ```

5.  **Example Program**

    Here's a simple example demonstrating the core operations of the DSU:

    ```c
    #include "adt_DisjointSet.h"
    #include <stdio.h>

    int main() {
        // Initialize DSU for 5 elements (0, 1, 2, 3, 4)
        DisjointSet *dsu = init(5);

        printf("Initial State:\n");
        traverse(dsu);

        // Union sets containing 0 and 1
        unite(dsu, 0, 1);
        // Union sets containing 2 and 3
        unite(dsu, 2, 3);
        // Union sets containing 0 and 2 (merges {0, 1} and {2, 3})
        unite(dsu, 0, 2);

        printf("\nAfter Merges:\n");
        traverse(dsu);

        printf("\nIs 1 connected to 3? %s\n", connected(dsu, 1, 3) ? "Yes" : "No");
        printf("Is 1 connected to 4? %s\n", connected(dsu, 1, 4) ? "Yes" : "No");

        printf("Root of element 4: %d\n", find(dsu, 4));

        destroy(dsu);
        return 0;
    }
    ```

---

## Limitations

- **Fixed Universe**: The DSU must be initialized with a fixed number of elements $N$. It only manages elements indexed $0$ to $N-1$ and cannot dynamically add new, unmanaged elements without being re-initialized.
- **Non-Generic**: The current implementation is designed for integer indices/elements.
- **Basic Error Handling**: Functions check for `NULL` pointers and out-of-bounds indices but do not utilize C's `errno` for more detailed error logging.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name**: Zulqarnain Chishti
- **Email**: thisiszulqarnain@gmail.com
- **LinkedIn**: [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub**: [zulqarnainchishti](https://www.google.com/search?q=https://github.com/zulqarnainchishti)
