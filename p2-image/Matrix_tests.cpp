// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;

TEST(test_Matrix_init) {
    Matrix* mat1 = new Matrix;
    const int width = 1;
    const int height = MAX_MATRIX_HEIGHT;
    Matrix_init(mat1, width, height);  

    ASSERT_EQUAL(width, Matrix_width(mat1));
    ASSERT_EQUAL(height, Matrix_height(mat1));

    delete mat1;

    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    Matrix_init(mat2, width2, height2);

    ASSERT_EQUAL(width2, Matrix_width(mat2));
    ASSERT_EQUAL(height2, Matrix_height(mat2));

    delete mat2;

    Matrix* mat3 = new Matrix;
    const int width3 = MAX_MATRIX_WIDTH;
    const int height3 = MAX_MATRIX_HEIGHT;
    Matrix_init(mat3, width3, height3);

    ASSERT_EQUAL(width3, Matrix_width(mat3));
    ASSERT_EQUAL(height3, Matrix_height(mat3));

    delete mat3;

    Matrix* mat4 = new Matrix;
    const int width4 = MAX_MATRIX_WIDTH;
    const int height4 = 1;
    Matrix_init(mat4, width4, height4);

    ASSERT_EQUAL(width4, Matrix_width(mat4));
    ASSERT_EQUAL(height4, Matrix_height(mat4));

    delete mat4;
}

TEST(test_Matrix_width_height) {
    Matrix* mat1 = new Matrix;
    const int width = MAX_MATRIX_WIDTH;
    const int height = 1;
    Matrix_init(mat1, width, height);  

    ASSERT_EQUAL(width, Matrix_width(mat1));
    ASSERT_EQUAL(height, Matrix_height(mat1));
  

    delete mat1;

    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    Matrix_init(mat2, width2, height2);

    ASSERT_EQUAL(width2, Matrix_width(mat2));
    ASSERT_EQUAL(height2, Matrix_height(mat2));

    delete mat2;

    Matrix* mat3 = new Matrix;
    const int width3 = MAX_MATRIX_WIDTH;
    const int height3 = MAX_MATRIX_HEIGHT;
    Matrix_init(mat3, width3, height3);

    ASSERT_EQUAL(width3, Matrix_width(mat3));
    ASSERT_EQUAL(height3, Matrix_height(mat3));

    delete mat3;
}


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
    Matrix* mat = new Matrix;

    const int width = 3;
    const int height = 5;
    const int value = -42;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }

    delete mat;

    Matrix* mat2 = new Matrix;

    const int width2 = 1;
    const int height2 = 1;
    const int value2 = 25;
    Matrix_init(mat2, width2, height2);
    Matrix_fill(mat2, value2);

    for (int r = 0; r < height2; ++r) {
        for (int c = 0; c < width2; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat2, r, c), value2);
        }
    }

    delete mat2;

    Matrix* mat3 = new Matrix;

    const int width3 = MAX_MATRIX_WIDTH;
    const int height3 = MAX_MATRIX_HEIGHT;
    const int value3 = 25;
    Matrix_init(mat3, width3, height3);
    Matrix_fill(mat3, value3);

    for (int r = 0; r < height3; ++r) {
        for (int c = 0; c < width3; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat3, r, c), value3);
        }
    }

    delete mat3;

    Matrix* mat4 = new Matrix;

    const int width4 = 1;
    const int height4 = MAX_MATRIX_HEIGHT;
    const int value4 = 255;
    Matrix_init(mat4, width4, height4);
    Matrix_fill(mat4, value4);

    for (int r = 0; r < height4; ++r) {
        for (int c = 0; c < width4; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat4, r, c), value4);
        }
    }

    delete mat4;

    Matrix* mat5 = new Matrix;

    const int width5 = MAX_MATRIX_WIDTH;
    const int height5 = 1;
    const int value5 = 255;
    Matrix_init(mat5, width5, height5);
    Matrix_fill(mat5, value5);

    for (int r = 0; r < height5; ++r) {
        for (int c = 0; c < width5; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat5, r, c), value5);
        }
    }

    delete mat5;
}



