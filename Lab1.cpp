#include <stdio.h>
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2) {   //to find whether we have given image name as second parameter in cmd
		cout << "Enter Project.exe ImgeFileName\n";
		return -1;
	}

	Mat img;
	img = imread(argv[1], IMREAD_UNCHANGED);  //argument 1 isgiven image name. as imread there are other functions to read image as grayscal,hsv and other formats.
	if (img.empty()) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	int w = img.cols;  // number of columns. width
	int h = img.rows;  // number of rows. height
	int t = img.channels(); // number of channels
	int s = img.step;  //widthStep
	int v = img.data[0];  //data of 0 location(1st pixel), Blue color value
	int v1 = img.data[1];  //data of 1 location(1st pixel), Green color value
	int v2 = img.at<Vec3b>(0, 0)(2); // data of 1st pixel(0,0) 3rd channel(Red)
	for (int i = 10; i < 50; i++) {  // i = row. in this 10th row to 49 row
		for (int j = 1; j < w; j++) {  // j = height, w = number of cols.... w-1 is last colm of this image. so,in here we go to the last row
			//img.data[i] = 0;
			img.at<Vec3b>(i, j)(2) = 0;  //(row,column)channel number. 2 means red channel(B,G,R => 0,1,2)
		}
	}

	cout << "Width and Height :" << w << ", " << h << endl;
	cout << "Type :" << t << endl;  // t = number of channels
	cout << v << endl;
	cout << v1 << endl;
	cout << v2 << endl;

	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);
	waitKey(0);  //to hold program(unless you press any key)
	img.release();
	return 0;
}