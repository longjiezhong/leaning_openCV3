#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;

int g_nFillMode = 1;
int g_nLowDifference = 20, g_nUpDifference = 20;
int g_nConnectivity = 4;
int g_bIsColor = true;
bool g_bUseMask = false;
int g_nNewMackVal = 255;

static void onMouse(int event, int x, int y, int, void*)
{
	if(event != CV_EVENT_LBUTTONDOWN)
		return;

	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;
	int flags = g_nConnectivity + (g_nNewMackVal << 8) + (g_nFillMode
		== 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;

	Scalar newVal = g_bIsColor ? Scalar(b,g,r) : Scalar(r*0.299 + g*0.587
		+b*0.114);
	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;
	int area;

	if( g_bUseMask )
	{
		threshold(g_maskImage, g_maskImage, 1, 128, CV_THRESH_BINARY);
		area = floodFill(dst,				//�������ͼ��
			g_maskImage,					//��Ĥ��
			seed, 
			newVal, 
			&ccomp, 
			Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), 
			flags);
		imshow( "mask", g_maskImage );
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
	}

	imshow("Ч��ͼ", dst);
	cout << area << "�����ر��ػ�\n" << endl;
}

int main(int argc, char** argv)
{
	g_srcImage = imread("1.png", 1);
	if( !g_srcImage.data )
		cout << "��ȡͼƬ����" << endl;
	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
	g_maskImage.create(g_srcImage.rows+2, g_srcImage.cols+2, CV_8UC1);
	namedWindow("Ч��ͼ", CV_WINDOW_AUTOSIZE);

	createTrackbar("�������ֵ", "Ч��ͼ", &g_nLowDifference, 255, 0);
	createTrackbar("�������ֵ", "Ч��ͼ", &g_nUpDifference, 255, 0);

	setMouseCallback("Ч��ͼ", onMouse, 0);

	while(1)
	{
		imshow("Ч��ͼ", g_bIsColor ? g_dstImage : g_grayImage);

		char c = waitKey(0);

		if( c == 27 )
		{
			cout << "�����˳�......\n";
			break;
		}

		switch( c )
		{
		case '1':
			if( g_bIsColor )
			{
				//cout << "���̡�1�������£��л���ɫ/�Ҷ�ģʽ" << endl;
				cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
				g_maskImage = Scalar::all(0);
				g_bIsColor = false;
			}
			else
			{
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;
			}
			break;

		case '2' :
			if(g_bUseMask)
			{
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}
			break;

		case '3':
			cout << "����3�����£��ָ�ԭʼͼ��" << endl;
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_RGB2GRAY);
			g_maskImage = Scalar::all(0);
			break;

		case '4':
			cout << "����4�����£�ʹ�ÿշ�Χ����ˮ���" << endl;
			g_nFillMode = 0;
			break;

		case '5':
			cout << "����5�����£�ʹ�ý��䡢�̶���Χ����ˮ���" << endl;
			g_nFillMode = 1;
			break;

		case '6':
			cout << "����6�����£�ʹ�ý��䡢������Χ����ˮ���" << endl;
			g_nFillMode = 2;
			break;

		case '7':
			cout << "����7�����£�������־λ�ĵ�8λʹ��4λ������ģʽ" << endl;
			g_nConnectivity = 4;
			break;

		case '8':
			cout << "����8�����£�������־λ�ĵ�8λʹ��8λ������ģʽ" << endl;
			g_nConnectivity  = 8;
			break;
		}
	}
	return 0;
}