#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("1.jpg");
	Mat midImage, dstImage;
	imshow("src", srcImage);
	cvtColor(srcImage, midImage, CV_BGR2GRAY);
	GaussianBlur(midImage, midImage, Size(9,9), 2, 2);
	vector<Vec3f> circels;

	//���л���任
	HoughCircles(midImage, circels, 
		CV_HOUGH_GRADIENT,		//ʹ�û����ݶȷ���
		1.5,  					//�ۼ����ֱ���������ֱ��ʵı����ĵ���
		10,						//Բ����Բ��֮�����С����
		120,					//canny��Ե���ĸ���ֵ
		100,					//���Բ�Ľ׶ε��ۼ�����ֵ
		0, 0);
	for(size_t i = 0; i< circels.size(); i++)
	{
		Point center(cvRound(circels[i][0]), cvRound(circels[i][1]));
		int radius = cvRound(circels[i][2]);
		//����Բ��
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

	imshow("Ч��", srcImage);
	waitKey(0);
	return 0;
}