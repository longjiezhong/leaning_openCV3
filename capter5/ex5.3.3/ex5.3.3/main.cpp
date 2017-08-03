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
		cout<<endl<<"\n���гɹ����ó�����Ҫ��ͼ��~! ";
	}

	waitKey(0);
	return 0;
}


bool  MultiChannelBlending()
{
	//��0��������ر���
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat  imageBlueChannel;

	logoImage= imread("dota_logo.jpg",0);
	srcImage= imread("dota_jugg.jpg");

	if( !logoImage.data ) { printf("Oh��no����ȡlogoImage����~�� \n"); return false; }
	if( !srcImage.data ) { printf("Oh��no����ȡsrcImage����~�� \n"); return false; }

	split(srcImage,channels);//����ɫ��ͨ��
	imageBlueChannel= channels.at(0);

	//����ɫͨ���ϼ�LOGO
	addWeighted(imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,
		0,
		imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	merge(channels,srcImage);

	imshow(" <1>��Ϸԭ��+logo��ɫͨ��",srcImage);

	Mat  imageGreenChannel;

	logoImage= imread("dota_logo.jpg",0);
	srcImage= imread("dota_jugg.jpg");

	if( !logoImage.data ) { printf("��ȡlogoImage����~�� \n"); return false; }
	if( !srcImage.data ) { printf("��ȡsrcImage����~�� \n"); return false; }

	split(srcImage, channels);
	imageGreenChannel = channels.at(1);

	//����ɫͨ���ϼ�LOGO
	addWeighted(imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,
		0.,
		imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	merge(channels, srcImage);

	imshow("<2>��Ϸԭ��+logo��ɫͨ��",srcImage);

	Mat  imageRedChannel;

	logoImage= imread("dota_logo.jpg",0);
	srcImage= imread("dota_jugg.jpg");

	if( !logoImage.data ) { printf("Oh��no����ȡlogoImage����~�� \n"); return false; }
	if( !srcImage.data ) { printf("Oh��no����ȡsrcImage����~�� \n"); return false; }

	split(srcImage,channels);//����ɫ��ͨ��
	imageRedChannel= channels.at(2);

	//�ں�ɫͨ���ϼ�LOGO
	addWeighted(imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,
		0.,
		imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	merge(channels,srcImage);

	imshow("<3>��Ϸԭ��+logo��ɫͨ�� ",srcImage);

	return true;
}


