#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#define WINDOW_NAME0 "ԭͼ"
#define WINDOW_NAME1 "�����˲�"
#define WINDOW_NAME2 "��ֵ�˲�"
#define WINDOW_NAME3 "��˹�˲�"
#define WINDOW_NAME4 "��ֵ�˲�"
#define WINDOW_NAME5 "˫���˲�"

Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3,g_dstImage4,g_dstImage5;
int g_nBoxFilterValue = 3;
int g_nMeanBlurValue = 3;
int g_nGaussianBlurValue = 3;
int g_nMedianBlurValue = 3;
int g_nBilateralFilterValue = 3;

static void on_BoxFilter(int, void *);		//�����˲�
static void on_MeanBlur(int, void *);		//��ֵ�˲�
static void on_GaussianBlur(int, void *);	//��˹�˲�
static void on_MedianBlur(int, void*);		//��ֵ�˲�
static void on_BilateralFilter(int, void*);	//˫���˲�

int main()
{
	g_srcImage = imread("2.bmp", 1);
	Mat src = imread("1.bmp", 1);
	imshow(WINDOW_NAME0, src);

	if(!g_srcImage.data)
	{
		cout << "��ȡԭͼƬ����" << endl;
		return false;
	}

	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	g_dstImage4 = g_srcImage.clone();
	g_dstImage5 = g_srcImage.clone();

	//namedWindow("ԭͼ", 1);
	//imshow("ԭͼ", g_srcImage);

	namedWindow(WINDOW_NAME1, 1);
	namedWindow(WINDOW_NAME2, 1);
	namedWindow(WINDOW_NAME3, 1);
	namedWindow(WINDOW_NAME4, 1);
	namedWindow(WINDOW_NAME5, 1);

	createTrackbar("�ں�ֵ", WINDOW_NAME1, &g_nBoxFilterValue, 
		40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	imshow("�����˲�", g_dstImage1);

	createTrackbar("�ں�ֵ", WINDOW_NAME2, &g_nMeanBlurValue, 
		40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);

	createTrackbar("�ں�ֵ", WINDOW_NAME3, &g_nGaussianBlurValue, 
		40, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);

	createTrackbar("�ں�ֵ", WINDOW_NAME4, &g_nMedianBlurValue, 
		40, on_MedianBlur);
	on_MedianBlur(g_nMedianBlurValue, 0);

	createTrackbar("�ں�ֵ", WINDOW_NAME5, &g_nBilateralFilterValue, 
		40, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);

	moveWindow( WINDOW_NAME0, 0, 0);
	moveWindow( WINDOW_NAME1, 0, 0);
	moveWindow( WINDOW_NAME2, 0, 0);
	moveWindow( WINDOW_NAME3, 0, 0);
	moveWindow( WINDOW_NAME4, 0, 0);
	moveWindow( WINDOW_NAME5, 0, 0);

	while(char(waitKey(1)) != 'q'){}
	return 0;

}

static void on_BoxFilter(int, void *)
{
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1,
		g_nBoxFilterValue + 1));
	imshow(WINDOW_NAME1, g_dstImage1);
}

static void on_MeanBlur(int, void *)
{
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue +1, 
		g_nMeanBlurValue + 1), Point(-1, -1));
	imshow(WINDOW_NAME2, g_dstImage2);
}

static void on_GaussianBlur(int, void *)
{
	GaussianBlur(g_srcImage, g_dstImage3,
		Size(g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1), 0, 0);
	imshow(WINDOW_NAME3, g_dstImage3);
}

static void on_MedianBlur(int, void *)
{
	medianBlur(g_srcImage, g_dstImage4,
		g_nMedianBlurValue*2+1);
	imshow(WINDOW_NAME4, g_dstImage4);
}

static void on_BilateralFilter(int, void*)
{
	bilateralFilter(g_srcImage, g_dstImage5, g_nBilateralFilterValue,
		g_nBilateralFilterValue*2, g_nBilateralFilterValue/2);
	imshow(WINDOW_NAME5, g_dstImage5);
}