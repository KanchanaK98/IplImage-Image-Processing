#include "cv.h" //main opencv header
#include "highgui.h" //GUI header
int main(int argc, char* argv[])
{
	IplImage* img;
	IplImage* img2;
	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);  // if we set 0 to CV_LOAD_IMAGE_COLOR, then image show as grayscale image

	img2 = cvLoadImage(argv[2], CV_LOAD_IMAGE_COLOR); //to open second image


	if (!img)
		printf("Could not load image file: %s\n", argv[1]);

	if (!img2)
		printf("Could not load image file: %s\n", argv[2]);

		/*cvNamedWindow("Image");
		cvShowImage("Image", img);*/
		//cvWaitKey(0);


		//question 2
	printf("Height : %d\n", img->height);
	printf("Width : %d\n", img->width);
	printf("Width Step : %d\n", img->widthStep);
	printf("Number of Channels : %d\n", img->nChannels);  //number of channel means the B, G, R. So, 3 channels


	//print data values of each pixel
	uchar* data = (uchar*)img->imageData;
	printf("1st pixel(0,0) Blue color level : %d\n", data[0]);
	printf("1st pixel(0,0) Green color level : %d\n", data[1]);
	printf("1st pixel(0,0) Red color level : %d\n", data[2]);

	//print 100,100 pixel color levels of each channel
	printf("100,100 pixel Blue color level : %d\n", data[100 * img->widthStep + 100 * img->nChannels]);
	printf("100,100 pixel Green color level : %d\n", data[100 * img->widthStep + 100 * img->nChannels + 1]);
	printf("100,100 pixel Red color level : %d\n", data[100 * img->widthStep + 100 * img->nChannels + 2]);

	//to convert each channel of each pixel to black color
	/*data[100 * img->widthStep + 100 * img->nChannels] = 0;
	data[100 * img->widthStep + 100 * img->nChannels  +  1] = 0;
	data[100 * img->widthStep + 100 * img->nChannels + 2] = 0;*/

	////to convert each channel of each pixel to white color
	//data[100 * img->widthStep + 100 * img->nChannels] = 255;
	//data[100 * img->widthStep + 100 * img->nChannels + 1] = 255;
	//data[100 * img->widthStep + 100 * img->nChannels + 2] = 255;

	//question 3
	//for (int i = 0; i < 100; i++) //to access rows(height)
	//{
	//	for (int j = 0; j < 100; j++) //to access columns(width)
	//	{
	//		data[i * img->widthStep + j * img->nChannels] = 255;
	//		data[i * img->widthStep + j * img->nChannels + 1] = 255;
	//		data[i * img->widthStep + j * img->nChannels + 2] = 255;
	//	}
	//	
	//}

	//question 4
	/*uchar* data2 = (uchar*)img2->imageData;
	for (int i = 100; i < 200; i++)
	{
		for (int j = 100; j < 200; j++)
		{
			data2[i * img2->widthStep + j * img2->nChannels] = data[i * img->widthStep + j * img->nChannels];
			data2[i * img2->widthStep + j * img2->nChannels + 1] = data[i * img->widthStep + j * img->nChannels];
			data2[i * img2->widthStep + j * img2->nChannels + 2] = data[i * img->widthStep + j * img->nChannels];
		}

	}*/
	//question 5
	//to get whole width and whole height, we can use
		/*for (int i = 0; i < img->height; i++)
		{
			for (int j = 0; j < img->width; j++) {
				data[i * img->widthStep + j * img->nChannels] = 0;
				data[i * img->widthStep + j * img->nChannels + 1] = 0;
				data[i * img->widthStep + j * img->nChannels + 2] = 0;
			}
		}*/


		//question 6
	IplImage* gray = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	uchar* dataGray = (uchar*)gray->imageData;
	int widthGray = gray->widthStep;
	for (int i = 0; i < (img->height); i++) //to access rows(height)
	{
		for (int j = 0; j < (img->width); j++) //to access columns(width)
		{
			dataGray[i * widthGray + j * 1] = 0.1140 * data[i * img->widthStep + j * img->nChannels] + 0.5870 * data[i * img->widthStep + j * img->nChannels + 1] + 0.2989 * data[i * img->widthStep + j * img->nChannels + 2];
		}

	}

	////question 7
	IplImage* binary = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	uchar* dataBinary = (uchar*)binary->imageData;
	int widthStepsBinary = binary->widthStep;
	for (int i = 0; i < (img->height); i++) //to access rows(height)
	{
		for (int j = 0; j < (img->width); j++) //to access columns(width)
		{
			if (dataGray[i * widthGray + j * 1] > 150)
			{
				dataBinary[i * widthStepsBinary + j * 1] = 255;
			}
			else {
				dataBinary[i * widthStepsBinary + j * 1] = 0;
			}
		}

	}


	//question 8   Negative image  
	/*IplImage* negative = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	uchar* negativeData = (uchar*)negative->imageData;*/
	for (int i = 0; i < img->height; i++) { //to access rows
		for (int j = 0; j < img->width; j++) { //to access columns
			data[i * img->widthStep + j * img->nChannels] = 255 - data[i * img->widthStep + j * img->nChannels];
			data[i * img->widthStep + j * img->nChannels + 1] = 255 - data[i * img->widthStep + j * img->nChannels + 1];
			data[i * img->widthStep + j * img->nChannels + 2] = 255 - data[i * img->widthStep + j * img->nChannels + 2];
		}
	}


	//question 9  for Blue 
	IplImage* blue = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	uchar* dataBlue = (uchar*)blue->imageData;
	for (int i = 0; i < img->height; i++) { //to access rows
		for (int j = 0; j < img->width; j++) { //to access columns
			dataBlue[i * blue->widthStep + j * blue->nChannels] = data[i * img->widthStep + j * 3];
			dataBlue[i * blue->widthStep + j * blue->nChannels + 1] = 0;
			dataBlue[i * blue->widthStep + j * blue->nChannels + 2] = 0;
		}
	}
	//question 9  for Green 
	IplImage* green = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	uchar* dataGreen = (uchar*)green->imageData;
	for (int i = 0; i < img->height; i++) { //to access rows
		for (int j = 0; j < img->width; j++) { //to access columns
			dataGreen[i * green->widthStep + j * green->nChannels] = 0;
			dataGreen[i * green->widthStep + j * green->nChannels + 1] = data[i * img->widthStep + j * 3 +  1];
			dataGreen[i * green->widthStep + j * green->nChannels + 2] = 0;
		}
	}
	//question 9  for Red 
	IplImage* red = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	uchar* dataRed = (uchar*)red->imageData;
	for (int i = 0; i < img->height; i++) { //to access rows
		for (int j = 0; j < img->width; j++) { //to access columns
			dataRed[i * red->widthStep + j * red->nChannels] = 0;
			dataRed[i * red->widthStep + j * red->nChannels + 1] = 0;
			dataRed[i * red->widthStep + j * red->nChannels + 2] = data[i * img->widthStep + j * 3  +  2];
		}
	}


	cvNamedWindow("Image");
	cvShowImage("Image", img);  //to do question 4, this should be img2

	cvNamedWindow("Image 2 ");
	cvShowImage("Image 2 ", gray);  //to do question 6, to open image as new window

	cvNamedWindow("Image 3 ");
	cvShowImage("Image 3 ", binary);  //to do question 7, to open image as new window

	cvNamedWindow("Image 4 ");
	cvShowImage("Image 4 ", img2);  //to do question 8, to open image as new window

	cvNamedWindow("Image 5 ");
	cvShowImage("Image 5 ", blue);

	cvNamedWindow("Image 6 ");
	cvShowImage("Image 6 ", green);

	cvNamedWindow("Image 7 ");
	cvShowImage("Image 7 ", red);


	cvWaitKey(0);
	cvDestroyWindow("Image");
	cvReleaseImage(&img);  //to do question 4, this should be &img2

	cvDestroyWindow("Image 2");
	cvReleaseImage(&gray);

	cvDestroyWindow("Image 3");
	cvReleaseImage(&binary);

	cvDestroyWindow("Image 4");
	cvReleaseImage(&img2);

	cvDestroyWindow("Image 5");
	cvReleaseImage(&blue);

	cvDestroyWindow("Image 6");
	cvReleaseImage(&green);

	cvDestroyWindow("Image 7");
	cvReleaseImage(&red);

	return 0;
}