TEST(test_Matrix_print) {
    Matrix* mat1 = new Matrix;
    const int width = 3;
    const int height = 5;
    Matrix_init(mat1, width, height);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            *Matrix_at(mat1, row, col) = row * width + col;
        }
    }

    ostringstream output;
    Matrix_print(mat1, cout);
    Matrix_print(mat1, output);

    ostringstream correct;
    correct << "3 5" << endl;
    correct << "0 1 2 " << endl;
    correct << "3 4 5 " << endl;
    correct << "6 7 8 " << endl;
    correct << "9 10 11 " << endl;
    correct << "12 13 14 " << endl;

    ASSERT_EQUAL(output.str(), correct.str());
    delete mat1;

    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    Matrix_init(mat2, width2, height2);

    for (int row = 0; row < height2; ++row) {
        for (int col = 0; col < width2; ++col) {
            *Matrix_at(mat2, row, col) = row * width2 + col;
        }
    }
    Matrix_print(mat2, cout);

    ostringstream output2;
    Matrix_print(mat2, cout);
    Matrix_print(mat2, output2);

    ostringstream correct2;
    correct2 << "1 1" << endl;
    correct2 << "0 " << endl;

    ASSERT_EQUAL(output2.str(), correct2.str());
    delete mat2;

    Matrix* mat3 = new Matrix;
    const int width3 = 3;
    const int height3 = 5;
    Matrix_init(mat3, width3, height3);
    Matrix_print(mat3, cout);  //What if I print a Matrix that has not been filled??

    delete mat3;
}


TEST(test_Matrix_at) {
    Matrix* mat1 = new Matrix;
    const int width = 3;
    const int height = 5;
    Matrix_init(mat1, width, height);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            *Matrix_at(mat1, row, col) = row * width + col;
        }
    }

    int* ptr1 = Matrix_at(mat1, 0, 0);
    int* ptr2 = Matrix_at(mat1, 0, 2);
    int* ptr3 = Matrix_at(mat1, 1, 0);
    int* ptr4 = Matrix_at(mat1, 1, 2);
    int* ptr5 = Matrix_at(mat1, 4, 0);
    int* ptr6 = Matrix_at(mat1, 4, 2);

    ASSERT_EQUAL(*ptr1, 0);
    ASSERT_EQUAL(*ptr2, 2);
    ASSERT_EQUAL(*ptr3, 3);
    ASSERT_EQUAL(*ptr4, 5);
    ASSERT_EQUAL(*ptr5, 12);
    ASSERT_EQUAL(*ptr6, 14);

    delete mat1;

    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    Matrix_init(mat2, width2, height2);

    for (int row = 0; row < height2; ++row) {
        for (int col = 0; col < width2; ++col) {
            *Matrix_at(mat2, row, col) = row * width2 + col;
        }
    }

    int* ptr7 = Matrix_at(mat2, 0, 0);
    ASSERT_EQUAL(*ptr7, 0);
    *ptr7 = 80;
    ASSERT_EQUAL(*ptr7, 80);
    *Matrix_at(mat2, 0, 0) = 95;
    ASSERT_EQUAL(*ptr7, 95);

    delete mat2;

}


TEST(test_const_Matrix_at) {
    Matrix* mat = new Matrix;
    const int width = 3;
    const int height = 5;
    Matrix_init(mat, width, height);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            *Matrix_at(mat, row, col) = row * width + col;
        }
    }
    const Matrix* mat1 = mat;

  
 
    const int* ptr1 = Matrix_at(mat1, 0, 0);
    const int* ptr2 = Matrix_at(mat1, 0, 2);
    const int* ptr3 = Matrix_at(mat1, 1, 0);
    const int* ptr4 = Matrix_at(mat1, 1, 2);
    const int* ptr5 = Matrix_at(mat1, 4, 0);
    const int* ptr6 = Matrix_at(mat1, 4, 2);

    ASSERT_EQUAL(*ptr1, 0);
    ASSERT_EQUAL(*ptr2, 2);

    ASSERT_EQUAL(*ptr3, 3);
    ASSERT_EQUAL(*ptr4, 5);
 
    ASSERT_EQUAL(*ptr5, 12);
    ASSERT_EQUAL(*ptr6, 14);
    //What's the difference between checking matrix_at and const matrix_at?
    delete mat;

    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    Matrix_init(mat2, width2, height2);


    for (int row = 0; row < height2; ++row) {
        for (int col = 0; col < width2; ++col) {
            cout << row << " " << col << endl;
            *Matrix_at(mat2, row, col) = row * width2 + col;
        }
    }


    const Matrix* mat3 = mat2;

    const int* ptr7 = Matrix_at(mat3, 0, 0);
    ASSERT_EQUAL(*ptr7, 0);

    delete mat2;
    
}


