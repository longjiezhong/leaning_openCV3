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

	//进行霍夫变换
	HoughCircles(midImage, circels, 
		CV_HOUGH_GRADIENT,		//使用霍夫梯度方法
		1.5,  					//累加器分辨率与输入分辨率的比例的倒数
		10,						//圆心与圆心之间的最小距离
		120,					//canny边缘检测的高阈值
		100,					//检测圆心阶段的累加器阈值
		0, 0);
	for(size_t i = 0; i< circels.size(); i++)
	{
		Point center(cvRound(circels[i][0]), cvRound(circels[i][1]));
		int radius = cvRound(circels[i][2]);
		//绘制圆心
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

	imshow("效果", srcImage);
	waitKey(0);
	return 0;
}