# DoublyLinkedList: A Dynamic Doubly Linked List Abstract Data Type in C

---

## Overview

The DoublyLinkedList ADT provides a robust and flexible implementation of a doubly linked list in C. Designed for dynamic storage, this ADT allows for efficient insertion, deletion, and traversal of elements, offering capabilities for managing a collection of data where the size can change during runtime. The header-only design ensures straightforward integration into any C project. Key benefits of a doubly linked list include efficient bidirectional traversal and simplified deletion of nodes without needing a separate traversal to find the previous node.

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

- **Header-Only Design:** Fully self-contained within a single `adt_DoublyLinkedList.h` file, simplifying integration.
- **Dynamic Size:** The list grows and shrinks as elements are added or removed, adapting to data requirements.
- **Bidirectional Traversal:** Each node maintains pointers (`prev` and `next`) to both the preceding and succeeding nodes, enabling efficient traversal in both forward and reverse directions.
- **Manual Memory Management:** Explicit memory allocation and deallocation for each node, ensuring control over resources.
- **Deep Copying:** Supports creating a complete, independent duplicate of an existing doubly linked list, including correct `prev` and `next` pointer linkages.
- **Flexible Insertions:** Provides functions for inserting at the beginning, end, specific index, or after a particular value, maintaining all bidirectional links.
- **Comprehensive Deletions:** Offers functions to delete from the beginning, end, specific index, or by value, with simplified re-linking due to the presence of `prev` pointers.
- **Utility Operations:** Includes searching for elements, clearing the entire list, and an in-place reversal of the list order.

---

## Function Overview

The `adt_DoublyLinkedList.h` header file exposes the following API functions:

### Core Management

- `DLLNode *create(const int value)`: Creates and returns a new `DLLNode` initialized with the given `value`. This function will exit the program if memory allocation fails.
- `DoublyLinkedList init()`: Initializes and returns an empty `DoublyLinkedList` structure with `head` and `tail` set to `NULL` and `length` to 0.
- `void __recClear__(DLLNode *node)`: (Helper) Recursively frees all nodes starting from the given `node`. Used internally by `clear()`.
- `void clear(DoublyLinkedList *list)`: Clears all elements from the list, deallocating their memory, and resets the list to an empty state (`head = NULL`, `tail = NULL`, `length = 0`).
- `DLLNode *__recCopy__(const DLLNode *node, DLLNode *prev, DLLNode **tail)`: (Helper) Recursively copies nodes from a source node, correctly establishing the `prev` and `next` pointers for the new list, and updating the `tail` pointer of the new list.
- `DoublyLinkedList copy(const DoublyLinkedList *list)`: Creates and returns a deep copy of the provided doubly linked list. All nodes in the new list are distinct memory locations from the original.
- `void reverse(DoublyLinkedList *list)`: Reverses the order of nodes in the doubly linked list in-place. This operation modifies the `next` and `prev` pointers of each node and swaps the `head` and `tail` of the list.

### Search and Traversal

- `DLLNode *search(const DoublyLinkedList *list, const int value)`: Searches the list for the first occurrence of `value`. Returns a pointer to the `DLLNode` if found, otherwise `NULL`.
- `void traverse(const DoublyLinkedList *list)`: Prints the data of each node in the list from `head` to `tail`, with elements separated by `<=>` to indicate bidirectional links. Prints `\n` if the list is empty.

### Insertion Operations

- `void insertAtStart(DoublyLinkedList *list, const int value)`: Inserts a new node with `value` at the beginning of the list. Updates the `head` and ensures correct `prev` and `next` linkages.
- `void insertAtEnd(DoublyLinkedList *list, const int value)`: Inserts a new node with `value` at the end of the list. Updates the `tail` and ensures correct `prev` and `next` linkages.
- `void insertAtIndex(DoublyLinkedList *list, const int value, const int index)`: Inserts a new node with `value` at the specified `index`. If `index <= 0`, it delegates to `insertAtStart`. If `index >= list->length`, it delegates to `insertAtEnd`. For middle insertions, it correctly updates `prev` and `next` pointers of surrounding nodes.
- `int insertAfterValue(DoublyLinkedList *list, const int newVal, const int oldVal)`: Inserts a new node with `newVal` immediately after the first occurrence of a node containing `oldVal`. Returns `0` on success, or `-1` if `oldVal` is not found in the list. Handles updating `tail` if inserting after the last node.

### Deletion Operations

- `int deleteStart(DoublyLinkedList *list)`: Deletes the first node from the list. Returns the data of the deleted node. If the list is empty or invalid, returns `-1`. Correctly updates the `head` and sets the `prev` of the new head to `NULL`.
- `int deleteEnd(DoublyLinkedList *list)`: Deletes the last node from the list. Returns the data of the deleted node. If the list is empty or invalid, returns `-1`. Correctly updates the `tail` and sets the `next` of the new tail to `NULL`.
- `int deleteIndex(DoublyLinkedList *list, const int index)`: Deletes the node at the specified `index`. If `index <= 0`, it delegates to `deleteStart`. If `index >= list->length - 1`, it delegates to `deleteEnd`. For middle deletions, it correctly updates `prev` and `next` pointers of adjacent nodes. Returns the data of the deleted node, or `-1` if the list is empty or the index is invalid.
- `int deleteValue(DoublyLinkedList *list, const int value)`: Deletes the first occurrence of a node with the specified `value`. If the node to delete is the head or tail, it delegates to `deleteStart` or `deleteEnd` respectively. For middle nodes, it correctly re-links the `prev` and `next` pointers of its neighbors. Returns `0` on success, or `-1` if the `value` is not found or the list is empty/invalid.

---

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_DoublyLinkedList.h` file and your main source file (e.g., `test_DoublyLinkedList.c`) in the same directory.

2.  **Include the Header File**
    Add the following directive in your source file:

    ```c
    #include "adt_DoublyLinkedList.h"
    ```

3.  **Compile the Code**
    Use any standard C compiler to compile your program. Example using GCC:

    ```bash
    gcc -o test_DoublyLinkedList test_DoublyLinkedList.c
    ```

    _Note: Since `adt_DoublyLinkedList.h` is a header-only library, you only need to compile your main source file that includes it. No separate compilation of the ADT itself is required._

4.  **Run the Executable**
    After successful compilation:

    ```bash
    ./test_DoublyLinkedList
    ```

5.  **Example Usage**

    ```c
    #include "adt_DoublyLinkedList.h"
    #include <stdio.h>
    #include <stdbool.h>

    int main() {
        DoublyLinkedList my_list = init(); // Initialize an empty doubly linked list

        insertAtEnd(&my_list, 10);      // List: [10]
        insertAtStart(&my_list, 5);     // List: [5] <=> [10]
        insertAtIndex(&my_list, 15, 1); // List: [5] <=> [15] <=> [10]

        printf("List after insertions: ");
        traverse(&my_list); // Expected: [5] <=> [15] <=> [10]

        DLLNode *found = search(&my_list, 15);
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
        traverse(&my_list); // Expected: [empty]\n (or just a newline based on your traverse implementation)

        DoublyLinkedList copied_list = copy(&my_list); // Copy an empty list
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
- **Recursive Copy/Clear Stack Depth:** The recursive implementation of `__recClear__` and `__recCopy__` might lead to stack overflow issues for extremely large lists due to deep recursion. For typical list sizes, this should not be a concern.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name:** Zulqarnain Chishti
- **Email:** [thisiszulqarnain@gmail.com](mailto:thisiszulqarnain@gmail.com)
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
