#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

static void on_ContrastAndBright(int, void*); //回调函数
int g_nContrastValue;
int g_nBrightValue;
Mat g_srcImage, g_dstImage;

//测试改变对比度与亮度
int main(int argc, char** argv)
{
	VideoCapture capture(0);
	capture >> g_srcImage;

	//g_srcImage = imread("1.bmp");
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	g_nContrastValue = 80;
	g_nBrightValue = 80;

	//创建窗口与滑动条
	namedWindow("【效果图】", 1);
	createTrackbar("对比度：", "【效果图】", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("亮度：", "【效果图】", &g_nBrightValue, 200, on_ContrastAndBright);

	//初始化回调函数
	on_ContrastAndBright(g_nBrightValue, 0);
	on_ContrastAndBright(g_nContrastValue, 0);

	while(char(waitKey(1)) != 'q')
	{
		capture >> g_srcImage;
		on_ContrastAndBright(g_nContrastValue, 0);
	}
	return 0;
}

//g(x) = a*f(x) + b
static void on_ContrastAndBright(int, void*)
{
	double time0 = static_cast<double>(getTickCount());

	time0 = static_cast<double>(getTickCount());
	int rowNumber = g_srcImage.rows;
	int colNumber = g_srcImage.cols*g_srcImage.channels();

	for(int i = 0;i < rowNumber;i++)  //行循环
	{  
		uchar* data = g_dstImage.ptr<uchar>(i);  //获取第i行的首地址
		uchar* dataSrc = g_srcImage.ptr<uchar>(i);  //获取第i行的首地址

		for(int j = 0;j < colNumber;j++)
		{  	
			data[j] = saturate_cast<uchar>((g_nContrastValue * 0.01)
				*(dataSrc[j]) + g_nBrightValue);
		}
	}  

	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "耗时" << time0 << endl;

	imshow("【原始图】", g_srcImage);
	imshow("【效果图】", g_dstImage);
}