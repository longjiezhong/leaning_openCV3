#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//��1�ַ�����ָ��
void colorReducePoint(Mat& inpuImg, Mat& outputImage, int div)
{
	outputImage = inpuImg.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols * outputImage.channels();	//������

	for(int i = 0; i < rowNumber; i++)
	{
		uchar* data = outputImage.ptr<uchar>(i);				//ĳһ�е����ݵ�ַ
		for(int j = 0; j < colNumber; j++)
		{
			data[j] = data[j] / div * div + div / 2;
		}
	}
}


//��2�ַ�����������
void colorReduceIterator(Mat& inpuImg, Mat& outputImage, int div)
{
	outputImage = inpuImg.clone();
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();		//���ݿ�ʼ
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();		//���ݽ���

	for(; it != itend; it++)
	{
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}

//��3�ַ�������̬��ַ
void colorReduceDynamicAddress(Mat& inpuImg, Mat& outputImage, int div)
{
	outputImage = inpuImg.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;

	for(int i = 0; i < rowNumber; i++)
	{
		for(int j = 0; j < colNumber; j++)
		{
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;
		}
	}
}

//�������ַ���ͼ�����ص�Ч�ʲ��
int main(int argc, char** argv)
{
	Mat srcImg = imread("1.bmp");
	imshow("src", srcImg);
	Mat dstImg;
	dstImg.create(srcImg.rows, srcImg.cols, srcImg.type());

	double time0 = static_cast<double>(getTickCount());
	colorReducePoint(srcImg, dstImg, 32);						//ָ���������
	//colorReduceDynamicAddress(srcImg, dstImg, 32);			//��̬��ַ����
	//colorReduceIterator(srcImg, dstImg, 32);					//����������
	time0 = ((double)getTickCount() - time0) / getTickFrequency();

	cout << time0 << endl;
	imshow("dst", dstImg);
	waitKey(0);
	return 0;
}
