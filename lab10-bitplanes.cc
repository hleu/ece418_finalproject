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
	if (argc != 3) {
		cerr << "Useage: " << argv[0] 
		     << " input.png output" << endl;
		return 1;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);

	// create images for each plane
	Image imagePlane;
	imagePlane.Resize (image.Width (), image.Height () );
	
	// perform decomposition
	for (int plane = 0; plane < 8; plane++)
	{
		int bitMask = (1 << plane);
		int shift = 8 - plane;

		for (int x = 0; x < image.Width (); x++)
		{
			for (int y = 0; y < image.Height (); y++)
			{	
				imagePlane.Pixel (x, y) = ( (image.Pixel (x, y) & bitMask) >> plane) * 255;
			}
		}
		
		stringstream ss;
		ss << argv[2] << plane << ".png";
		string fileName;
		ss >> fileName;
		imagePlane.SavePng (fileName);
	}

	return 0;
}
