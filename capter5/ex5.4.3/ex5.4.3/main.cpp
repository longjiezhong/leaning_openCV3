#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

static void on_ContrastAndBright(int, void*); //�ص�����
int g_nContrastValue;
int g_nBrightValue;
Mat g_srcImage, g_dstImage;

//���Ըı�Աȶ�������
int main(int argc, char** argv)
{
	VideoCapture capture(0);
	capture >> g_srcImage;

	//g_srcImage = imread("1.bmp");
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	g_nContrastValue = 80;
	g_nBrightValue = 80;

	//���������뻬����
	namedWindow("��Ч��ͼ��", 1);
	createTrackbar("�Աȶȣ�", "��Ч��ͼ��", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("���ȣ�", "��Ч��ͼ��", &g_nBrightValue, 200, on_ContrastAndBright);

	//��ʼ���ص�����
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

	for(int i = 0;i < rowNumber;i++)  //��ѭ��
	{  
		uchar* data = g_dstImage.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
		uchar* dataSrc = g_srcImage.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ

		for(int j = 0;j < colNumber;j++)
		{  	
			data[j] = saturate_cast<uchar>((g_nContrastValue * 0.01)
				*(dataSrc[j]) + g_nBrightValue);
		}
	}  

	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "��ʱ" << time0 << endl;

	imshow("��ԭʼͼ��", g_srcImage);
	imshow("��Ч��ͼ��", g_dstImage);
}