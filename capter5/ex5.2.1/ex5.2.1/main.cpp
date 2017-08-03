#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

	// ��1������ͼ��
	Mat srcImage1= imread("dota_pa.jpg");
	Mat logoImage= imread("dota_logo.jpg");
	if( !srcImage1.data ) { printf("��ȡsrcImage1����~�� \n"); return false; }
	if( !logoImage.data ) { printf("��ȡlogoImage����~�� \n"); return false; }

	// ��2������һ��Mat���Ͳ������趨ROI����
	//  ָ��ͼ���е�һ������������Ϊ����Ȥ����
	Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));

	// ��3��������ģ�������ǻҶ�ͼ��
	Mat mask= imread("dota_logo.jpg",0);

	//��4������Ĥ������ROI
	logoImage.copyTo(imageROI,mask);

	// ��5����ʾ���
	namedWindow("<1>����ROIʵ��ͼ�����ʾ������");
	imshow("<1>����ROIʵ��ͼ�����ʾ������",srcImage1);
	waitKey(0);
	return 0;
}