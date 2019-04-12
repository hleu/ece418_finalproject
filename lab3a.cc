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
	Complex zz=0;
	for(int i=topLeftRow; i<topLeftRow+128; ++i){
		for(int j=topLeftColumn; j<topLeftColumn+128; ++j){
			zz = inputImage.Pixel(i,j);
			for(int ii=(i-topLeftRow)*4; ii<(i-topLeftRow)*4+4; ++ii){
				for(int jj=(j-topLeftColumn)*4; jj<(j-topLeftColumn)*4+4; ++jj){
					outputImage.Pixel(ii,jj)= zz;
				}
			}
		}
	}	

	
	// save the image
	outputImage.SavePng (argv[2]);

	return 0;
}
