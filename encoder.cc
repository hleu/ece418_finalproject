/*===
lab10-bitplanes.cc

Abstract: Bit plane decompostion of an image
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
	if (argc != 4) {
		cerr << "Usage: " << argv[0]
		     << " lena.png logo.png output.png" << endl;
		return 1;
	}

	// load the input image
	Image imageLena;
	imageLena.LoadPng (argv[1]);

	Image imageLogo;
	imageLogo.LoadPng (argv[2]);

	// create images for each plane
	Image imagePlane;
	imagePlane.Resize (imageLena.Width (), imageLena.Height () );

	// perform decomposition

		int bitMask = 0b11111110;

		for (int x = 0; x < imageLena.Width (); x++)
		{
			for (int y = 0; y < imageLena.Height (); y++)
			{
				imagePlane.Pixel (x, y) = ( (imageLena.Pixel (x, y) & bitMask) + (imageLogo.Pixel(x,y) >128 ? 1:0));

			}
		}

		imagePlane.SavePng (argv[3]);


	return 0;
}
