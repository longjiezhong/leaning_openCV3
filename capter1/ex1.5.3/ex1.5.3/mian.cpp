#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat srcImg = imread("girl.bmp");
	imshow("��ֵ�˲���ԭͼ��",srcImg);
	Mat dstImg;
	blur(srcImg,dstImg,Size(7,7));				//�ص�
	imshow("��ֵ�˲���Ч��ͼ��",dstImg);
	waitKey(0);
	return 0;
}