#include <opencv2/opencv.hpp>
using namespace cv;

#define WINDOW_NAME1 "SRC"
#define WINDOW_NAME2 "DST"

Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 50;
int g_nMaxThresh = 255;
RNG g_rng(12345);

void on_ContoursChange(int, void*);

int main()
{
	g_srcImage = imread("3.jpg");
	//g_srcImage = imread("gray.bmp");

	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
	blur(g_grayImage, g_grayImage, Size(3,3));

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("��ֵ", WINDOW_NAME1, &g_nThresh, g_nMaxThresh,
		on_ContoursChange);

	on_ContoursChange(0, 0);

	waitKey(0);
	return 0;
}

void on_ContoursChange(int, void*)
{
	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//��ͼ���ֵ��
	threshold(g_grayImage, threshold_output, g_nThresh, 255,
		THRESH_BINARY);

	Mat midImage = g_grayImage.clone();

	//Ѱ��ͼ������
	findContours(threshold_output, contours, hierarchy, RETR_TREE,
		CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point>> contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for(unsigned int i=0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);			//��������߱ƽ�
		boundRect[i] = boundingRect(Mat(contours_poly[i]));					//���α߽�
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);			//Բ�α߽�
	}

	for(unsigned int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),
			g_rng.uniform(0, 255));

		drawContours(threshold_output, contours_poly, i,	color, 1, 8,	//��������
			vector<Vec4i>(), 0, Point());
		rectangle(threshold_output, boundRect[i].tl(), boundRect[i].br(),	//���α߽����
			color, 2, 8, 0);
		circle(threshold_output, center[i], (int)radius[i], color, 2, 8, 0);//Բ�α߽�
	}

	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, threshold_output);
}