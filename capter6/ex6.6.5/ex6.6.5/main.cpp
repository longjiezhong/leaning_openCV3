#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("1.jpg");
	Mat tmpImage, dstImage, dstImage2, dstImage3,
		dstImage4;
	tmpImage = srcImage;

	imshow("原图", srcImage);
	resize(tmpImage, dstImage, 
		Size(tmpImage.cols*2, tmpImage.rows*2),		//缩放后尺寸
		0, 0, 
		INTER_AREA);											//插值方式
	resize(tmpImage, dstImage2, 
		Size(tmpImage.cols*2, tmpImage.rows*2),		//缩放后尺寸
		0, 0, 
		INTER_LANCZOS4);

	pyrUp(tmpImage, dstImage3, 
		Size(tmpImage.cols*2, tmpImage.rows*2));	

	pyrDown(dstImage3, dstImage4,					//上采样->下采样
		Size(dstImage3.cols/2, dstImage3.rows/2));	

	imshow("效果图1", dstImage3);
	imshow("效果图2", dstImage4);

	waitKey(0);
	return 0;
}