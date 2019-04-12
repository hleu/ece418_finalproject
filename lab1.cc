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
	if (argc != 3)
	{
		cerr << "Usage: lab1 in.png out.png" << endl;
		return 1;
	}

	// load the imagez
	Image image;
	image.LoadPng (argv[1]);

	double sum;
	double avg;
	for (int i = 0; i < image.Width(); i+=4){
		for (int j = 0; j < image.Height(); j+=4){
			sum = 0;
			for (int x = 0; x < 4 ; x++){
				for (int y = 0; y < 4; y++){
					sum += image.Pixel(i+x, j+y);
				}
			}
			avg = sum/16;
			for (int x = 0; x < 4 ; x++){
				for (int y = 0; y < 4; y++){
					image.Pixel(i+x, j+y) = avg;
				}
			}
		}
	}

	// save it
	image.SavePng (argv[2]);

	return 0;
}
