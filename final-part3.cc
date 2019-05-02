/*===
lab10-part2-solution.cc

Abstract: Skeleton for part two of lab ten (run length coding)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"

#include <string>
using namespace std;

// snake raster scan function -- updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y);

string num2str (int Number);

int main (int argc, char* argv[])
{
	// verify arguments' correctness
	if (argc != 3)
	{
		cerr << "Useage: " << argv[0]
		     << " input.png message.txt" << endl;
		return 1;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);
	int totalPixels = image.Width () * image.Height ();

	// edit image to be either 0 or 255
	for (int i = 0; i < image.Width(); i++){
		for (int j = 0; j < image.Height(); j++){
			if (image.Pixel(i,j) < 128){
				image.Pixel(i,j) = 0;
			}
			else {
				image.Pixel(i,j) = 255;
			}
		}
	}

	// create the normalized (sum of elements is one) histogram for the run lengths
	vector<int> runLength (totalPixels + 3, 0);

	// initialize values
	int curr = image.Pixel(0,0);
	if (curr == 0){
		runLength[0] = 1;
	}
	else{
		runLength[0] = 2;
	}
	runLength[1] = image.Width();
	runLength[2] = image.Height();

	int val = 1;
	int index = 3;
	// traverse the image in raster-snake order to get the runLengthHistogram
	for (int x = 0, y = 0; SnakePixel (image, x, y); )
	{
		if (curr == image.Pixel(x,y))
		{
			val++;
		}
		else
		{
			runLength[index] = val;
			val = 1;
			index ++;
		}
		curr = image.Pixel(x,y);
	}

	// print the histogram the specified file (only as many entries as are nonzero)
	ofstream out (argv[2]);
	if (out.fail () )
	{
		cerr << "Failed to open file for message output" << endl;
		return 1;
	}
	int maxNonZeroIndex = 0;
	for (int i = 0; i < runLength.size (); i++)
	{
		if (runLength[i] != 0) {
			maxNonZeroIndex = i;
		}
	}

	// int test = std::atoi()
	stringstream ss;
	ss << num2str(runLength[0]);

	for (int i = 1; i <= maxNonZeroIndex; i++)
	{
		ss << ","<< num2str(runLength[i]);
	}
	string message = ss.str();

	cout<<message<<endl;
	out << message << endl;

	out.close ();

	return 0;
}

// snake raster scan function -- updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y)
{
	if (y % 2 == 0)
	{
		x++;
		if (x == image.Width () )
		{
			x--;
			y++;
		}
	}
	else
	{
		x--;
		if (x == -1)
		{
			x++;
			y++;
		}
	}
	return (y < image.Height () );
}

string num2str (int Number)
{
   ostringstream ss;
   ss << Number;
   return ss.str();
}
