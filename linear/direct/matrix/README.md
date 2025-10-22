## Matrix: A Mathematical Matrix Abstract Data Type in C

### Overview

Matrix is a C library for mathematical matrix operations, designed for both educational purposes and practical use. It provides a robust, user-friendly API for creating, manipulating, and performing complex calculations on matrices. The library supports a wide range of functions, from basic creation and element manipulation to advanced linear algebra operations. This project serves as a comprehensive example of implementing a mathematical data structure in C.

---

## Table of Contents

- [Features](#features)
- [Function Overview](#function-overview)
  - [Core Management](#core-management)
  - [Matrix Creation](#matrix-creation)
  - [Element Manipulation](#element-manipulation)
  - [Data Transformation](#data-transformation)
  - [Linear Algebra](#linear-algebra)
- [How to Compile and Run](#how-to-compile-and-run)
- [Limitations](#limitations)
- [License](#license)
- [Author](#author)

---

### Features

- **Dynamic Sizing**: The library handles all memory management, allowing matrices to be created and manipulated with flexible dimensions.
- **Comprehensive Operations**: It includes a wide range of functions for matrix manipulation, from fundamental tasks like **initialization**, **copying**, and **slicing** to advanced **linear algebra** and **element-wise** calculations.
- **Data Handling**: You can easily populate matrices with data from C arrays, fill them with specific values, or generate specialized matrices like **identity** or **random** matrices.
- **Field Manipulation**: The API provides dedicated functions for manipulating entire rows or columns, making it simple to **get**, **set**, **swap**, or **insert** new data fields.
- **Mathematical Toolkit**: A robust set of mathematical functions allows for operations like **dot product**, **determinant**, and **matrix inversion**, as well as **scalar** and **element-wise** transformations.
- **User-Friendly**: The library is designed with clarity in mind, and the test file includes **ANSI color codes** to provide clear, color-coded output for test results.

---

## Functions Overview

The `adt_Matrix.h` header file exposes the following public API functions:

### Core Management

- `Matrix *init(const int rows, const int columns)`: Initializes a new matrix with specified dimensions, filled with zeros.
- `void destroy(Matrix *matrix)`: Deallocates all memory associated with the matrix.
- `Matrix *copy(const Matrix *matrix)`: Creates a deep copy of the matrix.
- `Matrix *slice(const Matrix *matrix, const int row_start, const int row_end, const int col_start, const int col_end)`: Creates a new matrix containing a portion (slice) of the original.
- `Matrix *join(const Matrix *matrix1, const Matrix *matrix2, const bool horizontal)`: Concatenates two matrices horizontally or vertically.
- `void traverse(const Matrix *matrix)`: Prints the elements of the matrix to the console.

### Matrix Creation

- `Matrix *fill(const int rows, const int columns, const double value)`: Creates a new matrix filled with a specified value.
- `Matrix *random(const int rows, const int columns, const double min, const double max)`: Creates a new matrix with random values within a specified range.
- `Matrix *identity(const int size)`: Creates a new identity matrix of size `n x n`.
- `Matrix *meshgrid(const int rows, const int cols, double (*const func)(double, double))`: Creates a 2D grid of values by applying a function to row and column indices.
- `Matrix *populate(const int rows, const int columns, const double *array)`: Populates a new matrix from a 1D C-style array.
- `double *flatten(const Matrix *matrix)`: Converts a matrix into a 1D C-style array.
- `Matrix *reshape(const Matrix *matrix, const int new_rows, const int new_columns)`: Reshapes a matrix into new dimensions.

### Element Manipulation

- `double get(const Matrix *matrix, const int row, const int col)`: Retrieves the element at a specific row and column.
- `double *getField(const Matrix *matrix, const int index, const bool column)`: Retrieves a row or column as a C-style array.
- `void set(Matrix *matrix, const int row, const int col, const double value)`: Sets the element at a specific row and column to a new value.
- `void setField(Matrix *matrix, const int index, const bool column, const double *array)`: Sets an entire row or column from a C-style array.
- `void swapField(Matrix *matrix, const int field1, const int field2, const bool column)`: Swaps two rows or columns.
- `Matrix *insertField(const Matrix *matrix, const int index, const bool column, const double *array)`: Inserts a new row or column at a specific index.
- `Matrix *discardField(const Matrix *matrix, const int index, const bool column)`: Removes a row or column at a specific index.

### Data Transformation

- `Matrix *transpose(const Matrix *matrix)`: Transposes the matrix.
- `Matrix *shuffle(const Matrix *matrix)`: Randomly shuffles the elements of the matrix.
- `Matrix *scalar(const Matrix *matrix, double (*const func)(double))`: Applies a scalar function to each element of a matrix.
- `double *scalarField(const Matrix *matrix, const int index, const bool column, double (*const func)(double))`: Applies a scalar function to each element of a row or column.
- `Matrix *elementwise(const Matrix *matrix1, const Matrix *matrix2, double (*const func)(double, double))`: Applies a binary function to each element of two matrices.
- `double *elementwiseField(const Matrix *matrix, const int index, const bool column, const double *array, double (*const func)(double, double))`: Applies a binary function between a field and a C-style array.

### Linear Algebra

- `Matrix *dot(const Matrix *matrix1, const Matrix *matrix2)`: Computes the dot product of two matrices.
- `double determinant(const Matrix *matrix)`: Computes the determinant of a square matrix.
- `Matrix *inverse(const Matrix *matrix)`: Computes the inverse of a square matrix.

---

## How to Compile and Run

1.  **Download the Library**

    To begin using the library, ensure you have the `adt_Matrix.h` header file and the `test_Matrix.c` test file in your project directory.

    _Note: `adt_Matrix.h` is a header-only library, meaning all function implementations are directly in the header._

2.  **Include the Header File**

    In your C program (e.g., `test_Matrix.c`), include the header:

    ```c
    #include "adt_Matrix.h"
    ```

3.  **Compile the Code**

    Since `adt_Matrix.h` is a header-only library, you just need to compile your main application file (e.g., `test_Matrix.c`) and link against the math library. For example, if you're using GCC, compile your program like this:

    ```bash
    gcc -o test_Matrix test_Matrix.c
    ```

    _This command will compile your source file (`test_Matrix.c`) and link it with the necessary math functions to produce the final executable (`test_Matrix`)._

4.  **Run the Executable**

    After successful compilation, run the program from the terminal:

    ```bash
    ./test_Matrix
    ```

5.  **Example Program**

    Here's a quick example demonstrating basic matrix creation and operations:

    ```c
    #include "adt_Matrix.h"
    #include <stdio.h>

    int main() {
        Matrix *myMatrix = init(2, 2);

        populate(myMatrix, 2, 2, (double[]){1, 2, 3, 4});

        printf("Original matrix:\n");
        traverse(myMatrix);

        double *row_data = getField(myMatrix, 0, false);
        printf("\nRow 0: ");
        for (int i = 0; i < myMatrix->columns; i++) {
            printf("%.2f ", row_data[i]);
        }
        printf("\n");
        free(row_data);

        destroy(myMatrix);
        return 0;
    }
    ```

---

## Limitations

- **Fixed Data Type:** This implementation is designed exclusively for `double`-precision floating-point numbers. To support other numeric types, the function signatures and `typedef` would need to be changed.
- **Square Matrices:** Functions for `determinant` and `inverse` only work with square matrices and will return `NULL` or `0` for non-square inputs.
- **No Direct Error Codes:** The library relies on returning `NULL` for invalid operations (e.g., mismatched dimensions for dot product) or printing to `stderr` and exiting on critical failures.
- **Performance:** While the code is functional, it is not optimized for high-performance computing (HPC) or multi-threading. It is designed for clarity and correctness over raw speed.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Author

- **Name:** Zulqarnain Chishti
- **Email:** thisiszulqarnain@gmail.com
- **LinkedIn:** [Zulqarnain Chishti](https://www.linkedin.com/in/zulqarnain-chishti-6731732a1/)
- **GitHub:** [zulqarnainchishti](https://www.google.com/search?q=https://github.com/zulqarnainchishti)
