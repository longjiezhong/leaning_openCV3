#include <opencv2/opencv.hpp>
using namespace cv;

//测试拉普拉斯算子

int main( )
{
	Mat src = imread("1.jpg");
	imshow("原图", src);

	Mat src_gray, abs_dst, dst;
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);

	imshow("效果图", abs_dst);

	waitKey(0);
	return 0;

}