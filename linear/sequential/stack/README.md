# Stack: A Fixed-Capacity Stack Abstract Data Type in C

## Overview

The Stack ADT is a minimalistic and efficient implementation of a last-in, first-out (LIFO) abstract data type in C using a fixed-size array. Designed with clarity and correctness in mind, this implementation allows for essential stack operations such as pushing, popping, peeking, and traversing elements, along with proper memory management and deep copying. The header-only design allows for seamless integration into any C project without requiring separate compilation units.

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

- **Header-Only Design:** Fully self-contained within a single `adt_Stack.h` file. No separate `.c` file is needed.
- **Manual Memory Management:** Dynamically allocates memory for internal array with user-defined capacity.
- **Deep Copying:** Allows full duplication of stack state with independent internal memory.
- **Basic Error Reporting:** Graceful error messages on stack overflows and underflows.
- **Deterministic Memory Behavior:** No resizing logic—capacity must be specified at initialization.
- **Utility Operations:** Includes inspection (`peek`), full clearing, traversal, and safe deallocation.

## Function Overview

The `adt_Stack.h` header file exposes the following API functions:

### Core Management

- `Stack init(const int capacity)`: Initializes a new stack with the specified `capacity`. Allocates memory for internal array. Exits on failure.
- `Stack copy(const Stack stack)`: Returns a deep copy of the given stack, including copied contents and capacity.
- `void clear(Stack *stack)`: Resets the stack's contents without deallocating memory.
- `void destroy(Stack *stack)`: Frees the stack's allocated memory and resets internal fields.

### Status Queries

- `bool isEmpty(const Stack stack)`: Returns `true` if the stack is empty (i.e., has no elements).
- `bool isFull(const Stack stack)`: Returns `true` if the stack is full (i.e., cannot accept new elements).

### Operations

- `void push(Stack *stack, const int value)`: Pushes an `int` value onto the stack. Prints an overflow message if full.
- `int pop(Stack *stack)`: Pops the top value off the stack and returns it. Prints underflow message if empty.
- `int peek(const Stack stack)`: Returns the current top value of the stack without modifying it. Prints underflow message if empty.

### Diagnostics

- `void traverse(const Stack stack)`: Prints the contents of the stack in order of insertion, followed by current size and capacity.

## How to Compile and Run

1. **Download the Library**
   Ensure you have the `adt_Stack.h` file and a corresponding test program (e.g., `test_Stack.c`) in the same directory.

2. **Include the Header File**
   Add the following directive in your source file:

   ```c
   #include "adt_Stack.h"
   ```

3. **Compile the Code**
   Use any standard C compiler to compile your program. Example using GCC:

   ```bash
   gcc -o test_Stack test_Stack.c
   ```

4. **Run the Executable**
   After successful compilation:

   ```bash
   ./test_Stack
   ```

5. **Example Usage**

   ```c
   #include "adt_Stack.h"
   #include <stdio.h>

   int main() {
       Stack stack = init(5);
       push(&stack, 10);
       push(&stack, 20);
       push(&stack, 30);

       printf("Top of stack: %d\n", peek(stack));
       printf("Popped: %d\n", pop(&stack));

       traverse(stack); // Should show remaining elements

       clear(&stack);
       printf("Is stack empty? %s\n", isEmpty(stack) ? "Yes" : "No");

       destroy(&stack);
       return 0;
   }
   ```

## Limitations

- **Fixed Capacity:** Stack size is fixed at initialization and does not grow dynamically.
- **No Type Generality:** This implementation handles only `int` data. For generic types, macros or void pointers would be required.
- **Manual Deallocation Required:** Caller is responsible for invoking `destroy()` to free allocated memory.
- **No Thread Safety:** This is a single-threaded implementation with no internal synchronization primitives.
- **Basic Error Handling:** Overflow and underflow conditions are reported with messages but do not raise exceptions or return error codes.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Author

- **Name:** Zulqarnain Chishti
- **Email:** [thisiszulqarnain@gmail.com](mailto:thisiszulqarnain@gmail.com)
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://github.com/zulqarnainchishti)
