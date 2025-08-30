# AVLTree: A Self-Balancing Binary Search Tree ADT for C

## Overview

AVLTree is an efficient implementation of a self-balancing Binary Search Tree as an Abstract Data Type (ADT) in C. It's a hierarchical data structure that stores data in a sorted manner while automatically maintaining balance to ensure optimal performance. This implementation provides a comprehensive set of functions to manage the tree, analyze its properties, and perform various traversals. Its self-balancing nature guarantees that operations like search, insertion, and deletion have a time complexity of $O(log n)$, making it superior to a standard BST for large, dynamic datasets.

---

## Table of Contents

- [Features](#features)
- [Function Overview](#function-overview)
  - [Core Operations](#core-operations)
  - [Search Operations](#search-operations)
  - [Tree Properties](#tree-properties)
  - [Traversal Operations](#traversal-operations)
  - [Type Checks](#type-checks)
- [How to Compile and Run](#how-to-compile-and-run)
- [Limitations](#limitations)
- [License](#license)
- [Author](#author)

---

## Features

- **Self-Balancing Logic:** This AVL tree implementation automatically performs **rotations** (left-left, left-right, right-right, and right-left) to maintain a balanced structure. This key feature guarantees that the tree's height remains logarithmic, ensuring that core operations are always efficient.
- **Robust Node Management:** This ADT provides essential functions for managing individual nodes, including **creation**, **copying**, and **complete destruction** of the tree. These core operations ensure reliable memory handling and allow for safe manipulation of the data structure.
- **Efficient Search and Traversal:** The ADT is optimized for fast data retrieval. You can perform quick searches, find the **minimum and maximum values**, and locate a node's **predecessor** or **successor**. It also supports all standard traversal methods (**in-order, pre-order, post-order, and level-order**) to visit every node in a specific order.
- **Structural Analysis and Classification:** Beyond basic operations, the library includes a suite of functions to analyze the tree's structure. You can easily determine its **size**, **height**, and **depth**, as well as classify it as **perfect, complete, full, or symmetric**. These functions are crucial for evaluating the tree's balance and performance.
- **Node Relationship Queries:** The implementation allows you to query the relationships between nodes. You can find a node's **parent** or **sibling**, and even find the **ceiling** or **floor** value for a given number. This adds a layer of navigational utility that goes beyond simple data storage.
- **Memory-Safe Design:** The ADT is built with a focus on memory safety. All functions that allocate memory explicitly return pointers that the user must manage, and a dedicated `destroy` function helps prevent memory leaks. This design promotes responsible resource management in C programming.

---

## Function Overview

The `adt_AVLTree.h` header file exposes a public API for interacting with the AVL Tree ADT.

### Core Operations

- `AVLTree *init(const int value)`: Initializes a new AVL tree node.
- `AVLTree *destroy(AVLTree *root)`: Frees the memory for the entire tree.
- `AVLTree *copy(const AVLTree *root)`: Creates a deep copy of a tree.
- `AVLTree *insert(AVLTree *root, const int value)`: Inserts a new value while maintaining the AVL property.
- `AVLTree *discard(AVLTree *root, const int value)`: Deletes a node while rebalancing the tree.

### Search Operations

- `AVLTree *search(AVLTree *root, const int value)`: Finds a node with a specific value.
- `AVLTree *parent(AVLTree *root, const int value)`: Finds the parent of a node.
- `AVLTree *sibling(AVLTree *root, const int value)`: Finds the sibling of a node.
- `AVLTree *minimum(AVLTree *root)`: Finds the node with the minimum value.
- `AVLTree *maximum(AVLTree *root)`: Finds the node with the maximum value.
- `AVLTree *successor(AVLTree *root, const int value)`: Finds the in-order successor.
- `AVLTree *predecessor(AVLTree *root, const int value)`: Finds the in-order predecessor.
- `AVLTree *ceiling(AVLTree *root, const double value)`: Finds the smallest value greater than or equal to the given value.
- `AVLTree *floored(AVLTree *root, const double value)`: Finds the largest value less than or equal to the given value.

### Tree Properties

- `int degree(const AVLTree *root)`: Calculates the number of children for a node.
- `int size(const AVLTree *root)`: Counts the total number of nodes.
- `int external(const AVLTree *root)`: Counts the number of leaf nodes.
- `int internal(const AVLTree *root)`: Counts the number of non-leaf nodes.
- `int height(const AVLTree *root)`: Calculates the height of the tree.
- `int balance(const AVLTree *root)`: Calculates the balance factor of a node (height of left subtree - height of right subtree).
- `int depth(const AVLTree *root, const int value)`: Calculates the depth of a specific node.

### Traversal Operations

- `void preorder(const AVLTree *root)`: Prints nodes in a **Root → Left → Right** order.
- `void inorder(const AVLTree *root)`: Prints nodes in a **Left → Root → Right** order (sorted).
- `void postorder(const AVLTree *root)`: Prints nodes in a **Left → Right → Root** order.
- `void levelorder(const AVLTree *root)`: Prints nodes level by level (**Breadth-First Search**).

### Type Checks

- `bool isPerfect(const AVLTree *root)`: Checks for a perfect binary tree.
- `bool isComplete(AVLTree *root)`: Checks for a complete binary tree.
- `bool isFull(const AVLTree *root)`: Checks for a full binary tree.
- `bool isSymmetric(const AVLTree *root)`: Checks if the tree is symmetric.

---

## How to Compile and Run

1.  **Download the Library**

    Make sure you have the `adt_AVLTree.h` header file and the `test_AVLTree.c` test file in your project directory.

2.  **Include the Header File**

    In your C program (e.g., `test_AVLTree.c`), include the header file at the top:

    ```c
    #include "adt_AVLTree.h"
    ```

3.  **Compile the Code**

    Since `adt_AVLTree.h` is a header-only library, you just need to compile your main application file (e.g., `test_AVLTree.c`). For example, using GCC:

    ```bash
    gcc -o test_AVLTree test_AVLTree.c
    ```

4.  **Run the Executable**

    Execute the compiled program from your terminal:

    ```bash
    ./test_AVLTree
    ```

5.  **Example Program**

    Here's a simple example demonstrating how to build and traverse an AVL Tree:

    ```c
    #include "adt_AVLTree.h"
    #include <stdio.h>

    int main() {
        AVLTree *root = NULL;

        // Inserting nodes in an order that would unbalance a regular BST
        // The AVL Tree will automatically rebalance itself
        root = insert(root, 10);
        root = insert(root, 20);
        root = insert(root, 30); // Left rotation happens here

        printf("In-order traversal after rebalancing: ");
        inorder(root);
        printf("\n");

        printf("Height of the tree: %d\n", height(root));

        root = discard(root, 10); // Discard and rebalance
        printf("In-order traversal after discard: ");
        inorder(root);
        printf("\n");

        destroy(root);
        return 0;
    }
    ```

---

## Limitations

- **Fixed Data Type (Integers Only):** The current implementation is designed to store integer data. To handle other data types, the `data` field in the `AVLTree` struct and comparison logic within the functions would need to be modified.
- **Basic Error Handling:** Error handling is limited. For example, `init` returns `NULL` on memory allocation failure, which the caller is responsible for checking.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name:** Zulqarnain Chishti
- **Email:** thisiszulqarnain@gmail.com
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://www.google.com/search?q=https://github.com/zulqarnainchishti)
