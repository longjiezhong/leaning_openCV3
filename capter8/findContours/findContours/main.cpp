#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat srcImage = imread("1.jpg", 0);
	imshow("src", srcImage);

	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	srcImage = srcImage > 100;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//�������ҳ���
	findContours(srcImage, contours, hierarchy, CV_RETR_CCOMP,
		CV_CHAIN_APPROX_SIMPLE);

	int index = 0;
	for(; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand()&255, rand()&255, rand()&255);

		//������������
		drawContours(dstImage, contours, index, color, CV_FILLED, 8,
			hierarchy);
	}

	imshow("����ͼ", dstImage);
	waitKey(0);
}