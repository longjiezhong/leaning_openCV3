#include<opencv2/opencv.hpp>
using namespace cv;

//��ͼ����и�ʴ
int main()
{
	//����ͼ��
	Mat srcImg = imread("girl.bmp");
	imshow("src",srcImg);
	//��ȡ�ں˾���
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat dstImg;
	//��ʴ����
	erode(srcImg,dstImg,element);		//�ص�
	imshow("��ʴЧ��",dstImg);
	waitKey(0);

	return 0;
}
