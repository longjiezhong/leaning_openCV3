#include <opencv2/opencv.hpp>
using namespace cv;

//测试色相-饱和度直方图统计
int main()
{
	Mat srcImage, hsvImage;
	srcImage = imread("1.jpg");
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);			//转换成HSV空间

	int hueBinNum = 30;										//色相分成30格
	int saturationBinNum = 32;								//饱和度分成32格
	int histSize[ ] = {hueBinNum, saturationBinNum};		//二维直方图
	float hueRanges[] = {0, 180};							//只统计0-180度的色相
	float saturationRanges[] = {0, 256};					//饱和度
	const float* ranges[] = {hueRanges, saturationRanges};	//180*256大小的二维数组
	MatND dstHist;											//直方图
	int channels[] = {0, 1};								//只统计色相和饱和度，忽略亮度

	calcHist(&hsvImage,			//要计算的图片序列
		1,						//序列中最有1张需要计算
		channels,				//H和S通道需要计算
		Mat(),					//不使用掩膜
		dstHist,				//计算后的直方图
		2,						//需要计算的直方图为二维
		histSize,				//每个维度的尺寸
		ranges,					//每个维度的取值范围
		true,					//是否均匀
		false);					//是否累积

	double maxValue = 0;
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);		//把直方图的最大值找出来
	int scale = 10;
	Mat histImg = Mat::zeros(saturationBinNum*scale, hueBinNum*10,CV_8UC3);

	for(int hue = 0; hue < hueBinNum; hue++)
	{
		for(int saturation = 0; saturation < saturationBinNum;
			saturation++)
		{
			float binValue = dstHist.at<float>(hue, saturation);	//取直方图中的值,即某色相时对应某饱和度的像素数量有多少
			int intensity = cvRound(binValue*255/maxValue);			//计算强度

			rectangle(histImg,										//每个值都在图上用一个小矩形表示出来
				Point(hue*scale, saturation*scale),
				Point( (hue+1)*scale - 1, (saturation+1)*scale - 1 ),
				Scalar::all(intensity), 
				CV_FILLED);
		}
	}

	imshow("素材图", srcImage);
	imshow("H-S直方图", histImg);

	waitKey();
}