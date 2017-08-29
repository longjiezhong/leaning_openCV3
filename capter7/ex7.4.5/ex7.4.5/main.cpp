#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "src"
#define WINDOW_NAME2 "warp"
#define WINDOW_NAME3 "warp & rotate"

//���Է���任

int main()
{
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];

	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	srcImage = imread("girl.bmp", 1);

	dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols,
		srcImage.type());

	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols -1),
		0);
	srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));

	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols * 0.0), 
		static_cast<float>(srcImage.rows * 0.33));

	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols * 0.65), 
		static_cast<float>(srcImage.rows * 0.35));

	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols * 0.15), 
		static_cast<float>(srcImage.rows * 0.6));

	//��֪ԭͼ��3����Ͷ�Ӧ��Ŀ��ͼ��3���㣬���Ӧ��ϵ
	warpMat = getAffineTransform(srcTriangle, dstTriangle);

	//���ñ任��ϵ�������ͼƬ�ķ���任
	warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());

	Point center = Point(dstImage_warp.cols/2, dstImage_warp.rows/2);
	double angle = -30.0;
	double scale = 0.8;

	//����ͼ������ĳһ����ת�ľ���
	rotMat = getRotationMatrix2D(center, angle, scale);

	//��ת����
	warpAffine(dstImage_warp, dstImage_warp_rotate, rotMat,
		dstImage_warp.size());

	imshow(WINDOW_NAME1, srcImage);					//Դͼ��
	imshow(WINDOW_NAME2, dstImage_warp);			//����ͼ��
	imshow(WINDOW_NAME3, dstImage_warp_rotate);		//�������ת

	waitKey(0);
	return 0;
}