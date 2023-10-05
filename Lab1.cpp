#include <stdio.h>
#include <iostream>
#include<opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Enter Project.exe ImgeFileName\n";
		return -1;
	}

	Mat img, gr, cst;
	img = imread(argv[1], IMREAD_UNCHANGED);
	if (img.empty()) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	int w = img.cols;
	int h = img.rows;
	int t = img.channels();
	int s = img.step;
	int t1 = 0;

	cvtColor(img, gr, COLOR_BGR2GRAY);
	cst = gr.clone();
	int x = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			x = gr.at<uchar>(i, j);
			if (x < 105) {
				cst.at<uchar>(i, j) = (uchar)(cvRound((double)(5 / 105) * (double)(x)));
			}
			else if (x < 245) {
				cst.at<uchar>(i, j) = (uchar)(cvRound(1.75 * ((double)(x)-105)) + 5);
			}
			else {
				cst.at<uchar>(i, j) = (uchar)(cvRound(0.5 * ((double)(x)-245)) + 250);
			}
		}
	}

	cout << "Width and Height :" << w << ", " << h << endl;
	imwrite("cst.jpg", cst);
	namedWindow("image", WINDOW_NORMAL);
	namedWindow("High_Contrast", WINDOW_AUTOSIZE);
	imshow("image", gr);
	imshow("High_Contrast", cst);
	waitKey(0);
	img.release();
	gr.release();
	cst.release();
	return 0;
}