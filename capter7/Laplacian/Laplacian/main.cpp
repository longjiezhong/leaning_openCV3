#include <opencv2/opencv.hpp>
using namespace cv;

//����������˹����

int main( )
{
	Mat src = imread("1.jpg");
	imshow("ԭͼ", src);

	Mat src_gray, abs_dst, dst;
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);

	imshow("Ч��ͼ", abs_dst);

	waitKey(0);
	return 0;

}