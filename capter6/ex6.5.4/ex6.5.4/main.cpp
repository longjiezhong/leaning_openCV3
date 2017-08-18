#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;

int g_nFillMode = 1;
int g_nLowDifference = 20, g_nUpDifference = 20;
int g_nConnectivity = 4;
int g_bIsColor = true;
bool g_bUseMask = false;
int g_nNewMackVal = 255;

static void onMouse(int event, int x, int y, int, void*)
{
	if(event != CV_EVENT_LBUTTONDOWN)
		return;

	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;
	int flags = g_nConnectivity + (g_nNewMackVal << 8) + (g_nFillMode
		== 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;

	Scalar newVal = g_bIsColor ? Scalar(b,g,r) : Scalar(r*0.299 + g*0.587
		+b*0.114);
	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;
	int area;

	if(g_bUseMask)
	{
		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
		area = FloodFill(dst, g_maskImage, seed, newVal, &ccomp,
			Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
		imshow("mask", g_maskImage);
	}
	else
	{
		area = FloodFill(dst, seed, newVal, &ccomp, 
			Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
	}

	imshow("效果图", dst);
	cout << area << "个像素被重绘\n" << endl;
}

int main(int argc, char** argv)
{
	g_srcImage = imread("1.bmp", 1);
	if( !g_srcImage.data )
		cout << "读取图片错误！" << endl;
	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
	g_maskImage.create(g_srcImage.row+2, g_srcImage.cols+2, CV_8UC1);
	namedWindow("效果图", CV_WINDOW_AUTOSIZE);

	createTrackbar("负差最大值"， "效果图", &g_nLowDifference, 255, 0);
	createTrackbar("正差最大值"， "效果图", &g_nUpDifference, 255, 0);

	setMouseCallback("效果图", onMouse, 0);

	while(1)
	{
		imshow("效果图", g_bIsColor ? g_dstImage : g_grayImage);

		char c = waitKey(0);

		if( c == 27 )
		{
			cout << "程序退出......\n";
			break;
		}

		switch( c )
			case '1':
				if( g_bIsColor )
				{
					//cout << "键盘“1”被按下，切换彩色/灰度模式" << endl;
					cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
					g_maskImage = Scalar::all(0);
					g_bIsColor = false;
				}
				else
				{
					g_srcImage.copyTo(g_dstImage);
					g_maskImage = Scalar::all(0);
					g_bIsColor = true;
				}
				break;
	}
}