#include <opencv2/opencv.hpp>
using namespace cv;

int main( )
{
	Mat src = imread("1.jpg");
	Mat src1 = src.clone();

	imshow("ԭͼ", src);

	Mat dst, edge, gray;
	dst.create(src1.size(),src1.type());
	cvtColor(src1, gray, COLOR_RGB2GRAY);

	blur(gray, edge, Size(3,3));

	Canny(edge, edge, 64, 128, 3);

	dst = Scalar::all(0);
	src1.copyTo(dst, edge);

	imshow("Ч��ͼ", dst);
	waitKey(0);

	return 0;

}