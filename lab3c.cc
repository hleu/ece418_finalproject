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
		cerr << "Usage: " << argv[0] << " input.png small_output.png restored.png difference.png filter_flag decimation_factor" << endl;
		return 1;
	}

	// read the filter flag and dicimation factor
	int filter_flag = atoi(argv[5]);
	double M = atoi(argv[6]);

	// load the input image
	ComplexFFTImage inputImage;
	ComplexFFTImage inputImage2;
	inputImage.LoadPng (argv[1]);
	inputImage2.LoadPng (argv[1]);

	//initialize decimatedImage
	ComplexFFTImage decimatedImage;
	decimatedImage.Resize(inputImage.Width()/M,inputImage.Height()/M);
	//initialize bilinear restored image
	ComplexFFTImage b_restoredImage;
	b_restoredImage.Resize(inputImage.Width(),inputImage.Height());

	////////////////////Apply Low Pass Filter if Flagged////////////


	if(filter_flag == 1){
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
					decimatedImage.Pixel(i,j) = small2DFT.Pixel(i,j)/(M*M);
				}
			}
		}
	else{

	////////////////////Decimate the input image////////////////////

	//Method A: Decimation without an Anti-aliasing Filter
	for (int i = 0; i<inputImage.Height()/M; i++){
		for(int j = 0; j<inputImage.Width()/M; j++){
		decimatedImage.Pixel(i,j) = inputImage.Pixel(i*M,j*M);
		}
	}
}
//Following code applies to all methods
////////////////////Thresholding////////////////////

for(int i=0; i<decimatedImage.Height();++i){
	for(int j=0; j<decimatedImage.Width();++j){
		double pixel =decimatedImage.Pixel(i,j).real();
		if(pixel<0){
			decimatedImage.Pixel(i,j) = 0;
		}
		if(pixel>255){
			decimatedImage.Pixel(i,j) = 255;
		}
	}
}

	////////////////////Compute the Residual Error////////////////////
	//put decimatedImage pixel into corner of larger output imager
	for(int i=0; i<decimatedImage.Height(); i++){
		for(int j=0; j<decimatedImage.Width(); j++){
			b_restoredImage.Pixel(i*M,j*M) = decimatedImage.Pixel(i,j);
		}
	}

	////////////////////Bilinear Interpolation////////////////////
	//interpolate linearly each row between the copied pixels
	for (int i = 0; i<decimatedImage.Height(); i++){
		for(int j = 0; j<decimatedImage.Width()-1; j++){
			Complex A = b_restoredImage.Pixel(M*j,M*i);
			Complex B = b_restoredImage.Pixel(M*j+M,M*i);
			for(int x = 0; x<=M; x++){
				b_restoredImage.Pixel(M*j+x,M*i) = ((1-((x)/M)) * A) + (((x)/M) * B);
			}
		}
	}

	//interpolate linearly each column between pixels
	for (int j = 0; j<decimatedImage.Width()-1; j++){
		for(int i = 0; i<decimatedImage.Height()-1; i++){

			for(int x = 0; x<=M; x++){
				Complex A = b_restoredImage.Pixel(M*j+x,M*i);
				Complex B = b_restoredImage.Pixel(M*j+x,M*i+M);
				for(int y = 0; y<=M; y++){
					b_restoredImage.Pixel(M*j+x,M*i+y) = ((1-((y)/M)) * A) + (((y)/M) * B);
				}
			}
		}
	}


	//Create diffImage
	ComplexFFTImage diffImage;
	//inputImage_restoredImage
	diffImage.Resize(inputImage.Width(),inputImage.Height());
	double MSE = 0;
	for (int i = 0; i<inputImage.Height()-2*M; i++){
		for(int j = 0; j<inputImage.Width()-2*M; j++){
				diffImage.Pixel(i,j) = (inputImage2.Pixel(i,j))-(b_restoredImage.Pixel(i,j));
				MSE += diffImage.Pixel(i,j).real()*diffImage.Pixel(i,j).real();
		}
	}


	////////////////////Save the following image files:////////////////////
	//Small output image, Bilinear restored image,Difference image (input minus bilinear restored)


	double min = real(diffImage.Pixel(0,0));
		double max = real(diffImage.Pixel(0,0));

//Getting min and max values of diffImage
		for(int i=0; i<diffImage.Height();++i){
			for(int j=0; j<diffImage.Width();++j){
				if(diffImage.Pixel(i,j).real()<min){
					min = diffImage.Pixel(i,j).real();
				}

				if(diffImage.Pixel(i,j).real()>max){
					max = diffImage.Pixel(i,j).real();
				}
			}
		}
		MSE=MSE/(inputImage.Height()*inputImage.Width());
		printf("%f %f %f\n", MSE, max, min);

		//Use min and max to scale the difference to visualize it
		//min = -200;
		//max = 240;
		for(int i=0; i<diffImage.Height();++i){
			for(int j=0; j<diffImage.Width();++j){
				if( diffImage.Pixel(i,j).real()<=0){
					diffImage.Pixel(i,j) = double (128)*(diffImage.Pixel(i,j)-min)/(-min);
				}
				else diffImage.Pixel(i,j) = double (127)*diffImage.Pixel(i,j)/max + double (128);
			}
		}

	// save the image
	decimatedImage.SavePng (argv[2]);
	b_restoredImage.SavePng (argv[3]);
	diffImage.SavePng (argv[4]);

	return 0;
}
