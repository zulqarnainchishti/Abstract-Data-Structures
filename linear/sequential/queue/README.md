# Queue: A Fixed-Capacity Queue Abstract Data Type in C

---

## Overview

The Queue ADT is a minimalistic and efficient implementation of a first-in, first-out (FIFO) abstract data type in C using a fixed-size array. Designed with clarity and correctness in mind, this implementation allows for essential queue operations such as enqueuing, dequeuing, peeking, and traversing elements, along with proper memory management and deep copying. The header-only design allows for seamless integration into any C project without requiring separate compilation units.

---

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

---

## Features

- **Header-Only Design:** Fully self-contained within a single `adt_Queue.h` file. No separate `.c` file is needed.
- **Manual Memory Management:** Dynamically allocates memory for the internal array with user-defined capacity.
- **Deep Copying:** Allows full duplication of queue state with independent internal memory.
- **Basic Error Reporting:** Graceful error messages on queue overflows and underflows.
- **Deterministic Memory Behavior:** No resizing logic—capacity must be specified at initialization.
- **Utility Operations:** Includes inspection (`peek`), full clearing, traversal, and safe deallocation.

---

## Function Overview

The `adt_Queue.h` header file exposes the following API functions:

### Core Management

- `Queue init(const int capacity)`: Initializes a new queue with the specified `capacity`. Allocates memory for the internal array. Exits on failure.
- `Queue copy(const Queue queue)`: Returns a deep copy of the given queue, including copied contents and capacity.
- `void clear(Queue *queue)`: Resets the queue's contents without deallocating memory.
- `void destroy(Queue *queue)`: Frees the queue's allocated memory and resets internal fields.

### Status Queries

- `bool isEmpty(const Queue queue)`: Returns `true` if the queue is empty (i.e., has no elements).
- `bool isFull(const Queue queue)`: Returns `true` if the queue is full (i.e., cannot accept new elements).
- `int length(const Queue queue)`: Returns the current number of elements in the queue.

### Operations

- `void enqueue(Queue *queue, const int value)`: Adds an `int` value to the rear of the queue. Prints an overflow message if full.
- `int dequeue(Queue *queue)`: Removes the front value from the queue and returns it. Prints an underflow message if empty.
- `int peek(const Queue queue)`: Returns the current front value of the queue without modifying it. Prints an underflow message if empty.

### Diagnostics

- `void traverse(const Queue queue)`: Prints the contents of the queue in order from front to rear, followed by current size and capacity.

---

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_Queue.h` file and a corresponding test program (e.g., `test_Queue.c`) in the same directory.

2.  **Include the Header File**
    Add the following directive in your source file:

    ```c
    #include "adt_Queue.h"
    ```

3.  **Compile the Code**
    Use any standard C compiler to compile your program. Example using GCC:

    ```bash
    gcc -o test_queue test_Queue.c adt_Queue.c -Wall -Wextra -std=c11
    ```

    _Note: If `adt_Queue.h` is header-only, you might not need to explicitly include `adt_Queue.c` in the compile command if your main file includes the header._

4.  **Run the Executable**
    After successful compilation:

    ```bash
    ./test_queue
    ```

5.  **Example Usage**

    ```c
    #include "adt_Queue.h"
    #include <stdio.h>
    #include <stdbool.h> // For bool type

    int main() {
        Queue queue = init(5); // Initialize a queue with capacity 5
        enqueue(&queue, 10);
        enqueue(&queue, 20);
        enqueue(&queue, 30);

        printf("Front of queue: %d\n", peek(queue));
        printf("Dequeued: %d\n", dequeue(&queue));

        traverse(queue); // Should show remaining elements

        clear(&queue);
        printf("Is queue empty? %s\n", isEmpty(queue) ? "Yes" : "No");

        destroy(&queue); // Free allocated memory
        return 0;
    }
    ```

---

## Limitations

- **Fixed Capacity:** Queue size is fixed at initialization and does not grow dynamically.
- **No Type Generality:** This implementation handles only `int` data. For generic types, macros or void pointers would be required.
- **Manual Deallocation Required:** The caller is responsible for invoking `destroy()` to free allocated memory.
- **No Thread Safety:** This is a single-threaded implementation with no internal synchronization primitives.
- **Basic Error Handling:** Overflow and underflow conditions are reported with messages but do not raise exceptions or return explicit error codes.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name:** Zulqarnain Chishti
- **Email:** [thisiszulqarnain@gmail.com](mailto:thisiszulqarnain@gmail.com)
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
