/*===
lab1-skeleton.cc

Abstract: Skeleton for Lab 1
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness
	if (argc != 5)
	{
		cerr << "Usage: ./final-part1 in.png logo.png out.png alpha" << endl;
		return 1;
	}

	// load the images
	Image image;
	image.LoadPng (argv[1]);
	Image logo;
	logo.LoadPng (argv[2]);

	// get the alpha value
	int alpha = atoi(argv[4]);
	
	// loop through image to add logo to the input images
	for (int i = 0; i < image.Width(); i++){
		for (int j = 0; j < image.Height(); j++){
			if (logo.Pixel(i,j) < 128){
				image.Pixel(i,j) = 	int(image.Pixel(i,j)*(alpha/100.) + logo.Pixel(i,j)*(1-alpha/100.));
			}
		}
	}

	// save it
	image.SavePng (argv[3]);

	return 0;
}
