#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool  MultiChannelBlending();

int main(   )
{
	if(MultiChannelBlending( ))
	{
		cout<<endl<<"\n运行成功，得出了需要的图像~! ";
	}

	waitKey(0);
	return 0;
}


bool  MultiChannelBlending()
{
	//【0】定义相关变量
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat  imageBlueChannel;

	logoImage= imread("dota_logo.jpg",0);
	srcImage= imread("dota_jugg.jpg");

	if( !logoImage.data ) { printf("Oh，no，读取logoImage错误~！ \n"); return false; }
	if( !srcImage.data ) { printf("Oh，no，读取srcImage错误~！ \n"); return false; }

	split(srcImage,channels);//分离色彩通道
	imageBlueChannel= channels.at(0);

	//在蓝色通道上加LOGO
	addWeighted(imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,
		0,
		imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	merge(channels,srcImage);

	imshow(" <1>游戏原画+logo蓝色通道",srcImage);

	Mat  imageGreenChannel;

	logoImage= imread("dota_logo.jpg",0);
	srcImage= imread("dota_jugg.jpg");

	if( !logoImage.data ) { printf("读取logoImage错误~！ \n"); return false; }
	if( !srcImage.data ) { printf("读取srcImage错误~！ \n"); return false; }

	split(srcImage, channels);
	imageGreenChannel = channels.at(1);

	//在绿色通道上加LOGO
	addWeighted(imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,
		0.,
		imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	merge(channels, srcImage);

	imshow("<2>游戏原画+logo绿色通道",srcImage);

	Mat  imageRedChannel;

	logoImage= imread("dota_logo.jpg",0);
	srcImage= imread("dota_jugg.jpg");

	if( !logoImage.data ) { printf("Oh，no，读取logoImage错误~！ \n"); return false; }
	if( !srcImage.data ) { printf("Oh，no，读取srcImage错误~！ \n"); return false; }

	split(srcImage,channels);//分离色彩通道
	imageRedChannel= channels.at(2);

	//在红色通道上加LOGO
	addWeighted(imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,
		0.,
		imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	merge(channels,srcImage);

	imshow("<3>游戏原画+logo红色通道 ",srcImage);

	return true;
}


