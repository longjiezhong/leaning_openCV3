#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("1.jpg");
	Mat midImage, dstImage, dstImage2;

	dstImage2 = Mat::zeros(srcImage.size(), srcImage.type());

	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, CV_GRAY2BGR);

	vector<Vec2f> lines;
	vector<Vec4i> lines2;
	HoughLines(midImage, 
		lines, 
		1,					//������Ϊ��λ�ľ��뾫��
		CV_PI/180,			//�Ի���Ϊ��λ�ĽǶȾ���
		170,				//�ۼ�ƽ�����ֵ
		0, 
		0);
	HoughLinesP(midImage, lines2, 1, CV_PI/180, 80, 50, 10);

	for(size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));

		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
	}

	for(size_t i = 0; i < lines2.size(); i++)
	{
		Vec4i l = lines2[i];
		line(dstImage2, Point(l[0], l[1]), Point(l[2], l[3]),
			Scalar(186,88,255), 1, CV_AA);
	}

	imshow("ԭͼ", srcImage);
	imshow("canny", midImage);
	imshow("houghLines", dstImage);
	imshow("houghLinesp", dstImage2);

	waitKey(0);
	return 0;
}