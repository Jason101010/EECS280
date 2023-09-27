// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image

  Image* img1 = new Image;
  Image_init(img1, 1, 1);
  Image_set_pixel(img1, 0, 0, white);
  ostringstream s2;
  Image_print(img1, s2);
  ostringstream correct2;
  correct2 << "P3\n1 1\n255\n";
  correct2 << "255 255 255";
  ASSERT_EQUAL(s2.str(), correct2.str());

  delete img1;
}

//Initializes a 3 by 3 image using Image_init then tests to see if the initialized image has the correct parameters.
TEST(test_image_init) {
	Image* img = new Image;
	const int width = 3;
	const int height = 3;
	Image_init(img, width, height);
	ASSERT_EQUAL(Image_width(img), width)
	ASSERT_EQUAL(Image_height(img), height);
	delete img;

	Image* img2 = new Image;
	stringstream a;
	a << "P3\n5 5\n255\n";
	a << "0 0 0 0 0 0 255 255 250 0 0 0 0 0 0 \n";
	a << "255 255 250 126 66 0 126 66 0 126 66 0 255 255 250 \n";
	a << "126 66 0 0 0 0 255 219 183 0 0 0 126 66 0 \n";
	a << "255 219 183 255 219 183 0 0 0 255 219 183 255 219 183 \n";
	a << "255 219 183 0 0 0 134 0 0 0 0 0 255 219 183 \n";
	Image_init(img2, a);
	ostringstream s;
	Image_print(img2, s);
	ASSERT_EQUAL(s.str(), a.str());
	delete img2;
	
	//new
	Image* img3 = new Image;
	const int width3 = MAX_MATRIX_WIDTH;
	const int height3 = MAX_MATRIX_HEIGHT;
	Image_init(img3, width3, height3);
	ASSERT_EQUAL(Image_width(img3), width3)
	ASSERT_EQUAL(Image_height(img3), height3);
	delete img3;

	Image* img4 = new Image;
	const int width4 = MAX_MATRIX_WIDTH;
	const int height4 = 1;
	Image_init(img4, width4, height4);
	ASSERT_EQUAL(Image_width(img4), width4)
	ASSERT_EQUAL(Image_height(img4), height4);
	delete img4;

	Image* img5 = new Image;
	const int width5 = 1;
	const int height5 = MAX_MATRIX_HEIGHT;
	Image_init(img5, width5, height5);
	ASSERT_EQUAL(Image_width(img5), width5)
	ASSERT_EQUAL(Image_height(img5), height5);
	delete img5;

	Image* img6= new Image;
	const int width6= 1;
	const int height6 = 1;
	Image_init(img6, width6, height6);
	ASSERT_EQUAL(Image_width(img6), width6)
	ASSERT_EQUAL(Image_height(img6), height6);
	delete img6;
}
//Createas an image with a width of 1 and a height of 500, then tests to see if Image_width and Image_height
//returns the expected values
TEST(test_image_width_and_height) {
	Image* img = new Image;
	const int width = 1;
	const int height = MAX_MATRIX_WIDTH;
	Image_init(img, width, height);
	ASSERT_EQUAL(Image_width(img), width)
	ASSERT_EQUAL(Image_height(img), height);
	delete img;

	//new
	Image* img2 = new Image;
	const int width2 = MAX_MATRIX_HEIGHT;
	const int height2 = MAX_MATRIX_WIDTH;
	Image_init(img2, width2, height2);
	ASSERT_EQUAL(Image_width(img2), width2)
	ASSERT_EQUAL(Image_height(img2), height2);
	delete img2;

	Image* img3 = new Image;
	const int width3 = MAX_MATRIX_HEIGHT;
	const int height3 =	1;
	Image_init(img3, width3, height3);
	ASSERT_EQUAL(Image_width(img3), width3)
	ASSERT_EQUAL(Image_height(img3), height3);
	delete img3;

	Image* img4 = new Image;
	const int width4 = 1;
	const int height4 = 1;
	Image_init(img4, width4, height4);
	ASSERT_EQUAL(Image_width(img4), width4)
	ASSERT_EQUAL(Image_height(img4), height4);
	delete img4;
}

