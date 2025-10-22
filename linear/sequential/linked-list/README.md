# LinkedList: A Dynamic Singly Linked List Abstract Data Type in C

---

## Overview

The LinkedList ADT provides a robust and flexible implementation of a singly linked list in C. Designed for dynamic storage, this ADT allows for efficient insertion, deletion, and traversal of elements, offering capabilities for managing a collection of data where the size can change during runtime. The header-only design ensures straightforward integration into any C project.

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

- **Header-Only Design:** Fully self-contained within a single `adt_LinkedList.h` file, simplifying integration.
- **Dynamic Size:** The list grows and shrinks as elements are added or removed, adapting to data requirements.
- **Manual Memory Management:** Explicit memory allocation and deallocation for each node, ensuring control over resources.
- **Deep Copying:** Supports creating a complete, independent duplicate of an existing linked list.
- **Flexible Insertions:** Provides functions for inserting at the beginning, end, specific index, or after a particular value.
- **Comprehensive Deletions:** Offers functions to delete from the beginning, end, specific index, or by value.
- **Utility Operations:** Includes searching for elements, clearing the entire list, and reversing the list order.

---

## Function Overview

The `adt_LinkedList.h` header file exposes the following API functions:

### Core Management

- `LLNode *create(int value)`: Creates and returns a new `LLNode` initialized with the given `value`. Exits on memory allocation failure.
- `LinkedList init()`: Initializes and returns an empty `LinkedList` structure.
- `void __recClear__(LLNode *node)`: (Helper) Recursively frees all nodes starting from the given node.
- `void clear(LinkedList *list)`: Clears all elements from the list and frees their memory. Resets the list to an empty state.
- `LLNode *__recCopy__(const LLNode *node)`: (Helper) Recursively copies nodes from a source node.
- `LinkedList copy(const LinkedList *list)`: Creates and returns a deep copy of the provided linked list.
- `void reverse(LinkedList *list)`: Reverses the order of nodes in the linked list in-place.

### Search and Traversal

- `LLNode *search(const LinkedList *list, const int value)`: Searches the list for the first occurrence of `value` and returns a pointer to the node if found, otherwise `NULL`.
- `void traverse(const LinkedList *list)`: Prints the data of each node in the list from head to tail.

### Insertion Operations

- `void insertAtStart(LinkedList *list, const int value)`: Inserts a new node with `value` at the beginning of the list.
- `void insertAtEnd(LinkedList *list, const int value)`: Inserts a new node with `value` at the end of the list.
- `void insertAtIndex(LinkedList *list, const int value, const int index)`: Inserts a new node with `value` at the specified `index`. Handles out-of-bounds indices by inserting at the start or end.
- `int insertAfterValue(LinkedList *list, const int newVal, const int oldVal)`: Inserts a new node with `newVal` after the first occurrence of a node containing `oldVal`. Returns 0 on success, -1 if `oldVal` is not found.

### Deletion Operations

- `int deleteStart(LinkedList *list)`: Deletes the first node in the list. Returns the data of the deleted node, or -1 if the list is empty.
- `int deleteEnd(LinkedList *list)`: Deletes the last node in the list. Returns the data of the deleted node, or -1 if the list is empty.
- `int deleteIndex(LinkedList *list, const int index)`: Deletes the node at the specified `index`. Returns the data of the deleted node, or -1 if the list is empty. Handles out-of-bounds indices by deleting from the start or end.
- `int deleteValue(LinkedList *list, const int value)`: Deletes the first node containing the specified `value`. Returns 0 on success, -1 if `value` is not found or list is empty.

---

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_LinkedList.h` file and a corresponding test program (e.g., `test_LinkedList.c`) in the same directory.

2.  **Include the Header File**
    Add the following directive in your source file:

    ```c
    #include "adt_LinkedList.h"
    ```

3.  **Compile the Code**
    Use any standard C compiler to compile your program. Example using GCC:

    ```bash
    gcc -o test_LinkedList test_LinkedList.c
    ```

    _Note: Since `adt_LinkedList.h` is header-only, you only need to compile your main source file that includes it._

4.  **Run the Executable**
    After successful compilation:

    ```bash
    ./test_LinkedList
    ```

5.  **Example Usage**

    ```c
    #include "adt_LinkedList.h"
    #include <stdio.h>
    #include <stdbool.h>

    int main() {
        LinkedList my_list = init(); // Initialize an empty linked list

        insertAtEnd(&my_list, 10);
        insertAtStart(&my_list, 5);
        insertAtIndex(&my_list, 15, 1); // List: 5 -> 15 -> 10

        printf("List after insertions: ");
        traverse(&my_list);

        LLNode *found = search(&my_list, 15);
        if (found) {
            printf("Found %d in the list.\n", found->data);
        }

        deleteStart(&my_list); // List: 15 -> 10
        printf("List after deleting start: ");
        traverse(&my_list);

        deleteValue(&my_list, 10); // List: 15
        printf("List after deleting value 10: ");
        traverse(&my_list);

        clear(&my_list); // Empty the list
        printf("List after clearing: ");
        traverse(&my_list); // Should print only a newline

        LinkedList copied_list = copy(&my_list); // Copy an empty list
        insertAtEnd(&copied_list, 100);
        printf("Copied list: ");
        traverse(&copied_list);

        clear(&copied_list); // Free memory for copied_list

        return 0;
    }
    ```

---

## Limitations

- **No Type Generality:** This implementation handles only `int` data. For generic types, a more complex approach using `void` pointers and function pointers for data manipulation would be required.
- **Manual Memory Management:** The user is responsible for understanding and managing memory by calling `clear()` when the list is no longer needed to prevent memory leaks.
- **Single-Threaded:** This implementation does not include any internal synchronization mechanisms, making it unsuitable for direct use in multi-threaded environments without external locking.
- **Basic Error Handling:** Functions typically return -1 for errors or `NULL` for not found, but comprehensive error codes or exceptions are not implemented.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name:** Zulqarnain Chishti
- **Email:** [thisiszulqarnain@gmail.com](mailto:thisiszulqarnain@gmail.com)
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
