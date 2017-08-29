#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "SRC"
#define WINDOW_NAME2 "DST"

Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 100;
int g_nMaxThresh = 255;
RNG g_rng(12345);
Mat g_canny;
vector <vector<Point>> g_vContours;
vector <Vec4i>g_vHierarchy;

void on_ThreshChange(int, void*);

int main()
{
	g_srcImage = imread("1.jpg", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("��ֵ", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, 
		on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return 0;
}

void on_ThreshChange(int, void*)
{
	//����Ե
	Canny(g_grayImage, g_canny, g_nThresh, g_nThresh*2, 3);

	//�������
	findContours(g_canny, g_vContours, g_vHierarchy, 
		RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Moments> mu(g_vContours.size());
	for(unsigned int i = 0; i < g_vContours.size(); i++)
	{
		//���������ľ�
		mu[i] = moments( g_vContours[i], false);
	}

	vector<Point2f> mc( g_vContours.size() );
	for(unsigned int i = 0; i < g_vContours.size(); i++)
	{
		//�������ľ�
		mc[i] = Point2f(static_cast<float>(mu[i].m10/mu[i].m00),
			static_cast<float>(mu[i].m01/mu[i].m00));
	}

	Mat drawing = Mat::zeros(g_canny.size(), CV_8UC3);
	for(unsigned int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255),
			g_rng.uniform(0, 255), g_rng.uniform(0, 255));

		//��������
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy,
			0, Point());
		//�������ľ�
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}

	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);

	printf("\t������ݣ��������������\n");
	for(unsigned int i = 0; i < g_vContours.size(); i++)
	{
		printf(" >ͨ��m00���������[%d]�����: (M_00) = %.2f \n OpenCV��������������=%.2f , ����: %.2f \n\n", 
			i, 
			mu[i].m00,						//�����
			contourArea(g_vContours[i]),	//��������õ��������
			arcLength( g_vContours[i],		//��������
			true ) );
	}
}