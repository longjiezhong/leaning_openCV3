#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//第1种方法：指针
void colorReducePoint(Mat& inpuImg, Mat& outputImage, int div)
{
	outputImage = inpuImg.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols * outputImage.channels();	//总列数

	for(int i = 0; i < rowNumber; i++)
	{
		uchar* data = outputImage.ptr<uchar>(i);				//某一行的数据地址
		for(int j = 0; j < colNumber; j++)
		{
			data[j] = data[j] / div * div + div / 2;
		}
	}
}


//第2种方法：迭代器
void colorReduceIterator(Mat& inpuImg, Mat& outputImage, int div)
{
	outputImage = inpuImg.clone();
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();		//数据开始
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();		//数据结束

	for(; it != itend; it++)
	{
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}

//第3种方法：动态地址
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

//测试三种访问图像像素的效率差别
int main(int argc, char** argv)
{
	Mat srcImg = imread("1.bmp");
	imshow("src", srcImg);
	Mat dstImg;
	dstImg.create(srcImg.rows, srcImg.cols, srcImg.type());

	double time0 = static_cast<double>(getTickCount());
	colorReducePoint(srcImg, dstImg, 32);						//指针操作访问
	//colorReduceDynamicAddress(srcImg, dstImg, 32);			//动态地址访问
	//colorReduceIterator(srcImg, dstImg, 32);					//迭代器访问
	time0 = ((double)getTickCount() - time0) / getTickFrequency();

	cout << time0 << endl;
	imshow("dst", dstImg);
	waitKey(0);
	return 0;
}