//Creates an 10 by 10 image, then sets one of the pixels in the image to color using Image_set_pixel
//Next, uses Image_get_pixel to get the pixel that was changed and sees if it returns the correct value.
TEST(test_image_setpixel_and_get_pixel) {
	Image* img = new Image;
	const Pixel color = { 2, 3, 4 };
	const Pixel color2 = { 7, 90, 99 };
	const int row = 2;
	const int col = 6;
	Image_init(img, 10, 10);
	Image_fill(img, color2);
	Image_set_pixel(img, row, col, color);
	const Pixel temp = Image_get_pixel(img, row, col);
	ASSERT_TRUE(Pixel_equal(temp, color))
	delete img;

	//new
	Image* img2 = new Image;
	const Pixel color3 = { 0, 0, 0 };
	const Pixel color4 = { 255, 255, 255 };
	const int row2 = 0;
	const int col2 = 0;
	Image_init(img2, 1, 1);
	Image_fill(img2, color3);
	Image_set_pixel(img2, row2, col2, color4);
	const Pixel temp2 = Image_get_pixel(img2, row2, col2);
	ASSERT_TRUE(Pixel_equal(temp2, color4))
	delete img2;

	//new
	Image* img3 = new Image;
	const Pixel color5 = { 254, 255, 255 };
	const Pixel color6 = { 1, 0, 1 };
	const int row3 = 499;
	const int col3 = 499;
	Image_init(img3, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
	Image_fill(img3, color5);
	Image_set_pixel(img3, row3, col3, color6);
	const Pixel temp3 = Image_get_pixel(img3, row3, col3);
	ASSERT_TRUE(Pixel_equal(temp3, color6))
	delete img3;

	Image* img4 = new Image;
	const int row4 = 499;
	const int col4 = 0;
	Image_init(img4, 1, MAX_MATRIX_HEIGHT);
	Image_fill(img4, color5);
	Image_set_pixel(img4, row4, col4, color6);
	const Pixel temp4 = Image_get_pixel(img4, row4, col4);
	ASSERT_TRUE(Pixel_equal(temp4, color6))
	delete img4;

	Image* img5 = new Image;
	const int row5 = 0;
	const int col5 = 499;
	Image_init(img5, MAX_MATRIX_WIDTH, 1);
	Image_fill(img5, color5);
	Image_set_pixel(img5, row5, col5, color6);
	const Pixel temp5 = Image_get_pixel(img5, row5, col5);
	ASSERT_TRUE(Pixel_equal(temp5, color6))
	delete img5;
}

TEST(test_image_fill) {
	Image* img = new Image;
	Pixel color = { 50, 70, 90 };
	Image_init(img, 200, 200);
	Image_fill(img, color);
	for (int r = 0; r < Image_height(img); ++r) {
		for (int c = 0; c < Image_width(img); ++c) {
			ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, r, c), color));
		}
	}
	delete img;

	//new
	Image* img2 = new Image;
	Pixel color2 = { 0, 0, 0 };
	Image_init(img2, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
	Image_fill(img2, color2);
	for (int r = 0; r < Image_height(img2); ++r) {
		for (int c = 0; c < Image_width(img2); ++c) {
			ASSERT_TRUE(Pixel_equal(Image_get_pixel(img2, r, c), color2));
		}
	}
	delete img2;

	//new
	Image* img3 = new Image;
	Pixel color3 = { 255, 255, 255 };
	Image_init(img3, 1, 1);
	Image_fill(img3, color3);
	for (int r = 0; r < Image_height(img3); ++r) {
		for (int c = 0; c < Image_width(img3); ++c) {
			ASSERT_TRUE(Pixel_equal(Image_get_pixel(img3, r, c), color3));
		}
	}
	delete img3;

	Image* img4 = new Image;
	Pixel color4 = { 255, 182, 255 };
	Image_init(img4, 1, MAX_MATRIX_HEIGHT);
	Image_fill(img4, color4);
	for (int r = 0; r < Image_height(img4); ++r) {
		for (int c = 0; c < Image_width(img4); ++c) {
			ASSERT_TRUE(Pixel_equal(Image_get_pixel(img4, r, c), color4));
		}
	}
	delete img4;

	Image* img5 = new Image;
	Pixel color5 = { 74, 182, 255 };
	Image_init(img5, MAX_MATRIX_WIDTH, 1);
	Image_fill(img5, color5);
	for (int r = 0; r < Image_height(img5); ++r) {
		for (int c = 0; c < Image_width(img5); ++c) {
			ASSERT_TRUE(Pixel_equal(Image_get_pixel(img5, r, c), color5));
		}
	}
	delete img5;


}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
