/*===
encoder.cc
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[]) {
	// verify arguments' correctness
	if (argc != 5) {
		cerr << "Usage: " << argv[0]
		     << " lena.png logo.png output.png bit" << endl;
		return 1;
	}
	int bit = atoi(argv[4]);
	// load the input image
	Image imageLena;
	imageLena.LoadPng (argv[1]);

	Image imageLogo;
	imageLogo.LoadPng (argv[2]);

	// create images for each plane
	Image imagePlane;
	imagePlane.Resize (imageLena.Width (), imageLena.Height () );

	// perform decomposition
	int bitshift = 0;
	int bitMask = 0b11111111;
	switch (bit) {
		case 0: bitMask = 0b11111110;
		bitshift = 1;
			break;
		case 1: bitMask = 0b11111101;
		bitshift = 2;
			break;
		case 2: bitMask = 0b11111011;
		bitshift = 4;
			break;
	}


		for (int x = 0; x < imageLena.Width (); x++)
		{
			for (int y = 0; y < imageLena.Height (); y++)
			{
				imagePlane.Pixel (x, y) = ( (imageLena.Pixel (x, y) & bitMask) + (imageLogo.Pixel(x,y) >128 ? bitshift:0));

			}
		}

		imagePlane.SavePng (argv[3]);


	return 0;
}