TEST(test_Matrix_row) {
    Matrix* mat1 = new Matrix;
    const int width = 3;
    const int height = 5;
    Matrix_init(mat1, width, height);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            *Matrix_at(mat1, row, col) = row * width + col;
        }
    }

    int* ptr1 = Matrix_at(mat1, 0, 0);
    int* ptr2 = Matrix_at(mat1, 0, 2);
    int* ptr3 = Matrix_at(mat1, 1, 0);
    int* ptr4 = Matrix_at(mat1, 1, 2);
    int* ptr5 = Matrix_at(mat1, 4, 0);
    int* ptr6 = Matrix_at(mat1, 4, 2);

    ASSERT_EQUAL(Matrix_row(mat1, ptr1), 0);
    ASSERT_EQUAL(Matrix_row(mat1, ptr2), 0);
    ASSERT_EQUAL(Matrix_row(mat1, ptr3), 1);
    ASSERT_EQUAL(Matrix_row(mat1, ptr4), 1);
    ASSERT_EQUAL(Matrix_row(mat1, ptr5), 4);
    ASSERT_EQUAL(Matrix_row(mat1, ptr6), 4);

    delete mat1;

    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    Matrix_init(mat2, width2, height2);

    for (int row = 0; row < height2; ++row) {
        for (int col = 0; col < width2; ++col) {
            *Matrix_at(mat2, row, col) = row * width2 + col;
        }
    }

    int* ptr7 = Matrix_at(mat2, 0, 0);
    ASSERT_EQUAL(Matrix_row(mat2, ptr7), 0);

    delete mat2;

    Matrix* mat3 = new Matrix;
    const int width3 = MAX_MATRIX_WIDTH;
    const int height3 = MAX_MATRIX_HEIGHT;
    Matrix_init(mat3, width3, height3);

    for (int row = 0; row < height3; ++row) {
        for (int col = 0; col < width3; ++col) {
            *Matrix_at(mat3, row, col) = row * width3 + col;
        }
    }

    int* ptr8 = Matrix_at(mat3, 499, 499);
    ASSERT_EQUAL(Matrix_row(mat3, ptr8), 499);

    delete mat3;

    Matrix* mat4 = new Matrix;
    const int width4 = 1;
    const int height4 = MAX_MATRIX_HEIGHT;
    Matrix_init(mat4, width4, height4);

    for (int row = 0; row < height4; ++row) {
        for (int col = 0; col < width4; ++col) {
            *Matrix_at(mat4, row, col) = row * width4 + col;
        }
    }

    int* ptr9 = Matrix_at(mat4, 499, 0);
    ASSERT_EQUAL(Matrix_row(mat4, ptr9), 499);
    int* ptr10 = Matrix_at(mat4, 0, 0);
    ASSERT_EQUAL(Matrix_row(mat4, ptr10), 0);

    delete mat4;

    Matrix* mat5 = new Matrix;
    const int width5 = MAX_MATRIX_WIDTH;
    const int height5 = 1;
    Matrix_init(mat5, width5, height5);

    for (int row = 0; row < height5; ++row) {
        for (int col = 0; col < width5; ++col) {
            *Matrix_at(mat5, row, col) = row * width5 + col;
        }
    }

    int* ptr11 = Matrix_at(mat5, 0, 499);
    ASSERT_EQUAL(Matrix_row(mat5, ptr11), 0);

    delete mat5;
}


