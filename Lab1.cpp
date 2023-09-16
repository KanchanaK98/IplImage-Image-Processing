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

	Mat img,cs;
	img = imread(argv[1], IMREAD_UNCHANGED);
	cs = imread(argv[1], IMREAD_UNCHANGED);
	if (img.empty()) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	int w = img.cols;
	int h = img.rows;
	int t = img.channels();
	int s = img.step;
	int t1 = 0;

	
	int hist[256];
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			t1 = img.at<uchar>(i, j);
			hist[t1] = hist[t1] + 1;
		}
	}
	int max = 0;
	for (int i = 0; i < 256; i++) {
		cout << "Gray Level-" << i << " = " << hist[i] << endl;
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

	// start contrast streching
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int color = img.at<uchar>(i, j);
			if (color>=0 && color<=112) // 112 has been hard code as 'a'
			{
				cs.at<uchar>(i, j) = color * (10 / 112);  // c = 10
			}
			else if (color>112 && color<=242)  // 242 has been hard code as 'b'
			{
				cs.at<uchar>(i, j) = ((230 - 10) / (242 - 112)) * (color - 112) + 10;  // d = 230
			}
			else
			{
				cs.at<uchar>(i, j) = ((255 - 230) / (255 - 242)) * (color - 242) + 230;
			}
		}
	}

	//start contrast stretched histogram 
	int hist2[256];
	for (int i = 0; i < 256; i++) {
		hist2[i] = 0;
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			t1 = cs.at<uchar>(i, j);
			hist2[t1] = hist2[t1] + 1;
		}
	}
	int max2 = 0;
	for (int i = 0; i < 256; i++) {
		/*cout << "Gray Level-" << i << " = " << hist[i] << endl;*/
		if (max2 < hist2[i])
			max2 = hist2[i];
	}
	Mat him2(601, 520, CV_8UC1, Scalar(255));
	int his2[256];
	double maxd2 = max2;
	for (int i = 0; i <= 255; i++) {
		his2[i] = cvRound(double(hist2[i] / maxd2) * 600);
		Point pt1 = Point(2 * i, 600 - his2[i]);
		Point pt2 = Point(2 * i, 600);
		line(him2, pt1, pt2, Scalar(0), 1, 8, 0);
	}

	cout << "Width and Height :" << w << ", " << h << endl;
	cout << "Type :" << t << endl;

	namedWindow("image", WINDOW_NORMAL);
	namedWindow("Histogram", WINDOW_AUTOSIZE);
	namedWindow("ContrastStretching", WINDOW_NORMAL);
	namedWindow("Histogram2", WINDOW_AUTOSIZE);
	imshow("image", img);
	imshow("Histogram", him);
	imshow("ContrastStretching", cs);
	imshow("Histogram2", him2);
	waitKey(0);
	img.release();
	him.release();
	cs.release();
	him2.release();
	return 0;
}