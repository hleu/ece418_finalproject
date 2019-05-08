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

Make all the files
```
make all
```

Or make the files separately
```
make final-part1
make final-part2
make final-part3
make final-part4
make final-part5
make lab10-bitplanes
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
This part is very important in image processing in general and even more in our case. We need to be able to easily manipulate the images' sizes to make the task feasible for the following task. Therefore, we modified our code for one of the previous lab to perform image interpolation/decimation as needed. Additionally, it is important to have the logo images of only value 0 or 255 so we add threshold_flag to decide wether or not we need to threshold. It is not necessary to add this flag otherwise. The general instruction is
```
./final-part2 input.png output.png filter_flag decimation_flag decimation/interpolation_factor threshold_flag
```
To perform image decimation, we need to set the decimation_flag to 1, and we can choose either to apply a low pass filter to the image to get a better output image by setting the filter flag to 1 or simply apply linear decimation to the image by setting the filter flag to 0. For example, to half the size of an image with filter we can do,
```
./final-part2 image/logo.png output/smaller_logo.png 1 1 2
```
And we will have the output image as an image of half the size of the input image.

In contrast, to perform linear interpolation to an image, we only need to set the decimation flag to 0 and we do not need to care about the filter flag. For example, to double the size of an image, we can do,
```
./final-part2 image/logo.png output/bigger_logo.png 1 0 2
```
And we will have the output image as an image of double the size of the input image.

### Part 3
This part created a hidden message using run length of the logo image. We tested up to 128x128 size and we do not recommended much more than that (The logo image can be easily scale up/down as needed using Part 2 code). Then it hides the message into the fft of the input image. This results in an image that is almost the same as the input image. However, it actually includes the hidden message. The current code is not perfect since the image we save is in uint8 for normal grayscale image. The pixel value, therefore, is grounded. Because of that, we also need to keep track of the difference between the output image and the float value to be able to recover the hidden message. Then we can use that message to recreate the logo image.

We first need to get the hidden message to a .txt file.
```
./final-part3 logo.png logo_message.txt
```
For example,
```
./final-part3 image/smaller_logo.png output/logo.txt
```

Then we can use the final.m file to get the output image with hidden message as well as the difference matrix. We need to change the input to the appropriate location.
```
Message = fileread('logo_message.txt');
output_img_file = 'output.png';
org_message = 'original_message.txt';
```
For example,
```
Message = fileread('output/logo.txt');
output_img_file = 'output/';
org_message = 'output/msg.txt';
```

This will create the output image with hidden message at "output/output.png" and recover the hidden message to "msg.txt". Finally, we need to use this hidden message to recover the original logo input.
```
./final-part4 output/msg.txt output/output_logo.png
```
For example,
```
./final-part4 output/msg.txt output/output_logo.png
```

This logo image is the original logo with each pixel threshold to 0 or 255 only.

### Part 4
Since the images we work with are uint8, we can separate any of suhc images to 8 bit planes. This part encode a logo image to replace any bit plane of the original image and then decode the image to 8 bit plane image. 
```
./final-part5 input.png logo.png output.png bit 
```
For example,
```
./final-part4 image/lena.png image/logo.png output/lena_logo.png 0
```
This will replace the bit 0 plane with the logo image. We can do this several times with different bit planes to hide more logo images. For example,
```
./final-part4 image/lena.png image/logo.png output/lena_logo.png 0
./final-part4 output/lena_logo.png image/game.png output/lena_logo.png 1
./final-part4 output/lena_logo.png image/letter.png output/lena_logo.png 2
```
This will result in a new lena image with the three least significant bits replaced with 3 different logo images.

To decode this new image to 8 bit planes, we use lab 10 provided code to output 8 bit planes images. 
input.png output
```
./lab10-bitplanes input.png output_folder
```
For example,
```
./lab10-bitplanes output/lena_logo.png bitplane_out
```

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