TEST(test_matrix_column) {
    Matrix* mat1 = new Matrix;
    const int width = 3;
    const int height = 5;
    Matrix_init(mat1, width, height);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            *Matrix_at(mat1, row, col) = row * width + col;
        }
    }

    int* ptr1 = Matrix_at(mat1, 0, 0);
    int* ptr2 = Matrix_at(mat1, 0, 2);
    int* ptr3 = Matrix_at(mat1, 1, 0);
    int* ptr4 = Matrix_at(mat1, 1, 2);
    int* ptr5 = Matrix_at(mat1, 4, 0);
    int* ptr6 = Matrix_at(mat1, 4, 2);

    ASSERT_EQUAL(Matrix_column(mat1, ptr1), 0);
    ASSERT_EQUAL(Matrix_column(mat1, ptr2), 2);
    ASSERT_EQUAL(Matrix_column(mat1, ptr3), 0);
    ASSERT_EQUAL(Matrix_column(mat1, ptr4), 2);
    ASSERT_EQUAL(Matrix_column(mat1, ptr5), 0);
    ASSERT_EQUAL(Matrix_column(mat1, ptr6), 2);

    delete mat1;

    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    Matrix_init(mat2, width2, height2);

    for (int row = 0; row < height2; ++row) {
        for (int col = 0; col < width2; ++col) {
            *Matrix_at(mat2, row, col) = row * width2 + col;
        }
    }

    int* ptr7 = Matrix_at(mat2, 0, 0);
    ASSERT_EQUAL(Matrix_column(mat2, ptr7), 0);

    delete mat2;

    Matrix* mat3 = new Matrix;
    const int width3 = MAX_MATRIX_WIDTH;
    const int height3 = MAX_MATRIX_HEIGHT;
    Matrix_init(mat3, width3, height3);

    for (int row = 0; row < height3; ++row) {
        for (int col = 0; col < width3; ++col) {
            *Matrix_at(mat3, row, col) = row * width3 + col;
        }
    }

    int* ptr9 = Matrix_at(mat3, 499, 499);
    ASSERT_EQUAL(Matrix_column(mat3, ptr9), 499);

    delete mat3;

    Matrix* mat4 = new Matrix;
    const int width4 = 1;
    const int height4 = MAX_MATRIX_HEIGHT;
    Matrix_init(mat4, width4, height4);

    for (int row = 0; row < height4; ++row) {
        for (int col = 0; col < width4; ++col) {
            *Matrix_at(mat4, row, col) = row * width4 + col;
        }
    }

    int* ptr10 = Matrix_at(mat4, 499, 0);
    ASSERT_EQUAL(Matrix_column(mat4, ptr10), 0);

    delete mat4;

    Matrix* mat5 = new Matrix;
    const int width5 = MAX_MATRIX_WIDTH;
    const int height5 = 1;
    Matrix_init(mat5, width5, height5);

    for (int row = 0; row < height5; ++row) {
        for (int col = 0; col < width5; ++col) {
            *Matrix_at(mat5, row, col) = row * width5 + col;
        }
    }

    int* ptr11 = Matrix_at(mat5, 0, 499);
    ASSERT_EQUAL(Matrix_column(mat5, ptr11), 499);

    delete mat5;
}


