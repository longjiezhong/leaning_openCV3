#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	//以灰度方式读入图片
	Mat stcImage = imread("1.jpg", 0);
	imshow("src", stcImage);
	
	MatND dstHist;
	int dims = 1;
	float hranges[] = {0, 255};
	const float *ranges[] = {hranges};
	int size = 256;
	int channels = 0;

	calcHist(&stcImage, 
		1,					//单张图片
		&channels,			//灰度
		Mat(),				//无掩膜
		dstHist,			//目标直方图
		dims,				//1维
		&size,
		ranges);

	int scale = 1;

	Mat dstImage(size * scale, size, CV_8U, Scalar(0));
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	int hpt = saturate_cast<int>(0.9*size);
	for(int i = 0; i < 256; i++)						//已知像素值在0-255之间
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1) * scale
			-1, size - realValue), Scalar(255));
	}

	imshow("一维直方图", dstImage);
	waitKey(0);
	return 0;
}