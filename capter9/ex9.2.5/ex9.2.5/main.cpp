#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat srcImage;
	//srcImage = imread("1.jpg");
	srcImage = imread("2.bmp");

	imshow("src", srcImage);

	int bins = 256;
	int hist_size[] = {bins};
	float range[] = {0, 256};
	const float* ranges[] = {range};
	MatND redHist, greenHist, blueHist;						//���ֱ��ͼ�ľ���

	int channels_r[] = { 2 };								//��ɫ����ֱ��ͼ
	calcHist(&srcImage, 1, channels_r, Mat(),
		redHist, 1, hist_size, ranges, true, false);

	int channels_g[] = { 1 };								//��ɫ����ֱ��ͼ
	calcHist(&srcImage, 1, channels_g, Mat(),
		greenHist, 1, hist_size, ranges, true, false);

	int channels_b[] = { 0 };								//��ɫ����ֱ��ͼ
	calcHist(&srcImage, 1, channels_b, Mat(),
		blueHist, 1, hist_size, ranges, true, false);

	double maxValue_red, maxValue_green, maxValue_blue;
	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
	minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);

	int scale = 1;
	int histHeight = 256;
	Mat histImage = Mat::zeros(histHeight, bins*3, CV_8UC3);

	for(int i = 0; i < bins; i++)
	{
		float binValue_red = redHist.at<float>(i);
		float binValue_green = greenHist.at<float>(i);
		float binValue_blue = blueHist.at<float>(i);

		int intensity_red = cvRound(binValue_red*histHeight/maxValue_red);
		int intensity_green = cvRound(binValue_green*histHeight/maxValue_green);
		int intensity_blue = cvRound(binValue_blue*histHeight/maxValue_blue);

		//���öԽǵ����������Ѿ��λ�����
		rectangle(histImage, Point(i*scale, histHeight-1),
			Point((i+1)*scale-1, histHeight-intensity_red),
			CV_RGB(255, 0, 0));

		rectangle(histImage, Point((i+bins)*scale, histHeight-1),
			Point((i+bins+1)*scale-1, histHeight-intensity_green),
			CV_RGB(0, 255, 0));

		rectangle(histImage, Point((i + bins * 2)*scale, histHeight-1),
			Point((i+bins*2+1)*scale-1, histHeight-intensity_blue),
			CV_RGB(0, 0, 255));
	}

	imshow("rgbֱ��ͼ", histImage);
	waitKey(0);
	return 0;
}