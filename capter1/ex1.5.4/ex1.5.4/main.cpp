#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat srcImg = imread("girl.bmp");
	imshow("Canny��Ե��⣨ԭͼ��",srcImg);
	Mat dstImg,edge,grayImg;
	//dstImg.create(srcImg.size(),srcImg.type());

	cvtColor(srcImg,grayImg,CV_RGB2GRAY);
	blur(srcImg,edge,Size(8,8));
	Canny(edge,edge,3,9,3);						//�ص�
	imshow("Canny��Ե��⣨Ч��ͼ��",edge);
	imwrite("CannyGirl2.bmp",edge);

	waitKey(0);
	return 0;
}