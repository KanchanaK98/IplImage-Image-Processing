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

	//gray image histogram
	int hist[256];
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			t1 = gr.at<uchar>(i, j);
			hist[t1] = hist[t1] + 1;
		}
	}
	int max = 0;
	for (int i = 0; i < 256; i++) {
		//cout << "Gray Level-" << i << " = " << hist[i] << endl;
		if (max < hist[i])
			max = hist[i];
	}
	Mat him(601, 520, CV_8UC1, Scalar(255));
	int his[256];
	double maxd = max;
	for (int i = 0; i <= 255; i++) {
		his[i] = cvRound(double(hist[i] / maxd) * 600);
		Point pt1 = Point(2 * i, 600 - his[i]);
		Point pt2 = Point(2 * i, 600);
		line(him, pt1, pt2, Scalar(0), 1, 8, 0);
	}

	//contrasted image histogram
	int hist2[256];
	for (int i = 0; i < 256; i++) {
		hist2[i] = 0;
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			t1 = cst.at<uchar>(i, j);
			hist2[t1] = hist2[t1] + 1;
		}
	}
	max = 0;
	for (int i = 0; i < 256; i++) {
		//cout << "Gray Level-" << i << " = " << hist[i] << endl;
		if (max < hist2[i])
			max = hist2[i];
	}
	Mat him2(601, 520, CV_8UC1, Scalar(255));
	int his2[256];
	maxd = max;
	for (int i = 0; i <= 255; i++) {
		his2[i] = cvRound(double(hist2[i] / maxd) * 600);
		Point pt1 = Point(2 * i, 600 - his2[i]);
		Point pt2 = Point(2 * i, 600);
		line(him2, pt1, pt2, Scalar(0), 1, 8, 0);
	}


	cout << "Width and Height :" << w << ", " << h << endl;
	imwrite("cst.jpg", cst);
	namedWindow("image", WINDOW_NORMAL);
	namedWindow("High_Contrast", WINDOW_AUTOSIZE);
	namedWindow("Original Histogram", WINDOW_AUTOSIZE);
	namedWindow("Contrasted Histogram", WINDOW_AUTOSIZE);
	imshow("image", gr);
	imshow("High_Contrast", cst);
	imshow("Original Histogram", him);
	imshow("Contrasted Histogram", him2);
	waitKey(0);
	img.release();
	gr.release();
	cst.release();
	him.release();
	him2.release();
	return 0;
}