TEST(test_Matrix_fill_border) {
    cout << "Matrix 1 fill border" << endl;
    cout << endl;
    Matrix* mat1 = new Matrix;
    const int width = 3;
    const int height = 5;
    const int value = -9;
    Matrix_init(mat1, width, height);

    Matrix_fill_border(mat1, value);
    Matrix_print(mat1, cout);
    ASSERT_EQUAL(*Matrix_at(mat1, 0, 0), value);
    ASSERT_EQUAL(*Matrix_at(mat1, 0, 2), value);
    ASSERT_EQUAL(*Matrix_at(mat1, 1, 0), value);
    ASSERT_EQUAL(*Matrix_at(mat1, 3, 2), value);
    ASSERT_EQUAL(*Matrix_at(mat1, 4, 0), value);
    ASSERT_EQUAL(*Matrix_at(mat1, 4, 2), value);

    delete mat1;

    cout << "Matrix 2 fill border" << endl;
    cout << endl;
    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    const int value2 = 5;
    Matrix_init(mat2, width2, height2);

    Matrix_fill_border(mat2, value2);
    Matrix_print(mat2, cout);
    ASSERT_EQUAL(*Matrix_at(mat2, 0, 0), value2);

    delete mat2;

    cout << "Matrix 3 fill border" << endl;
    cout << endl;
    Matrix* mat3 = new Matrix;
    const int width3 = MAX_MATRIX_WIDTH;
    const int height3 = 1;
    Matrix_init(mat3, width3, height3);

    Matrix_fill_border(mat3, 1);
    Matrix_print(mat3, cout);
    ASSERT_EQUAL(*Matrix_at(mat3, 0, 499), 1);

    delete mat3;

    cout << "Matrix 4 fill border" << endl;
    cout << endl;
    Matrix* mat4 = new Matrix;
    const int width4 = 1;
    const int height4 = MAX_MATRIX_HEIGHT;
    const int value4 = 4;
    Matrix_init(mat4, width4, height4);

    Matrix_fill_border(mat4, value4);
    Matrix_print(mat4, cout);
    ASSERT_EQUAL(*Matrix_at(mat4, 499, 0), value4);

    delete mat4;

    cout << "Matrix 5 fill border" << endl;
    cout << endl;
    Matrix* mat5 = new Matrix;
    const int width5 = MAX_MATRIX_WIDTH;
    const int height5 = MAX_MATRIX_HEIGHT;
    const int value5 = 77;
    Matrix_init(mat5, width5, height5);

    Matrix_fill_border(mat5, value5);
    Matrix_print(mat5, cout);
    ASSERT_EQUAL(*Matrix_at(mat5, 0, 0), value5);
    ASSERT_EQUAL(*Matrix_at(mat5, 0, 499), value5);
    ASSERT_EQUAL(*Matrix_at(mat5, 499, 0), value5);
    ASSERT_EQUAL(*Matrix_at(mat5, 499, 499), value5);

    delete mat5;

    cout << "Matrix 6 fill border" << endl;
    cout << endl;
    Matrix* mat6 = new Matrix;
    const int width6 = 2;
    const int height6 = 2;
    const int value6 = -77;
    Matrix_init(mat6, width6, height6);

    Matrix_fill_border(mat6, value6);
    Matrix_print(mat6, cout);
    ASSERT_EQUAL(*Matrix_at(mat6, 0, 0), value6);
    ASSERT_EQUAL(*Matrix_at(mat6, 0, 1), value6);
    ASSERT_EQUAL(*Matrix_at(mat6, 1, 0), value6);
    ASSERT_EQUAL(*Matrix_at(mat6, 1, 1), value6);

    delete mat6;
}

TEST(test_Matrix_max) {
    cout << "Matrix 1 max" << endl;
    cout << endl;
    Matrix* mat1 = new Matrix;
    const int width = 3;
    const int height = 5;
    Matrix_init(mat1, width, height);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            *Matrix_at(mat1, row, col) = row * width + col;
        }
    }
    ASSERT_EQUAL(Matrix_max(mat1), 14);

    *Matrix_at(mat1, 2, 1) = 178;
    ASSERT_EQUAL(Matrix_max(mat1), 178);

    delete mat1;

    cout << "Matrix 2 max" << endl;
    cout << endl;
    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    Matrix_init(mat2, width2, height2);

    Matrix_fill(mat2, 298);
    ASSERT_EQUAL(Matrix_max(mat2), 298);

    delete mat2;
}


