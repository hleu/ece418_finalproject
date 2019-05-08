import argparse
from matplotlib import pyplot 
parser = argparse.ArgumentParser()
parser.add_argument('input_img1', metavar='input1', type=str)
parser.add_argument('input_img2', metavar='input2', type=str)

args = parser.parse_args()
img1 = pyplot.imread(args.input_img1)
img2 = pyplot.imread(args.input_img2)
mse = 0.0
for i in range(img1.shape[0]):
	for j in range(img1.shape[1]):
		mse += (int(img1[i][j]*255) - int(img2[i][j]*255))* (int(img1[i][j]*255) - int(img2[i][j]*255))

mse /= img1.shape[0]*img1.shape[1]
print(mse)