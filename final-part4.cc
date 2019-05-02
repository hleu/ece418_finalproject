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
#include <fstream>
using namespace std;

// snake raster scan function -- updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y);

int main (int argc, char* argv[])
{
	// verify arguments' correctness
	if (argc != 3)
	{
		cerr << "Useage: " << argv[0]
		     << " message.txt output_logo.png" << endl;
		return 1;
	}

  ifstream inFile;

  inFile.open(argv[1]);
  if (!inFile) {
      cout << "Unable to open file";
      exit(1); // terminate with error
  }

  // init values to read from message
  char x;
  char y;
  stringstream ss;
  int index = 0;
  string test;
  int curr;
  int w;
  int h;
  vector<int> runLength (3, 0);

  // read from message to runlength vector
  while (inFile >> x) {
    if (x != ','){
      ss << x;
      x = y;
    }
    else{
      test=ss.str();
      x = y;
      if (index == 0){
        ss>>curr;
        runLength[index] = curr;
        ss.clear();
      }
      if (index == 1){
        ss>>w;
        runLength[index] = w;
        ss.clear();
      }
      if (index == 2){
        ss>>h;
        runLength[index] = h;
        ss.clear();
        runLength.resize(w*h + 3);
      }
      else{
        ss>>runLength[index];
        ss.clear();
      }
      index++;
    }
  }
  ss>>runLength[index];
  ss.clear();

	// initialize values to recreate the original logo image
	Image image2;
	image2.Resize(runLength[1],runLength[2]);

	int curr2;
	if(runLength[0]==1){
		curr2 = 0;
	}
	else{
		curr2 = 255;
	}
	runLength[3]--;
	int index2 = 3;
	image2.Pixel(0,0) = curr2;

  // recreate the original logo image
	for (int x = 0, y = 0; SnakePixel (image2, x, y); )
	{
		if (runLength[index2] == 0) {
			if (curr2 == 0){
				curr2 = 255;
			}
			else{
				curr2 = 0;
			}
			image2.Pixel(x,y) = curr2;
			index2++;
			runLength[index2] --;
		}
		else{
			image2.Pixel(x,y) = curr2;
			runLength[index2] --;
		}
	}
  // save logo image
	image2.SavePng(argv[2]);

  // test if it is the same image
  // Image image;
  // image.LoadPng("image/re_logo.png");
  //
	// // edit image to be either 0 or 255
	// for (int i = 0; i < image.Width(); i++){
	// 	for (int j = 0; j < image.Height(); j++){
	// 		if (image.Pixel(i,j) < 128){
	// 			image.Pixel(i,j) = 0;
	// 		}
	// 		else {
	// 			image.Pixel(i,j) = 255;
	// 		}
	// 	}
	// }
  //
  // for (int i = 0; i < w; i++)
  // {
  //   for (int j = 0; j < h; j++)
  //   {
  //     if (image2.Pixel(i,j) != image.Pixel(i,j)) {
  //       cout<<i<<" "<<j<<" "<<image2.Pixel(i,j)<<" "<< image.Pixel(i,j)<<endl;
  //       break;
  //     }
  //   }
  // }
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
