/*===
lab3-skeleton.cc

Abstract: Skeleton for Lab 3 parts (a), (b), and (c)
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "imagefft.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness [for parts (a) and (b) -- this needs to be changed for (c)]
	if (argc < 3)
	{
		cerr << "Usage: " << argv[0] << " in.png out.png [top] [left]" << endl;
		return 1;
	}

	// read the top row and left column that will be used [remove this for part (c)]
	int topLeftRow = atoi(argv[3]);
	int topLeftColumn = atoi(argv[4]);

	// load the input image
	ComplexFFTImage inputImage;
	inputImage.LoadPng (argv[1]);

	// initialize the output interpolated image
	ComplexFFTImage outputImage;
	outputImage.Resize (512, 512);

	//Lab 3 Code
	//Note that in this lab if you want to take the FFT of a ComplexFFTImage called image,
	//you only have to call image.FourierTransform () or image.InverseFourierTransform ()

	//  To magnify a 128x128 block into a 512x512 output image, simply replicate each pixel
	//  value in the subblock to fill its corresponding 4x4 subblock in the output image.
	//make sublock
	//initialize a user defined sample of the input image as a 128x128 sublock image
	ComplexFFTImage sublockImage;
	sublockImage.Resize (128, 128);
	Complex zz=0;
	for(int i=topLeftRow; i<(topLeftRow+128); ++i){
		for(int j=topLeftColumn; j<(topLeftColumn+128); ++j){
			zz = inputImage.Pixel(i,j);
			sublockImage.Pixel(i-topLeftRow ,j-topLeftColumn) = zz;
		}
	}

	//put sublock pixel into corner of larger output imager
	for(int i=0; i<128; i++){
		for(int j=0; j<128; j++){
			outputImage.Pixel(i*4,j*4) = sublockImage.Pixel(i,j);
		}
	}

	//interpolate linearly each row between the copied pixels
	double distance = 4;
	for (int i = 0; i<127; i++){
		for(int j = 0; j<128; j++){
			  Complex A = outputImage.Pixel(4*i,4*j);
			  Complex B = outputImage.Pixel(4*i+4,4*j);
			  outputImage.Pixel(4*i+1,4*j) = ((1-((1)/distance)) * A) + (((1)/distance) * B);
			  outputImage.Pixel(4*i+2,4*j) = ((1-((2)/distance)) * A) + (((2)/distance) * B);
			  outputImage.Pixel(4*i+3,4*j) = ((1-((3)/distance)) * A) + (((3)/distance) * B);
		}
	}
	//interpolate linearly each column between pixels
	for (int j = 0; j<127; j++){
		for(int i = 0; i<128; i++){
			for (int ii=0; ii<4; ii++){


			Complex A = outputImage.Pixel(4*i+ii,4*j);
			Complex B = outputImage.Pixel(4*i+ii,4*j+4);
		  outputImage.Pixel(4*i+ii,4*j) = A;
			outputImage.Pixel(4*i+ii,4*j+1) = ((1-((1)/distance)) * A) + (((1)/distance) * B);
			outputImage.Pixel(4*i+ii,4*j+2) = ((1-((2)/distance)) * A) + (((2)/distance) * B);
			outputImage.Pixel(4*i+ii,4*j+3) = ((1-((3)/distance)) * A) + (((3)/distance) * B);
		  outputImage.Pixel(4*i+ii,4*j+4) = B;

			}
		}

	}

	// save the image
	outputImage.SavePng (argv[2]);

	return 0;
}
