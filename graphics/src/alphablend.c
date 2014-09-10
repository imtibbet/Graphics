/*
Author: Ian Tibbetts (Bruce Maxwell)
Date: 9/9/2014

Write a program that takes in two images and a mask image and merges the two images using the mask as an alpha mask. The alpha blending function is I = alpha*image1 + (1 - alpha)*image2. Note that you'll need to interpolate the 0-255 values in the mask to the range [0, 1].
*/

#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
	Pixel *image1,*image2,*imageMask;
	int rows1, cols1, colors1;
	int rows2, cols2, colors2;
	int rowsMask, colsMask, colorsMask;
	int dx, dy;
	float alphaR, alphaG, alphaB;
	//long imagesize1, imagesize2, imagesizeMask;
	long i,j,backgroundIndex,foregroundIndex;

	dx = 0;
	dy = 0;
	if(argc < 5 || argc > 7) {
		printf(	"Usage: alphablend <input file1> <input file2> <mask file>" 				"<output file1> [dx (default=0)] [dy (default=0)]\n");
		exit(-1);
	} 
	if(argc > 5) {
		dx = atoi(argv[5]);
	} 
	if (argc == 7) {
		dy = atoi(argv[6]);
	}

	/* read in the images */
	image1 = readPPM(&rows1, &cols1, &colors1, argv[1]);
	image2 = readPPM(&rows2, &cols2, &colors2, argv[2]);
	imageMask = readPPM(&rowsMask, &colsMask, &colorsMask, argv[3]);
	if(!image1) {
		fprintf(stderr, "Unable to read %s\n", argv[1]);
		exit(-1);
	} else if(!image2) {
		fprintf(stderr, "Unable to read %s\n", argv[2]);
		exit(-1);
	} else if(!imageMask) {
		fprintf(stderr, "Unable to read %s\n", argv[3]);
		exit(-1);
	}

	/* calculate the image size 
	imagesize1 = (long)rows1 * (long)cols1;
	imagesize2 = (long)rows2 * (long)cols2;
	imagesizeMask = (long)rowsMask * (long)colsMask;*/

	//TODO: this would be where the images would be resized for program

	/* loops over the entire background image
	* overwriting the background pixel values with the alpha blending
	* of the foreground image and the background using the mask */
	for(i=0;i<rows1-1;i++) {
		for(j=0;j<cols1-1;j++) {

			// test is the offset puts the index outside of the boundaries
			// of the background image, dx and dy can be negative
			if( 	(i+dy < 0 || i+dy > rows1-1) || 
				(j+dx < 0 || j+dx > cols1-1) ) {
				continue;
			}

			// assign separate index values to offset foreground and mask
			backgroundIndex = (i+dy) * cols1 + (j+dx);
			foregroundIndex = i * cols1 + j;

			// alpha blend two inputs using mask
			alphaR = (float)imageMask[foregroundIndex].r / 255.0;
			alphaG = (float)imageMask[foregroundIndex].g / 255.0;
			alphaB = (float)imageMask[foregroundIndex].b / 255.0;
			image1[backgroundIndex].r = alphaR*image1[backgroundIndex].r + 
					(1-alphaR)*image2[foregroundIndex].r;
			image1[backgroundIndex].g = alphaG*image1[backgroundIndex].g +
					(1-alphaG)*image2[foregroundIndex].g;
			image1[backgroundIndex].b = alphaB*image1[backgroundIndex].b +
					(1-alphaB)*image2[foregroundIndex].b;
		}
	}

	/* write out the resulting image */
	writePPM(image1, rows1, cols1, colors1 /* s/b 255 */, argv[4]);

	/* free the image memory */
	#if USECPP
	delete[] image1;
	delete[] image2;
	delete[] imageMask;
	#else
	free(image1);
	free(image2);
	free(imageMask);
	#endif

	return(0);
}
