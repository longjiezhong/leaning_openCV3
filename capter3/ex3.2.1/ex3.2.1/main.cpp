#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "�����Ի��ʾ����"
const int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlider;			//�켣��ֵ
double g_dAlphaValue;
double g_dBetaValue;

Mat g_srcImg1;
Mat g_srcImg2;
Mat g_dstImg;

void on_Tracbar(int, void*)
{
	g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue;
	g_dBetaValue = (1.0 - g_dAlphaValue);
	addWeighted(g_srcImg1, g_dAlphaValue, g_srcImg2, g_dBetaValue, 0.0, g_dstImg);
	imshow(WINDOW_NAME, g_dstImg);
}

int main(int argc, char** argv)
{
	g_srcImg1 = imread("1.bmp");
	g_srcImg2 = imread("2.bmp");
	if( !g_srcImg1.data )
	{
		cout << "��ȡ��1��ͼƬ����" << endl;
		return -1;
	}

	if( !g_srcImg2.data )
	{
		cout << "��ȡ��2��ͼƬ����" << endl;
		return -1;
	}

	g_nAlphaValueSlider = 70;
	namedWindow(WINDOW_NAME,1);
	char TrackbarName[50];
	sprintf(TrackbarName, "͸��ֵ%d", g_nMaxAlphaValue);

	createTrackbar(TrackbarName,	//��������
		WINDOW_NAME,				//������
		&g_nAlphaValueSlider,		//����������
		g_nMaxAlphaValue,			//�����������ֵ
		on_Tracbar);				//�ص�����,ÿ�����������ı䶼�ᵼ�»ص�������ִ��
	on_Tracbar(g_nAlphaValueSlider, 0);

	waitKey(0);
	return 0;
}