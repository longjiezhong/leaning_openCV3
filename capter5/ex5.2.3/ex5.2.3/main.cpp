#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//�������Ի��Ч��
int main(int argc, char** argv)
{
	//��0������һЩ�ֲ�����
	double alphaValue = 0.5; 
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	// ��1����ȡͼ�� ( ����ͼƬ��Ϊͬ�������ͺͳߴ� )
	srcImage2 = imread("mogu.jpg");
	srcImage3 = imread("rain.jpg");

	if( !srcImage2.data ) { printf("��ȡsrcImage2���� \n"); return false; }
	if( !srcImage3.data ) { printf("��ȡsrcImage3���� \n"); return false; }

	// ��2������ͼ���ϼ�Ȩ����
	betaValue = ( 1.0 - alphaValue );
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	// ��3����ʾԭͼ����
	imshow( "<2>���Ի��ʾ�����ڡ�ԭͼ��", srcImage2 );
	imshow( "<3>���Ի��ʾ�����ڡ�Ч��ͼ��", dstImage );
	waitKey(0);

	return 0;
}