#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage;
int g_nElementShape = MORPH_RECT;

int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;

static void on_OpenClose(int, void*);
static void on_ErodeDilate(int, void*);
static void on_TopBlackHat(int, void*);

int main()
{
	g_srcImage = imread("2.png");
	if(!g_srcImage.data)
		cout << "¶ÁÈ¡Í¼Æ¬´íÎó£¡" << endl;

	namedWindow("Ô­Í¼");
	imshow("Ô­Í¼", g_srcImage);


	namedWindow("¿ªÔËËã/±ÕÔËËã",1);
	namedWindow("¸¯Ê´/ÅòÕÍ",1);
	namedWindow("¶¥Ã±/ºÚÃ±",1);

	g_nOpenCloseNum = 9;
	g_nErodeDilateNum = 9;
	g_nTopBlackHatNum = 2;

	createTrackbar("µü´úÖµ","¿ªÔËËã/±ÕÔËËã", 
		&g_nOpenCloseNum, g_nMaxIterationNum*2+1,on_OpenClose);
	createTrackbar("µü´úÖµ","¸¯Ê´/ÅòÕÍ", 
		&g_nErodeDilateNum, g_nMaxIterationNum*2+1,on_ErodeDilate);
	createTrackbar("µü´úÖµ","¶¥Ã±/ºÚÃ±", 
		&g_nTopBlackHatNum, g_nMaxIterationNum*2+1,on_TopBlackHat);

	while(1)
	{
		char c;

		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackHatNum, 0);

		c = waitKey(0);

		if(c == 'q' || c == 27)
			break;
		if(c == 49)								//1
			g_nElementShape = MORPH_ELLIPSE;
		else if(c == 50)						//2
			g_nElementShape = MORPH_RECT;
		else if(c == 51)						//3
			g_nElementShape = MORPH_CROSS;
		else if(c == ' ')
			g_nElementShape = (g_nElementShape + 1) % 3;
	}

	return 0;

}


static void on_OpenClose(int, void*)
{
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;
	Mat elsment = getStructuringElement(g_nElementShape,
		Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset,
		Absolute_offset));

	if(offset < 0)
		morphologyEx(g_srcImage, g_dstImage, CV_MOP_OPEN, elsment);
	else
		morphologyEx(g_srcImage, g_dstImage, CV_MOP_CLOSE, elsment);

	imshow("¿ªÔËËã/±ÕÔËËã", g_dstImage);
}


static void on_ErodeDilate(int, void*)
{
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;	//ÎªÁË¾ö¶¨½á¹¹ÔªËØµÄ³ß´ç
	Mat elsment = getStructuringElement(g_nElementShape,
		Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset,
		Absolute_offset));

	if(offset < 0)
		erode(g_srcImage, g_dstImage, elsment);
	else
		dilate(g_srcImage, g_dstImage, elsment);

	imshow("¸¯Ê´/ÅòÕÍ", g_dstImage);
}

static void on_TopBlackHat(int, void*)
{
	int offset = g_nTopBlackHatNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;
	Mat elsment = getStructuringElement(g_nElementShape,
		Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset,
		Absolute_offset));

	if(offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, elsment);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, elsment);

	imshow("¶¥Ã±/ºÚÃ±", g_dstImage);
}