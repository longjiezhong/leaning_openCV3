#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#define WINDOW_NAME "���򴰿�"

int g_nThresholdValue = 100;

/*
0 ��������ֵ
1 ����������ֵ
2 �ض���ֵ
3 ����ֵ��Ϊ0
4 ��ֵ��Ϊ0
*/
int g_nThresholdType = 3;

Mat g_srcImage, g_grayImage, g_dstImage;

void on_Threshold(int, void*);

int main()
{
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data)
	{
		cout << "��ȡͼƬ����" << endl;
		return false;
	}

	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("ģʽ", WINDOW_NAME, &g_nThresholdType,
		4, on_Threshold);
	createTrackbar("����ֵ", WINDOW_NAME, &g_nThresholdValue,
		255,on_Threshold);

	on_Threshold(0, 0);

	while(1)
	{
		char key;
		key = waitKey( 20 );
		if( key == 27 )
		{
			break;
		}
	}
}

void on_Threshold(int, void*)
{
	threshold(g_grayImage, g_dstImage,
		g_nThresholdValue, 
		255,
		g_nThresholdType);

	imshow(WINDOW_NAME, g_dstImage);
}