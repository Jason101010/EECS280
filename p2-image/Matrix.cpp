// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
    assert(0 < width && width <= MAX_MATRIX_WIDTH);
    assert(0 < height && height <= MAX_MATRIX_HEIGHT);
    mat->width = width;
    mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
    os << mat->width << " " << mat->height << std::endl; 
    for (int row = 0; row < mat->height; ++row) {
        for (int col = 0; col < mat->width; ++col) {
            os << *Matrix_at(mat, row, col) << " ";
        }
        os << std::endl;
    }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
    return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
    return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
    const int* start = mat->data;
    int index = static_cast<int> (ptr - start);
    int row = index / mat->width;
    return row;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
    const int* start = mat->data;
    int index = static_cast<int> (ptr - start);
    int col = index % mat->width;
    return col;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
    assert(0 <= row && row < Matrix_height(mat));
    assert(0 <= column && column < Matrix_width(mat));

    int* ptr = mat->data;
    ptr += row * mat->width + column;
    return ptr;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
    assert(0 <= row && row < Matrix_height(mat));
    assert(0 <= column && column < Matrix_width(mat));

    const int* ptr = mat->data;
    ptr += row * mat->width + column;
    return ptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
    for (int row = 0; row < mat->height; ++row) {
        for (int col = 0; col < mat->width; ++col) {
            *Matrix_at(mat, row, col) = value;
        }
    }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
    for (int col = 0; col < mat->width; ++col) {
        *Matrix_at(mat, 0, col) = value;
    }
    for (int col = 0; col < mat->width; ++col) {
        *Matrix_at(mat, mat->height - 1, col) = value;
    }
    for (int row = 0; row < mat->height; ++row) {
        *Matrix_at(mat, row, 0) = value;
    }
    for (int row = 0; row < mat->height; ++row) {
        *Matrix_at(mat, row, mat->width - 1) = value;
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
    int max = mat->data[0];
    for (const int* ptr = mat->data;
        ptr < mat->data + mat->width * mat->height; ++ptr) {
        if (*ptr > max) {
            max = *ptr;
        }
    }
    return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
    int column_start, int column_end) {
    assert(0 <= row && row < Matrix_height(mat));
    assert(0 <= column_start && column_end <= Matrix_width(mat));
    assert(column_start < column_end);

    int min_value = *Matrix_at(mat, row, column_start);
    int min_col = column_start;
    for (int col = column_start + 1; col < column_end; ++col) {
        if (*Matrix_at(mat, row, col) < min_value) {
            min_value = *Matrix_at(mat, row, col);
            min_col = col;
        }
    }
    return min_col;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
    int column_start, int column_end) {
    assert(0 <= row && row < Matrix_height(mat));
    assert(0 <= column_start && column_end <= Matrix_width(mat));
    assert(column_start < column_end);

    int min_value = *Matrix_at(mat, row, column_start);
    for (int col = column_start + 1; col < column_end; ++col) {
        if (*Matrix_at(mat, row, col) < min_value) {
            min_value = *Matrix_at(mat, row, col);
        }
    }
    return min_value;
}