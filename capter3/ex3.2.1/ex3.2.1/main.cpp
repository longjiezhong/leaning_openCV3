#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "【线性混合示例】"
const int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlider;			//轨迹条值
double g_dAlphaValue;
double g_dBetaValue;

Mat g_srcImg1;
Mat g_srcImg2;
Mat g_dstImg;

void on_Tracbar(int, void*)
{
	g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue;
	g_dBetaValue = (1.0 - g_dAlphaValue);
	addWeighted(g_srcImg1, g_dAlphaValue, g_srcImg2, g_dBetaValue, 0.0, g_dstImg);
	imshow(WINDOW_NAME, g_dstImg);
}

int main(int argc, char** argv)
{
	g_srcImg1 = imread("1.bmp");
	g_srcImg2 = imread("2.bmp");
	if( !g_srcImg1.data )
	{
		cout << "读取第1张图片错误" << endl;
		return -1;
	}

	if( !g_srcImg2.data )
	{
		cout << "读取第2张图片错误" << endl;
		return -1;
	}

	g_nAlphaValueSlider = 70;
	namedWindow(WINDOW_NAME,1);
	char TrackbarName[50];
	sprintf(TrackbarName, "透明值%d", g_nMaxAlphaValue);

	createTrackbar(TrackbarName,	//滑动条名
		WINDOW_NAME,				//窗口名
		&g_nAlphaValueSlider,		//滑动条变量
		g_nMaxAlphaValue,			//滑动变量最大值
		on_Tracbar);				//回调函数,每当滑动变量改变都会导致回调函数被执行
	on_Tracbar(g_nAlphaValueSlider, 0);

	waitKey(0);
	return 0;
}