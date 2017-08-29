#include <opencv2/opencv.hpp>
using namespace cv;

//����ֱ��ͼ���⻯

int main()
{
	Mat srcImage, dstImage;
	srcImage = imread("1.jpg");

	cvtColor(srcImage, srcImage, COLOR_RGB2GRAY);

	equalizeHist(srcImage, dstImage);

	imshow("src", srcImage);
	imshow("dst", dstImage);

	waitKey(0);
	return 0;
}