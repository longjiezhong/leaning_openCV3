#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat srcImg = imread("girl.bmp");
	imshow("均值滤波（原图）",srcImg);
	Mat dstImg;
	blur(srcImg,dstImg,Size(7,7));				//重点
	imshow("均值滤波（效果图）",dstImg);
	waitKey(0);
	return 0;
}