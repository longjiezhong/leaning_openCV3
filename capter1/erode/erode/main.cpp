#include<opencv2/opencv.hpp>
using namespace cv;

//对图像进行腐蚀
int main()
{
	//载入图像
	Mat srcImg = imread("girl.bmp");
	imshow("src",srcImg);
	//获取内核矩阵
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat dstImg;
	//腐蚀处理
	erode(srcImg,dstImg,element);		//重点
	imshow("腐蚀效果",dstImg);
	waitKey(0);

	return 0;
}
