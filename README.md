# Watermark
This is the final project for our class ECE 418: Image and Video Processing at UIUC. The topic we decided to work on is watermarking: hide hard–to–destroy information (e.g., your signature or other personalized mark) in image or video file.

## Getting Started
### Prerequisites
This code is designed to be compatible with Linux machines

### Installing

Install ligpng-dev

```
apt-get install libpng-dev
```

### Pre-process input images
To remove the invalid iCCP chunk from all of the PNG files in a folder

```
mogrify *.png
```

### Compiling

Make the files

```
gmake final-part1
gmake final-part2
gmake final-part3
```
or
```
make final-part1
make final-part2
make final-part3
```

## Running the code

### Part 1
This part is the basic watermark version. Simply start with original input image then add watermark logo image that act as a mask that change the pixel according to the logo pixel that is darker than value 128 to the linear value between the logo image and the original input image based on an alpha value ranging from 0 to 100. The higher the value, the more of the original image pixel value is kept. It will output an output image.

```
./final-part1 input_image.png logo_image.png output_image.png alpha_value
```

For example,
```
./final-part1 image/lena.png image/logo.png image/lena_out.png 80
```

And we will have the output image with logo on top in image/out.png

### Part 2
This part created a hidden message using run length of the logo image (tested up to 128x128 size, not recommended much more than that). Then it hides the message into the fft of the input image. This results in an image that is almost the same as the input image. However, it actually includes the hidden message. The current code is not perfect since the image we save is in uint8 for normal grayscale image. The pixel value, therefore, is grounded. Because of that, we also need to keep track of the difference between the output image and the float value to be able to recover the hidden message. Then we can use that message to recreate the logo image.

We first need to get the hidden message to a .txt file. For example,
```
./final-part2 image/smaller_logo.png output/logo.txt
```

Then we can use the final.m file to get the output image with hidden message as well as the difference matrix. We need to change the input to the appropriate location. For example,
```
Message = fileread('output/logo.txt');
output_img_file = 'output/output.png';
org_message = 'output/msg.txt';
```

This will create the output image with hidden message at "output/output.png" and recover the hidden message to "msg.txt". Finally, we need to use this hidden message to recover the original logo input. For example,
```
./final-part3 output/msg.txt output/output_logo.png
```

This logo image is the original logo with each pixel threshold to 0 or 255 only.
 
## Expected rough timeline
* 04/15/2019: Finish figuring out how to implement basic watermark on image
* 04/22/2019: Work on more optimal watermark on image
* 04/29/2019: Work on more sophisticated watermark
* 05/06/2019: Meet with instructor for final feedback on the final project report
* 05/09/2019: Finish the final project report

## Authors

* [Dustin Mayfield-Jones](https://github.com/dmayfieldjones)
* [Anh Leu](https://github.com/hleu)

## Acknowledgments

* [ECE 418 labs](https://courses.engr.illinois.edu/ece418/sp2019/labs.html)
