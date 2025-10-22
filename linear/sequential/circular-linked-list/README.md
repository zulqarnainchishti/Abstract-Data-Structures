# CircularLinkedList: A Dynamic Circular Linked List Abstract Data Type in C

---

## Overview

The CircularLinkedList ADT offers a robust and adaptable implementation of a circular linked list in C. Crafted for dynamic storage, this ADT enables efficient insertion, deletion, and traversal of elements, providing capabilities for managing data where the collection's size can change during runtime. Its header-only design ensures straightforward integration into any C project. A key advantage of a circular linked list is that every node can be a starting point for traversal, and it's efficient for continuous cycling applications.

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

- **Header-Only Design:** Fully self-contained within a single `adt_CircularLinkedList.h` file, simplifying integration.
- **Dynamic Size:** The list grows and shrinks as elements are added or removed, adapting to data requirements.
- **Circular Structure:** The last node points back to the first node, forming a continuous cycle, which is efficient for repetitive data access.
- **Manual Memory Management:** Explicit memory allocation and deallocation for each node, ensuring control over resources.
- **Deep Copying:** Supports creating a complete, independent duplicate of an existing circular linked list, including correct `next` pointer linkages and circularity.
- **Flexible Insertions:** Provides functions for inserting at the beginning, end, specific index, or after a particular value, maintaining the circular structure.
- **Comprehensive Deletions:** Offers functions to delete from the beginning, end, specific index, or by value, with correct re-linking to preserve circularity.
- **Utility Operations:** Includes searching for elements, clearing the entire list, and an in-place reversal of the list order.

---

## Function Overview

The `adt_CircularLinkedList.h` header file exposes the following API functions:

### Core Management

- `CLLNode *create(const int value)`: Creates and returns a new `CLLNode` initialized with the given `value`. This function will exit the program if memory allocation fails.
- `CircularLinkedList init()`: Initializes and returns an empty `CircularLinkedList` structure with `tail` set to `NULL` and `length` to 0.
- `void __recClear__(CLLNode *node, CLLNode *head)`: (Helper) Recursively frees all nodes starting from the given `node` up to the `head`. Used internally by `clear()`.
- `void clear(CircularLinkedList *list)`: Clears all elements from the list, deallocating their memory, and resets the list to an empty state (`tail = NULL`, `length = 0`).
- `CLLNode *__recCopy__(const CLLNode *node, const CLLNode *original_head, CLLNode *prev_new, CLLNode **new_head_ptr)`: (Helper) Recursively copies nodes from a source node, correctly establishing the `next` pointers for the new circular list, and updating the `new_head_ptr` for the new list.
- `CircularLinkedList copy(const CircularLinkedList *list)`: Creates and returns a deep copy of the provided circular linked list. All nodes in the new list are distinct memory locations from the original.
- `void reverse(CircularLinkedList *list)`: Reverses the order of nodes in the circular linked list in-place. This operation modifies the `next` pointers of each node and updates the `tail` of the list.

### Search and Traversal

- `CLLNode *search(const CircularLinkedList *list, const int value)`: Searches the list for the first occurrence of `value`. Returns a pointer to the `CLLNode` if found, otherwise `NULL`.
- `void traverse(const CircularLinkedList *list)`: Prints the data of each node in the list starting from the head, with elements separated by `->` to indicate the flow. Prints `\n` if the list is empty.

### Insertion Operations

