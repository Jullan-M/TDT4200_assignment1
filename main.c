#include <stdlib.h>
#include <stdio.h>
#include "bitmap.h"

#define XSIZE 2560 // Size of before image
#define YSIZE 2048

void invert_colors(uchar* image) {
    for (int y = 0; y < YSIZE; y++) {
        for (int x = 0; x < XSIZE; x++) {
            for (int c = 0; c < 3; c++) {
                image[3 * XSIZE * y + x * 3 + c] = 255 - image[3 * XSIZE * y + x * 3 + c];
            }
        }
    }
}

void flip_image(uchar* image) {
    //      First we make a copy of the image
    uchar *temp = calloc(XSIZE * YSIZE * 3, 1);
    for (int y = 0; y < YSIZE; y++) {
        for (int x = 0; x < XSIZE; x++) {
            for (int c = 0; c < 3; c++) {
                temp[3 * XSIZE * y + x * 3 + c] = image[3 * XSIZE * y + x * 3 + c];
            }
        }
    }

    //      Now the flipping begins
    for (int y = 0; y < YSIZE; y++) {
        for (int x = 0; x < XSIZE; x++) {
            for (int c = 0; c < 3; c++) {
                image[3 * XSIZE * y + (XSIZE - x - 1) * 3 + c] = temp[3 * XSIZE * y + x * 3 + c];
            }
        }
    }
}

void all_blacks_are_now_blue(uchar* image) {
    for (int y = 0; y < YSIZE; y++) {
        for (int x = 0; x < XSIZE; x++) {
            uchar *r = & image[3 * XSIZE * y + x * 3 + 0];
            uchar *g = & image[3 * XSIZE * y + x * 3 + 1];
            uchar *b = & image[3 * XSIZE * y + x * 3 + 2];

            if (*r == 0 && *g == 0 && *b == 0) {
                *r = 255; // Okay, this was supposed to be *b, so I may have misunderstood the indexing here.
            }
        }
    }
}

void double_image_size(uchar* image) {
    //      First we make a copy of the image
    uchar *temp = calloc(XSIZE * YSIZE * 3, 1);
    for (int y = 0; y < YSIZE; y++) {
        for (int x = 0; x < XSIZE; x++) {
            for (int c = 0; c < 3; c++) {
                temp[3 * XSIZE * y + x * 3 + c] = image[3 * XSIZE * y + x * 3 + c];
            }
        }
    }

    // Reallocate the image area in memory.
    /*
    temp = realloc(image, 4 * XSIZE  * YSIZE * 3);

    // Duplicate each pixel in original image to 2x2 areas in new image.
    for (int y = 0; y < YSIZE; y++) {
        for (int x = 0; x < XSIZE; x++) {
            for (int c = 0; c < 3; c++) {
                image[3 * 2 * XSIZE * (2*y) + (2*x) * 3 + c] = temp[3 * XSIZE * y + x * 3 + c];
                image[3 * 2 * XSIZE * (2*y) + (2*x + 1) * 3 + c] = temp[3 * XSIZE * y + x * 3 + c];
                image[3 * 2 * XSIZE * (2*y + 1) + (2*x) * 3 + c] = temp[3 * XSIZE * y + x * 3 + c];
                image[3 * 2 * XSIZE * (2*y + 1) + (2*x + 1) * 3 + c] = temp[3 * XSIZE * y + x * 3 + c];
            }
        }
    }
     */
}

int main() {
	uchar *image = calloc(XSIZE * YSIZE * 3, 1); // Three uchars per pixel (RGB)
	readbmp("before.bmp", image);

	// Alter the image here

	// Inverting the colors
	invert_colors(image);

	// Flipping the image horizontally
	flip_image(image);

	// Change some colours
	all_blacks_are_now_blue(image);

	// Resize image
	double_image_size(image);


	savebmp("after.bmp", image, XSIZE, YSIZE);
	free(image);
	return 0;
}
