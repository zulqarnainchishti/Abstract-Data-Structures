# BinarySearchTree: A Binary Search Tree ADT for C

## Overview

BinarySearchTree is an efficient implementation of a Binary Search Tree as an Abstract Data Type (ADT) in C. The BST is a hierarchical data structure that stores data in a sorted manner, allowing for quick search, insertion, and deletion operations. This implementation provides a comprehensive set of functions to manage the tree, analyze its properties, and perform various traversals. It's built in pure C, making it a lightweight and standalone solution for projects requiring ordered data storage.

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

- **Robust Node Management:** This BST implementation provides essential functions for managing individual nodes, including **creation**, **copying**, and **complete destruction** of the tree. These core operations ensure reliable memory handling and allow for safe manipulation of the data structure.
- **Efficient Search and Traversal:** The ADT is optimized for fast data retrieval. You can perform quick searches, find the **minimum and maximum values**, and locate a node's **predecessor** or **successor**. It also supports all standard traversal methods (**in-order, pre-order, post-order, and level-order**) to visit every node in a specific order.
- **Structural Analysis and Classification:** Beyond basic operations, the library includes a suite of functions to analyze the tree's structure. You can easily determine its **size**, **height**, and **depth**, as well as classify it as **perfect, complete, full, or degenerate**. These functions are crucial for evaluating the tree's balance and performance.
- **Node Relationship Queries:** The implementation allows you to query the relationships between nodes. You can find a node's **parent** or **sibling**, and even find the **ceiling** or **floor** value for a given number. This adds a layer of navigational utility that goes beyond simple data storage.
- **Memory-Safe Design:** The ADT is built with a focus on memory safety. All functions that allocate memory explicitly return pointers that the user must manage, and a dedicated `destroy` function helps prevent memory leaks. This design promotes responsible resource management in C programming.

---

## Function Overview

The `adt_BinarySearchTree.h` header file exposes a public API for interacting with the BST ADT.

### Core Operations

- `BinarySearchTree *init(const int value)`: Initializes a new BST node.
- `BinarySearchTree *destroy(BinarySearchTree *root)`: Frees the memory for the entire tree.
- `BinarySearchTree *copy(const BinarySearchTree *root)`: Creates a deep copy of a tree.
- `BinarySearchTree *insert(BinarySearchTree *root, const int value)`: Inserts a new value.
- `BinarySearchTree *discard(BinarySearchTree *root, const int value)`: Deletes a node.

### Search Operations

- `BinarySearchTree *search(BinarySearchTree *root, const int value)`: Finds a node with a specific value.
- `BinarySearchTree *parent(BinarySearchTree *root, const int value)`: Finds the parent of a node.
- `BinarySearchTree *sibling(BinarySearchTree *root, const int value)`: Finds the sibling of a node.
- `BinarySearchTree *minimum(BinarySearchTree *root)`: Finds the node with the minimum value.
- `BinarySearchTree *maximum(BinarySearchTree *root)`: Finds the node with the maximum value.
- `BinarySearchTree *successor(BinarySearchTree *root, const int value)`: Finds the in-order successor.
- `BinarySearchTree *predecessor(BinarySearchTree *root, const int value)`: Finds the in-order predecessor.
- `BinarySearchTree *ceiling(BinarySearchTree *root, const double value)`: Finds the smallest value greater than or equal to the given value.
- `BinarySearchTree *floored(BinarySearchTree *root, const double value)`: Finds the largest value less than or equal to the given value.

### Tree Properties

- `int degree(const BinarySearchTree *root)`: Calculates the number of children for a node.
- `int size(const BinarySearchTree *root)`: Counts the total number of nodes.
- `int external(const BinarySearchTree *root)`: Counts the number of leaf nodes.
- `int internal(const BinarySearchTree *root)`: Counts the number of non-leaf nodes.
- `int height(const BinarySearchTree *root)`: Calculates the height of the tree.
- `int depth(const BinarySearchTree *root, const int value)`: Calculates the depth of a specific node.

### Traversal Operations

- `void preorder(const BinarySearchTree *root)`: Prints nodes in a **Root → Left → Right** order.
- `void inorder(const BinarySearchTree *root)`: Prints nodes in a **Left → Root → Right** order (sorted).
- `void postorder(const BinarySearchTree *root)`: Prints nodes in a **Left → Right → Root** order.
- `void levelorder(const BinarySearchTree *root)`: Prints nodes level by level (**Breadth-First Search**).

### Type Checks

- `bool isPerfect(const BinarySearchTree *root)`: Checks for a perfect binary tree.
- `bool isComplete(BinarySearchTree *root)`: Checks for a complete binary tree.
- `bool isFull(const BinarySearchTree *root)`: Checks for a full binary tree.
- `bool isDegenerate(const BinarySearchTree *root)`: Checks for a degenerate tree.
- `bool isSkewed(const BinarySearchTree *root)`: Checks for a skewed tree (left or right).
- `bool isSymmetric(const BinarySearchTree *root)`: Checks if the tree is symmetric.
- `bool isBalanced(const BinarySearchTree *root, int *currHeight)`: Checks if the tree is balanced.

---

## How to Compile and Run

1.  **Download the Library**

    Make sure you have the `adt_BinarySearchTree.h` header file and the `test_BinarySearchTree.c` test file in your project directory.

2.  **Include the Header File**

    In your C program (e.g., `test_BinarySearchTree.c`), include the header file at the top:

    ```c
    #include "adt_BinarySearchTree.h"
    ```

3.  **Compile the Code**

    Since `adt_BinarySearchTree.h` is a header-only library, you just need to compile your main application file (e.g., `test_BinarySearchTree.c`). For example, using GCC:

    ```bash
    gcc -o test_BinarySearchTree test_BinarySearchTree.c
    ```

4.  **Run the Executable**

    Execute the compiled program from your terminal:

    ```bash
    ./test_BinarySearchTree
    ```

5.  **Example Program**

    Here's a simple example demonstrating how to build and traverse a BST:

    ```c
    #include "adt_BinarySearchTree.h"
    #include <stdio.h>

    int main() {
        BinarySearchTree *root = NULL;

        root = insert(root, 50);
        insert(root, 30);
        insert(root, 20);
        insert(root, 40);
        insert(root, 70);
        insert(root, 60);
        insert(root, 80);

        printf("In-order traversal: ");
        inorder(root);
        printf("\n");

        printf("Height of the tree: %d\n", height(root));

        discard(root, 20); // Discard a leaf
        discard(root, 70); // Discard with one child
        discard(root, 50); // Discard the root

        printf("In-order traversal after discard: ");
        inorder(root);
        printf("\n");

        destroy(root);
        return 0;
    }
    ```

---

## Limitations

- **No Self-Balancing:** This is a basic BST implementation and does not perform any self-balancing operations (like AVL or Red-Black trees). A series of insertions in ascending or descending order will result in a **degenerate tree** , leading to $O(n)$ time complexity for search, insert, and delete operations.
- **Fixed Data Type (Integers Only):** The current implementation is designed to store integer data. To handle other data types, the `data` field in the `BinarySearchTree` struct and comparison logic within the functions would need to be modified.
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
