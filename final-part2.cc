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
	if (argc < 6)
	{
		cerr << "Usage: " << argv[0] << " input.png output.png filter_flag decimation_flag decimation/interpolation_factor" << endl;
		return 1;
	}

	// read the filter flag and dicimation factor
	int filter_flag = atoi(argv[3]);
	double M = atoi(argv[5]);
	int decimation_flag = atoi(argv[4]);
	// load the input image
	ComplexFFTImage inputImage;
	inputImage.LoadPng (argv[1]);

	//initialize outputImage
	ComplexFFTImage outputImage;
	if (decimation_flag == 1) {
		outputImage.Resize(inputImage.Width()/M,inputImage.Height()/M);
	}
	else{
		outputImage.Resize(inputImage.Width()*M,inputImage.Height()*M);
	}
	////////////////////Apply Low Pass Filter if Flagged////////////
	if(filter_flag == 1 & decimation_flag == 1){
		//The following method combines ideal low pass filtering (to prevent aliasing)
		// and subsampling in one step in the frequency domain:
	  //Create two 256x256 arrays of double. These will contain the real and
		//imaginary parts of the small output array's 2-D Fourier transform.
		//Let small 2-D FT denote these two arrays.


	  //Take the 2-D FT of the input image and copy a 128x128 subblock from each
		//corner into the small 2-D FT.
		//Take the inverse 2-D FT of the 256x256 array and divide the resulting pixel
		//values by the decimation rate to satisfy Parseval's relation
		//(in this case divide by 4 and in part D divide by 64).
		//The resulting 256x256 image should be the decimated image.

		//1. Compute the 2D FFT of the image

			inputImage.FourierTransform ();

			//Perform the frequency domain operation(s)
			//Low pass filter
			int width = inputImage.Height();
			ComplexFFTImage small2DFT;
			small2DFT.Resize(width/M,width/M);

			//topleft window
			for(int i=0; i<(width/(2*M)); i++){
				for(int j=0; j<(width/(2*M)); j++){
					small2DFT.Pixel(i,j) = inputImage.Pixel(i,j);
				}
			}
			//topright window
			for(int i=0; i<(width/(2*M)); i++){
				for(int j=0; j<(width/(2*M)); j++){
					small2DFT.Pixel(i,j+(width/(2*M))) = inputImage.Pixel(i,width-(width/(2*M))+j);
				}
			}
			//bottomleft window
			for(int i=0; i<(width/(2*M)); i++){
				for(int j=0; j<(width/(2*M)); j++){
					small2DFT.Pixel(i+(width/(2*M)),j) = inputImage.Pixel(width-(width/(2*M))+i,j);
				}
			}
			//bottomright window
			for(int i=0; i<(width/(2*M)); i++){
				for(int j=0; j<(width/(2*M)); j++){
					small2DFT.Pixel(i+(width/(2*M)),j+(width/(2*M))) = inputImage.Pixel(i+width-(width/(2*M)),j+width-(width/(2*M)));
				}
			}
			small2DFT.InverseFourierTransform ();

			//Scaling and copying result to decimateImage
			for(int i=0; i<(width/(M)); i++){
				for(int j=0; j<(width/(M)); j++){
					outputImage.Pixel(i,j) = small2DFT.Pixel(i,j)/(M*M);
				}
			}
		}
	else if (decimation_flag == 1)
	{
	//Method A: Decimation without an Anti-aliasing Filter
	for (int i = 0; i<inputImage.Height()/M; i++){
		for(int j = 0; j<inputImage.Width()/M; j++){
			outputImage.Pixel(i,j) = inputImage.Pixel(i*M,j*M);
		}
	}
}

//Following code applies to all methods
////////////////////Thresholding////////////////////
if (decimation_flag == 1){
	for(int i=0; i < outputImage.Height();++i){
		for(int j=0; j < outputImage.Width();++j){
			double pixel = outputImage.Pixel(i,j).real();
			if(pixel<0){
				outputImage.Pixel(i,j) = 0;
			}
			if(pixel>255){
				outputImage.Pixel(i,j) = 255;
			}
		}
	}
}
else{

	////////////////////Compute the Residual Error////////////////////
	//put outputImage pixel into corner of larger output imager
	for(int i=0; i<inputImage.Height(); i++){
		for(int j=0; j<inputImage.Width(); j++){
			outputImage.Pixel(i*M,j*M) = inputImage.Pixel(i,j);
		}
	}

	////////////////////Bilinear Interpolation////////////////////
	//interpolate linearly each row between the copied pixels
	for (int i = 0; i<inputImage.Height(); i++){
		for(int j = 0; j<inputImage.Width()-1; j++){
			Complex A = outputImage.Pixel(M*j,M*i);
			Complex B = outputImage.Pixel(M*j+M,M*i);
				for(int x = 0; x<=M; x++){
					outputImage.Pixel(M*j+x,M*i) = ((1-((x)/M)) * A) + (((x)/M) * B);
				}
			}
		}

		//interpolate linearly each column between pixels
		for (int j = 0; j<inputImage.Width()-1; j++){
			for(int i = 0; i<inputImage.Height()-1; i++){

				for(int x = 0; x<=M; x++){
					Complex A = outputImage.Pixel(M*j+x,M*i);
					Complex B = outputImage.Pixel(M*j+x,M*i+M);
					for(int y = 0; y<=M; y++){
						outputImage.Pixel(M*j+x,M*i+y) = ((1-((y)/M)) * A) + (((y)/M) * B);
					}
				}
			}
		}
	}


	for (int j = 0; j<outputImage.Width(); j++){
		for(int i = 0; i<outputImage.Height(); i++){
			if(outputImage.Pixel(i, j).real() < 128){
				outputImage.Pixel(i, j) =	0;
			}
			else{
				outputImage.Pixel(i, j) =	255;
			}
		}
	}

	////////////////////Save the following image files:////////////////////
	outputImage.SavePng (argv[2]);

	return 0;
}