TEST(test_Matrix_column_of_min_value_in_row) {
    cout << "Matrix 1 column of min value" << endl;
    cout << endl;
    Matrix* mat1 = new Matrix;
    const int width = 5;
    const int height = 5;
    Matrix_init(mat1, width, height);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            *Matrix_at(mat1, row, col) = row * width + col;
        }
    }
    Matrix_print(mat1, cout);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat1, 0, 0, 1), 0);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat1, 0, 0, 5), 0);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat1, 4, 0, 5), 0);
    *Matrix_at(mat1, 2, 2) = 0;
    Matrix_print(mat1, cout);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat1, 2, 0, 5), 2);

    delete mat1;

    cout << "Matrix 2 column of min value" << endl;
    cout << endl;
    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    Matrix_init(mat2, width2, height2);

    for (int row = 0; row < height2; ++row) {
        for (int col = 0; col < width2; ++col) {
            *Matrix_at(mat2, row, col) = row * width2 + col;
        }
    }

    Matrix_print(mat2, cout);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 0, 0, 1), 0);
    delete mat2;

    cout << "Matrix 3 column of min value" << endl;
    cout << endl;
    Matrix* mat3 = new Matrix;
    const int width3 = 1;
    const int height3 = MAX_MATRIX_HEIGHT;
    Matrix_init(mat3, width3, height3);

    for (int row = 0; row < height3; ++row) {
        for (int col = 0; col < width3; ++col) {
            *Matrix_at(mat3, row, col) = row * width3 + col;
        }
    }

    Matrix_print(mat3, cout);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat3, 0, 0, 1), 0);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat3, 5, 0, 1), 0);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat3, 82, 0, 1), 0);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat3, 250, 0, 1), 0);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat3, 499, 0, 1), 0);
    delete mat3;

    cout << "Matrix 4 column of min value" << endl;
    cout << endl;
    Matrix* mat4 = new Matrix;
    const int width4 = MAX_MATRIX_WIDTH;
    const int height4 = 1;
    Matrix_init(mat4, width4, height4);

    for (int row = 0; row < height4; ++row) {
        for (int col = 0; col < width4; ++col) {
            *Matrix_at(mat4, row, col) = row * width4 + col;
        }
    }

    Matrix_print(mat4, cout);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat4, 0, 0, 1), 0);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat4, 0, 3, 5), 3);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat4, 0, 45, 82), 45);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat4, 0, 98, 378), 98);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat4, 0, 456, 500), 456);
    delete mat4;
}

TEST(test_Matrix_min_value_in_row) {
    cout << "Matrix 1 min value" << endl;
    cout << endl;
    Matrix* mat1 = new Matrix;
    const int width = 5;
    const int height = 5;
    Matrix_init(mat1, width, height);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            *Matrix_at(mat1, row, col) = row * width + col;
        }
    }

    Matrix_print(mat1, cout);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat1, 0, 0, 1), 0);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat1, 1, 0, 1), 5);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat1, 4, 0, 5), 20);
    *Matrix_at(mat1, 2, 2) = 0;
    Matrix_print(mat1, cout);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat1, 2, 0, 5), 0);

    delete mat1;

    cout << "Matrix 2 min value" << endl;
    cout << endl;
    Matrix* mat2 = new Matrix;
    const int width2 = 1;
    const int height2 = 1;
    Matrix_init(mat2, width2, height2);

    for (int row = 0; row < height2; ++row) {
        for (int col = 0; col < width2; ++col) {
            *Matrix_at(mat2, row, col) = row * width2 + col;
        }
    }

    Matrix_print(mat2, cout);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 0, 0, 1), 0);

    delete mat2;

    cout << "Matrix 3 min value" << endl;
    cout << endl;
    Matrix* mat3 = new Matrix;
    const int width3 = 1;
    const int height3 = MAX_MATRIX_HEIGHT;
    Matrix_init(mat3, width3, height3);

    for (int row = 0; row < height3; ++row) {
        for (int col = 0; col < width3; ++col) {
            *Matrix_at(mat3, row, col) = row * width3 + col;
        }
    }

    Matrix_print(mat3, cout);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat3, 0, 0, 1), 0);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat3, 5, 0, 1), 5);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat3, 82, 0, 1), 82);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat3, 250, 0, 1), 250);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat3, 499, 0, 1), 499);
    delete mat3;

    cout << "Matrix 4 min value" << endl;
    cout << endl;
    Matrix* mat4 = new Matrix;
    const int width4 = MAX_MATRIX_WIDTH;
    const int height4 = 1;
    Matrix_init(mat4, width4, height4);

    for (int row = 0; row < height4; ++row) {
        for (int col = 0; col < width4; ++col) {
            *Matrix_at(mat4, row, col) = row * width4 + col;
        }
    }

    Matrix_print(mat4, cout);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat4, 0, 0, 1), 0);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat4, 0, 3, 5), 3);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat4, 0, 80, 82), 80);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat4, 0, 250, 378), 250);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat4, 0, 400, 500), 400);
    delete mat4;
}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here