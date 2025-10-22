# Deque: A Fixed-Capacity Double-Ended Queue Abstract Data Type in C

## Overview

The Deque ADT is a robust and efficient implementation of a double-ended queue (deque) abstract data type in C, utilizing a fixed-size array. Designed for scenarios where additions and removals are needed from both ends, this implementation provides essential deque functionalities like enqueuing and dequeuing from the front and rear, peeking, and traversing elements. It also includes proper memory management and deep copying capabilities. Its header-only design allows for straightforward integration into any C project without the need for separate compilation units.

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

- **Header-Only Design:** Fully self-contained within a single `adt_Deque.h` file. No separate `.c` file is needed.
- **Manual Memory Management:** Dynamically allocates memory for the internal array with user-defined capacity.
- **Deep Copying:** Allows full duplication of deque state with independent internal memory.
- **Basic Error Reporting:** Provides clear error messages on deque overflows and underflows.
- **Deterministic Memory Behavior:** No resizing logic—capacity must be specified at initialization.
- **Bidirectional Operations:** Efficiently adds and removes elements from both the front and rear.
- **Utility Operations:** Includes inspection (`peekFront`, `peekRear`), full clearing, traversal, and safe deallocation.

---

## Function Overview

The `adt_Deque.h` header file exposes the following API functions:

### Core Management

- `Deque init(int capacity)`: Initializes a new deque with the specified `capacity`. Allocates memory for the internal array. Exits on failure.
- `Deque copy(const Deque queue)`: Returns a deep copy of the given deque, including copied contents and capacity.
- `void clear(Deque *queue)`: Resets the deque's contents without deallocating memory, making it empty.
- `void destroy(Deque *vector)`: Frees the deque's allocated memory and resets internal fields.

### Status Queries

- `bool isEmpty(const Deque queue)`: Returns `true` if the deque is empty (i.e., has no elements).
- `bool isFrontFull(const Deque queue)`: Returns `true` if the front end of the deque is full (i.e., no more elements can be added from the front).
- `bool isRearFull(const Deque queue)`: Returns `true` if the rear end of the deque is full (i.e., no more elements can be added from the rear).

### Operations

- `void enqueueFront(Deque *queue, int value)`: Adds an `int` value to the front of the deque. Prints an overflow message if full.
- `int peekFront(const Deque queue)`: Returns the current front value of the deque without modifying it. Prints an underflow message if empty.
- `int dequeueFront(Deque *queue)`: Removes and returns the front value from the deque. Prints an underflow message if empty.
- `void enqueueRear(Deque *queue, int value)`: Adds an `int` value to the rear of the deque. Prints an overflow message if full.
- `int peekRear(const Deque queue)`: Returns the current rear value of the deque without modifying it. Prints an underflow message if empty.
- `int dequeueRear(Deque *queue)`: Removes and returns the rear value from the deque. Prints an underflow message if empty.

### Diagnostics

- `void traverse(const Deque queue)`: Prints the contents of the deque from front to rear, followed by the current size and total capacity.

---

## How to Compile and Run

1.  **Download the Library**
    Ensure you have the `adt_Deque.h` file and a corresponding test program (e.g., `test_Deque.c`) in the same directory.

2.  **Include the Header File**
    Add the following directive in your source file:

    ```c
    #include "adt_Deque.h"
    ```

3.  **Compile the Code**
    Use any standard C compiler to compile your program. Example using GCC:

    ```bash
    gcc -o test_Deque test_Deque.c
    ```

4.  **Run the Executable**
    After successful compilation:

    ```bash
    ./test_Deque
    ```

5.  **Example Usage**

    ```c
    #include "adt_Deque.h"
    #include <stdio.h>

    int main() {
        Deque deque = init(10); // Capacity of 10

        enqueueRear(&deque, 10);
        enqueueRear(&deque, 20);
        enqueueFront(&deque, 5); // Deque: [5 10 20]

        printf("Front of deque: %d\n", peekFront(deque)); // Expected: 5
        printf("Rear of deque: %d\n", peekRear(deque));   // Expected: 20

        printf("Dequeued from front: %d\n", dequeueFront(&deque)); // Expected: 5
        printf("Dequeued from rear: %d\n", dequeueRear(&deque));   // Expected: 20

        traverse(deque); // Should show remaining elements [10]

        clear(&deque);
        printf("Is deque empty? %s\n", isEmpty(deque) ? "Yes" : "No"); // Expected: Yes

        destroy(&deque);
        return 0;
    }
    ```

---

## Limitations

- **Fixed Capacity:** The deque size is fixed at initialization and does not grow dynamically.
- **No Type Generality:** This implementation handles only `int` data. For generic types, macros or `void` pointers would be required.
- **Manual Deallocation Required:** The caller is responsible for invoking `destroy()` to free allocated memory.
- **No Thread Safety:** This is a single-threaded implementation with no internal synchronization primitives.
- **Basic Error Handling:** Overflow and underflow conditions are reported with messages but do not raise exceptions or return error codes.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name:** Zulqarnain Chishti
- **Email:** [thisiszulqarnain@gmail.com](mailto:thisiszulqarnain@gmail.com)
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
