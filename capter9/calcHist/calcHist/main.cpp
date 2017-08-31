#include <opencv2/opencv.hpp>
using namespace cv;

//����ɫ��-���Ͷ�ֱ��ͼͳ��
int main()
{
	Mat srcImage, hsvImage;
	srcImage = imread("1.jpg");
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);			//ת����HSV�ռ�

	int hueBinNum = 30;										//ɫ��ֳ�30��
	int saturationBinNum = 32;								//���Ͷȷֳ�32��
	int histSize[ ] = {hueBinNum, saturationBinNum};		//��άֱ��ͼ
	float hueRanges[] = {0, 180};							//ֻͳ��0-180�ȵ�ɫ��
	float saturationRanges[] = {0, 256};					//���Ͷ�
	const float* ranges[] = {hueRanges, saturationRanges};	//180*256��С�Ķ�ά����
	MatND dstHist;											//ֱ��ͼ
	int channels[] = {0, 1};								//ֻͳ��ɫ��ͱ��Ͷȣ���������

	calcHist(&hsvImage,			//Ҫ�����ͼƬ����
		1,						//����������1����Ҫ����
		channels,				//H��Sͨ����Ҫ����
		Mat(),					//��ʹ����Ĥ
		dstHist,				//������ֱ��ͼ
		2,						//��Ҫ�����ֱ��ͼΪ��ά
		histSize,				//ÿ��ά�ȵĳߴ�
		ranges,					//ÿ��ά�ȵ�ȡֵ��Χ
		true,					//�Ƿ����
		false);					//�Ƿ��ۻ�

	double maxValue = 0;
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);		//��ֱ��ͼ�����ֵ�ҳ���
	int scale = 10;
	Mat histImg = Mat::zeros(saturationBinNum*scale, hueBinNum*10,CV_8UC3);

	for(int hue = 0; hue < hueBinNum; hue++)
	{
		for(int saturation = 0; saturation < saturationBinNum;
			saturation++)
		{
			float binValue = dstHist.at<float>(hue, saturation);	//ȡֱ��ͼ�е�ֵ,��ĳɫ��ʱ��Ӧĳ���Ͷȵ����������ж���
			int intensity = cvRound(binValue*255/maxValue);			//����ǿ��

			rectangle(histImg,										//ÿ��ֵ����ͼ����һ��С���α�ʾ����
				Point(hue*scale, saturation*scale),
				Point( (hue+1)*scale - 1, (saturation+1)*scale - 1 ),
				Scalar::all(intensity), 
				CV_FILLED);
		}
	}

	imshow("�ز�ͼ", srcImage);
	imshow("H-Sֱ��ͼ", histImg);

	waitKey();
}