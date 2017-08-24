#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("1.jpg");
	Mat tmpImage, dstImage, dstImage2, dstImage3,
		dstImage4;
	tmpImage = srcImage;

	imshow("ԭͼ", srcImage);
	resize(tmpImage, dstImage, 
		Size(tmpImage.cols*2, tmpImage.rows*2),		//���ź�ߴ�
		0, 0, 
		INTER_AREA);											//��ֵ��ʽ
	resize(tmpImage, dstImage2, 
		Size(tmpImage.cols*2, tmpImage.rows*2),		//���ź�ߴ�
		0, 0, 
		INTER_LANCZOS4);

	pyrUp(tmpImage, dstImage3, 
		Size(tmpImage.cols*2, tmpImage.rows*2));	

	pyrDown(dstImage3, dstImage4,					//�ϲ���->�²���
		Size(dstImage3.cols/2, dstImage3.rows/2));	

	imshow("Ч��ͼ1", dstImage3);
	imshow("Ч��ͼ2", dstImage4);

	waitKey(0);
	return 0;
}