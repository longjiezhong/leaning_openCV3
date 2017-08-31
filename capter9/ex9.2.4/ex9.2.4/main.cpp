#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	//�ԻҶȷ�ʽ����ͼƬ
	Mat stcImage = imread("1.jpg", 0);
	imshow("src", stcImage);
	
	MatND dstHist;
	int dims = 1;
	float hranges[] = {0, 255};
	const float *ranges[] = {hranges};
	int size = 256;
	int channels = 0;

	calcHist(&stcImage, 
		1,					//����ͼƬ
		&channels,			//�Ҷ�
		Mat(),				//����Ĥ
		dstHist,			//Ŀ��ֱ��ͼ
		dims,				//1ά
		&size,
		ranges);

	int scale = 1;

	Mat dstImage(size * scale, size, CV_8U, Scalar(0));
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	int hpt = saturate_cast<int>(0.9*size);
	for(int i = 0; i < 256; i++)						//��֪����ֵ��0-255֮��
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1) * scale
			-1, size - realValue), Scalar(255));
	}

	imshow("һάֱ��ͼ", dstImage);
	waitKey(0);
	return 0;
}