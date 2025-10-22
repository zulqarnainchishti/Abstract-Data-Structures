# CircularDoublyLinkedList: A Dynamic Circular Doubly Linked List Abstract Data Type in C

---

## Overview

The CircularDoublyLinkedList ADT provides a robust and adaptable implementation of a circular doubly linked list in C. Designed for dynamic storage, this ADT enables efficient insertion, deletion, and traversal of elements, offering capabilities for managing data where the collection's size can change during runtime. Its header-only design ensures straightforward integration into any C project. A key advantage of a circular doubly linked list is its ability to traverse in both forward and backward directions from any node, making it highly efficient for continuous cycling and bidirectional data access applications.

---

## Table of Contents

- [Features](#features)
- [Function Overview](#function-overview)
  - [Core Management](#core-management)
  - [Search and Traversal](#search-and-traversal)
  - [Insertion Operations](#insertion-operations)
  - [Deletion Operations](#deletion-operations)
- [How to Compile and Run](#how-to-compile-and-run)
- [Limitations](#limitations)
- [License](#license)
- [Author](#author)

---

## Features

- **Header-Only Design:** Fully self-contained within a single `adt_CircularDoublyLinkedList.h` file, simplifying integration.
- **Dynamic Size:** The list grows and shrinks as elements are added or removed, adapting to data requirements.
- **Circular and Doubly Linked Structure:** The last node points back to the first node, and each node maintains pointers to both its previous and next nodes, forming a continuous bidirectional cycle. This allows for efficient traversal in both directions.
- **Manual Memory Management:** Explicit memory allocation and deallocation for each node, ensuring precise control over resources.
- **Deep Copying:** Supports creating a complete, independent duplicate of an existing circular doubly linked list, including correct `prev` and `next` pointer linkages and circularity.
- **Flexible Insertions:** Provides functions for inserting at the beginning, end, specific index, or after a particular value, maintaining the circular and bidirectional structure.
- **Comprehensive Deletions:** Offers functions to delete from the beginning, end, specific index, or by value, with correct re-linking of `prev` and `next` pointers to preserve circularity.
- **Utility Operations:** Includes searching for elements, clearing the entire list, and an in-place reversal of the list order.

---

## Function Overview

The `adt_CircularDoublyLinkedList.h` header file exposes the following API functions:

### Core Management

- `CDLLNode *create(int value)`: Creates and returns a new `CDLLNode` initialized with the given `value`. This function will exit the program if memory allocation fails.
- `CircularDoublyLinkedList init()`: Initializes and returns an empty `CircularDoublyLinkedList` structure with `head` set to `NULL` and `length` to 0.
- `void clear(CircularDoublyLinkedList *list)`: Clears all elements from the list, deallocating their memory, and resets the list to an empty state (`head = NULL`, `length = 0`).
- `CircularDoublyLinkedList copy(const CircularDoublyLinkedList *list)`: Creates and returns a deep copy of the provided circular doubly linked list. All nodes in the new list are distinct memory locations from the original.
- `void reverse(CircularDoublyLinkedList *list)`: Reverses the order of nodes in the circular doubly linked list in-place. This operation modifies the `prev` and `next` pointers of each node and updates the `head` of the list.

### Search and Traversal

- `CDLLNode *search(const CircularDoublyLinkedList *list, int value)`: Searches the list for the first occurrence of `value`. Returns a pointer to the `CDLLNode` if found, otherwise `NULL`.
- `void traverse(CircularDoublyLinkedList *list)`: Prints the data of each node in the list starting from the head, with elements separated by `<=>` to indicate the bidirectional flow. Prints `[empty]` if the list is empty.

### Insertion Operations

- `void insertAtStart(CircularDoublyLinkedList *list, int value)`: Inserts a new node with `value` at the beginning of the list. Updates the `head`, the new node's `prev` and `next` pointers, and maintains circularity.
- `void insertAtEnd(CircularDoublyLinkedList *list, int value)`: Inserts a new node with `value` at the end of the list. Updates the new node's `prev` and `next` pointers, and maintains circularity.
- `void insertAtIndex(CircularDoublyLinkedList *list, int value, int index)`: Inserts a new node with `value` at the specified `index`. If `index <= 0`, it delegates to `insertAtStart`. If `index >= list->length`, it delegates to `insertAtEnd`. For middle insertions, it correctly updates `prev` and `next` pointers of surrounding nodes and maintains circularity.
- `int insertAfterValue(CircularDoublyLinkedList *list, int newVal, int oldVal)`: Inserts a new node with `newVal` immediately after the first occurrence of a node containing `oldVal`. Returns `0` on success, or `-1` if `oldVal` is not found in the list. Handles updating pointers correctly to maintain bidirectionality.

### Deletion Operations

- `int deleteStart(CircularDoublyLinkedList *list)`: Deletes the first node (the `head`) from the list. Returns the data of the deleted node. If the list is empty or invalid, returns `-1`. Correctly updates the `head` and maintains circularity.
- `int deleteEnd(CircularDoublyLinkedList *list)`: Deletes the last node (the `head->prev`) from the list. Returns the data of the deleted node. If the list is empty or invalid, returns `-1`. Correctly updates the new last node and maintains circularity.
- `int deleteIndex(CircularDoublyLinkedList *list, int index)`: Deletes the node at the specified `index`. If `index <= 0`, it delegates to `deleteStart`. If `index >= list->length - 1`, it delegates to `deleteEnd`. For middle deletions, it correctly updates `prev` and `next` pointers of adjacent nodes. Returns the data of the deleted node, or `-1` if the list is empty or the index is invalid.
- `int deleteValue(CircularDoublyLinkedList *list, int value)`: Deletes the first occurrence of a node with the specified `value`. If the node to delete is the head or tail, it delegates to `deleteStart` or `deleteEnd` respectively. For middle nodes, it correctly re-links its neighbors' `prev` and `next` pointers. Returns `0` on success, or `-1` if the `value` is not found or the list is empty/invalid.

---

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_CircularDoublyLinkedList.h` file and your main source file (e.g., `test_CircularDoublyLinkedList.c`) in the same directory.

2.  **Include the Header File**
    Add the following directive in your source file:

    ```c
    #include "adt_CircularDoublyLinkedList.h"
    ```

3.  **Compile the Code**
    Use any standard C compiler to compile your program. Example using GCC:

    ```bash
    gcc -o test_CircularDoublyLinkedList test_CircularDoublyLinkedList.c
    ```

    _Note: Since `adt_CircularDoublyLinkedList.h` is a header-only library, you only need to compile your main source file that includes it. No separate compilation of the ADT itself is required._

4.  **Run the Executable**
    After successful compilation:

    ```bash
    ./test_CircularDoublyLinkedList
    ```

5.  **Example Usage**

    ```c
    #include "adt_CircularDoublyLinkedList.h"
    #include <stdio.h>
    #include <stdbool.h>

    int main() {
        CircularDoublyLinkedList my_list = init(); // Initialize an empty circular doubly linked list

        insertAtEnd(&my_list, 10);      // List: [10]
        insertAtStart(&my_list, 5);     // List: [5] <=> [10]
        insertAtIndex(&my_list, 15, 1); // List: [5] <=> [15] <=> [10]

        printf("List after insertions: ");
        traverse(&my_list); // Expected: [5] <=> [15] <=> [10]

        CDLLNode *found = search(&my_list, 15);
        if (found) {
            printf("Found %d in the list.\n", found->data);
        } else {
            printf("Value 15 not found.\n");
        }

        deleteStart(&my_list); // List: [15] <=> [10]
        printf("List after deleting start: ");
        traverse(&my_list); // Expected: [15] <=> [10]

        deleteValue(&my_list, 10); // List: [15]
        printf("List after deleting value 10: ");
        traverse(&my_list); // Expected: [15]

        reverse(&my_list); // List: [15] (no change for single element)
        printf("List after reversing: ");
        traverse(&my_list); // Expected: [15]

        clear(&my_list); // Empty the list
        printf("List after clearing: ");
        traverse(&my_list); // Expected: [empty]\n

        CircularDoublyLinkedList copied_list = copy(&my_list); // Copy an empty list
        insertAtEnd(&copied_list, 100);
        printf("Copied list: ");
        traverse(&copied_list); // Expected: [100]

        clear(&copied_list); // Free memory for copied_list

        return 0;
    }
    ```

---

## Limitations

- **No Type Generality:** This implementation is designed to handle only `int` data. For generic types, a more complex approach using `void` pointers and function pointers for data manipulation would be required.
- **Manual Memory Management:** The user is explicitly responsible for managing memory by calling `clear()` when the list is no longer needed to prevent memory leaks.
- **Single-Threaded:** This implementation does not include any internal synchronization mechanisms and is not thread-safe. It is unsuitable for direct use in multi-threaded environments without external locking.
- **Basic Error Handling:** Functions typically return `-1` for errors or `NULL` for not found. More comprehensive error codes or exception-like mechanisms are not implemented.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name:** Zulqarnain Chishti
- **Email:** [thisiszulqarnain@gmail.com](mailto:thisiszulqarnain@gmail.com)
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