- `void insertAtStart(CircularLinkedList *list, const int value)`: Inserts a new node with `value` at the beginning (after the current `tail`'s `next` node) of the list. Updates the `tail->next` and maintains circularity.
- `void insertAtEnd(CircularLinkedList *list, const int value)`: Inserts a new node with `value` at the end (before the current `tail`'s `next` node) of the list. Updates the `tail` and maintains circularity.
- `void insertAtIndex(CircularLinkedList *list, const int value, const int index)`: Inserts a new node with `value` at the specified `index`. If `index <= 0`, it delegates to `insertAtStart`. If `index >= list->length`, it delegates to `insertAtEnd`. For middle insertions, it correctly updates `next` pointers of surrounding nodes and maintains circularity.
- `int insertAfterValue(CircularLinkedList *list, const int newVal, const int oldVal)`: Inserts a new node with `newVal` immediately after the first occurrence of a node containing `oldVal`. Returns `0` on success, or `-1` if `oldVal` is not found in the list. Handles updating `tail` if inserting after the last node.

### Deletion Operations

- `int deleteStart(CircularLinkedList *list)`: Deletes the first node (the node pointed to by `tail->next`) from the list. Returns the data of the deleted node. If the list is empty or invalid, returns `-1`. Correctly updates `tail->next` or sets `tail` to `NULL` for a single-element list.
- `int deleteEnd(CircularLinkedList *list)`: Deletes the last node (the `tail`) from the list. Returns the data of the deleted node. If the list is empty or invalid, returns `-1`. Correctly updates the `tail` to the new last node and maintains circularity.
- `int deleteIndex(CircularLinkedList *list, const int index)`: Deletes the node at the specified `index`. If `index <= 0`, it delegates to `deleteStart`. If `index >= list->length - 1`, it delegates to `deleteEnd`. For middle deletions, it correctly updates `next` pointers of adjacent nodes. Returns the data of the deleted node, or `-1` if the list is empty or the index is invalid.
- `int deleteValue(CircularLinkedList *list, const int value)`: Deletes the first occurrence of a node with the specified `value`. If the node to delete is the head or tail, it delegates to `deleteStart` or `deleteEnd` respectively. For middle nodes, it correctly re-links its neighbors' `next` pointers. Returns `0` on success, or `-1` if the `value` is not found or the list is empty/invalid.

---

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_CircularLinkedList.h` file and your main source file (e.g., `test_CircularLinkedList.c`) in the same directory.

2.  **Include the Header File**
    Add the following directive in your source file:

    ```c
    #include "adt_CircularLinkedList.h"
    ```

3.  **Compile the Code**
    Use any standard C compiler to compile your program. Example using GCC:

    ```bash
    gcc -o test_CircularLinkedList test_CircularLinkedList.c
    ```

    _Note: Since `adt_CircularLinkedList.h` is a header-only library, you only need to compile your main source file that includes it. No separate compilation of the ADT itself is required._

4.  **Run the Executable**
    After successful compilation:

    ```bash
    ./test_CircularLinkedList
    ```

5.  **Example Usage**

    ```c
    #include "adt_CircularLinkedList.h"
    #include <stdio.h>
    #include <stdbool.h>

    int main() {
        CircularLinkedList my_list = init(); // Initialize an empty circular linked list

        insertAtEnd(&my_list, 10);      // List: [10]
        insertAtStart(&my_list, 5);     // List: [5] -> [10]
        insertAtIndex(&my_list, 15, 1); // List: [5] -> [15] -> [10]

        printf("List after insertions: ");
        traverse(&my_list); // Expected: [5] -> [15] -> [10]

        CLLNode *found = search(&my_list, 15);
        if (found) {
            printf("Found %d in the list.\n", found->data);
        } else {
            printf("Value 15 not found.\n");
        }

        deleteStart(&my_list); // List: [15] -> [10]
        printf("List after deleting start: ");
        traverse(&my_list); // Expected: [15] -> [10]

        deleteValue(&my_list, 10); // List: [15]
        printf("List after deleting value 10: ");
        traverse(&my_list); // Expected: [15]

        reverse(&my_list); // List: [15] (no change for single element)
        printf("List after reversing: ");
        traverse(&my_list); // Expected: [15]

        clear(&my_list); // Empty the list
        printf("List after clearing: ");
        traverse(&my_list); // Expected: [empty]\n (or just a newline based on your traverse implementation)

        CircularLinkedList copied_list = copy(&my_list); // Copy an empty list
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
