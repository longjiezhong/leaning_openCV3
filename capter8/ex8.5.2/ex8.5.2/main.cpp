#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME "window1"

Mat g_maskImage, g_srcImage;
Point prevPt(-1, -1);

static void on_Mouse(int, event, int x, int y, int flags, void*);

int main()
{
	g_srcImage = imread("1.jpg", 1);
	imshow(WINDOW_NAME, g_srcImage);
	Mat srcImage, grayImage;
	g_srcImage.copyTo(srcImage);
	cvtColor(g_srcImage, g_maskImage, COLOR_RGB2GRAY);
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
	g_maskImage = Scalar::all(0);

	setMouseCallback(WINDOW_NAME, on_Mouse, 0);

	while(1)
	{
		char c = waitKey(0); 

		if(c == 27)
			break;

		if()
	}
}