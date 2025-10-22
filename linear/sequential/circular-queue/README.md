# CircularQueue: A Fixed-Capacity Circular Queue Abstract Data Type in C

## Overview

The CircularQueue ADT is a robust and efficient implementation of a first-in, first-out (FIFO) abstract data type in C, utilizing a fixed-size circular array. Designed for scenarios where efficient reuse of memory and constant-time operations are critical, this implementation provides essential queue functionalities like enqueuing, dequeuing, peeking, and traversing elements. It also includes proper memory management and deep copying capabilities. Its header-only design allows for straightforward integration into any C project without the need for separate compilation units.

## Table of Contents

- [Features](#features)
- [Function Overview](#function-overview)
  - [Core Management](#core-management)
  - [Status Queries](#status-queries)
  - [Operations](#operations)
  - [Diagnostics](#diagnostics)
- [How to Compile and Run](#how-to-compile-and-run)
- [Limitations](#limitations)
- [License](#license)
- [Author](#author)

## Features

- **Header-Only Design:** Fully self-contained within a single `adt_CircularQueue.h` file. No separate `.c` file is needed.
- **Manual Memory Management:** Dynamically allocates memory for the internal array with user-defined capacity.
- **Deep Copying:** Allows full duplication of queue state with independent internal memory.
- **Basic Error Reporting:** Provides clear error messages on queue overflows and underflows.
- **Deterministic Memory Behavior:** No resizing logic—capacity must be specified at initialization.
- **Efficient Circular Behavior:** Maximizes array utilization by wrapping around indices.
- **Utility Operations:** Includes inspection (`peek`), full clearing, traversal, and safe deallocation.

## Function Overview

The `adt_CircularQueue.h` header file exposes the following API functions:

### Core Management

- `CircularQueue init(int capacity)`: Initializes a new circular queue with the specified logical `capacity`. Allocates memory for the internal array. Exits on failure.
- `CircularQueue copy(const CircularQueue queue)`: Returns a deep copy of the given circular queue, including copied contents and capacity.
- `void clear(CircularQueue *queue)`: Resets the queue's contents without deallocating memory, making it empty.
- `void destroy(CircularQueue *queue)`: Frees the queue's allocated memory and resets internal fields.

### Status Queries

- `bool isEmpty(const CircularQueue queue)`: Returns `true` if the circular queue is empty (i.e., has no elements).
- `bool isFull(const CircularQueue queue)`: Returns `true` if the circular queue is full (i.e., cannot accept new elements).
- `int length(const CircularQueue queue)`: Returns the current number of elements in the circular queue.

### Operations

- `void enqueue(CircularQueue *queue, const int value)`: Adds an `int` value to the rear of the circular queue. Prints an overflow message if full.
- `int peek(const CircularQueue queue)`: Returns the current front value of the circular queue without modifying it. Prints an underflow message if empty.
- `int dequeue(CircularQueue *queue)`: Removes and returns the front value from the circular queue. Prints an underflow message if empty.

### Diagnostics

- `void traverse(const CircularQueue queue)`: Prints the contents of the circular queue from front to rear, followed by the current size and logical capacity.

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_CircularQueue.h` file and a corresponding test program (e.g., `test_CircularQueue.c`) in the same directory.

2.  **Include the Header File**
    Add the following directive in your source file:

    ```c
    #include "adt_CircularQueue.h"
    ```

3.  **Compile the Code**
    Use any standard C compiler to compile your program. Example using GCC:

    ```bash
    gcc -o test_CircularQueue test_CircularQueue.c
    ```

4.  **Run the Executable**
    After successful compilation:

    ```bash
    ./test_CircularQueue
    ```

5.  **Example Usage**

    ```c
    #include "adt_CircularQueue.h"
    #include <stdio.h>

    int main() {
        CircularQueue queue = init(5); // Logical capacity of 5
        enqueue(&queue, 10);
        enqueue(&queue, 20);
        enqueue(&queue, 30);

        printf("Front of queue: %d\n", peek(queue));
        printf("Dequeued: %d\n", dequeue(&queue));

        traverse(queue); // Should show remaining elements

        clear(&queue);
        printf("Is queue empty? %s\n", isEmpty(queue) ? "Yes" : "No");

        destroy(&queue);
        return 0;
    }
    ```

## Limitations

- **Fixed Capacity:** The queue size is fixed at initialization and does not grow dynamically.
- **No Type Generality:** This implementation handles only `int` data. For generic types, macros or `void` pointers would be required.
- **Manual Deallocation Required:** The caller is responsible for invoking `destroy()` to free allocated memory.
- **No Thread Safety:** This is a single-threaded implementation with no internal synchronization primitives.
- **Basic Error Handling:** Overflow and underflow conditions are reported with messages but do not raise exceptions or return error codes.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Author

- **Name:** Zulqarnain Chishti
- **Email:** [thisiszulqarnain@gmail.com](mailto:thisiszulqarnain@gmail.com)
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
