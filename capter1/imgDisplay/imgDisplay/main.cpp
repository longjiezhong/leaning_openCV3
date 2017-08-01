#include<opencv2\opencv.hpp>
using namespace cv;

void main()
{
	Mat srcImg = imread("girl.bmp");
	imshow("src",srcImg);
	waitKey(0);
}