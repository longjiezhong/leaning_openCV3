#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage;
int g_nTrackbarNumer = 0;
int g_nStructElementSize = 3;

void Process();
void on_TrackbarNumchange(int, void *);
void on_ElementSizeChange(int ,void *);

int main()
{
	g_srcImage = imread("1.png");
	namedWindow("ԭͼ");
	imshow("ԭͼ", g_srcImage);

	namedWindow("Ч��ͼ");
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),
		Point(g_nStructElementSize, g_nStructElementSize));
	erode(g_srcImage, g_dstImage, element);
	imshow("Ч��ͼ", g_dstImage);

	createTrackbar("��ʴ/����","Ч��ͼ",&g_nTrackbarNumer, 1, on_TrackbarNumchange);
	createTrackbar("�ں˳ߴ�","Ч��ͼ", &g_nStructElementSize, 21, on_ElementSizeChange);

	while(char(waitKey(1)) != 'q'){}

	return 0;
}

void Process()
{
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),
		Point(g_nStructElementSize, g_nStructElementSize));

	if(g_nTrackbarNumer == 0)
	{
		erode(g_srcImage, g_dstImage, element);
	}
	else
	{
		dilate(g_srcImage, g_dstImage, element);
	}

	imshow("Ч��ͼ", g_dstImage);

}

void on_TrackbarNumchange(int, void *)
{
	Process();
}

void on_ElementSizeChange(int, void *)
{
	Process();
}