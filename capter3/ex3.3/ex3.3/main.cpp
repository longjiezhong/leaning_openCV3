#include "opencv2/opencv.hpp"
using namespace cv;

#define WINDOW_NAME "【程序窗口】"

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);
void ShowHelpText();

Rect g_rectangle;
bool g_bDrawingBox = false;			//绘制标识符
RNG g_rng(12345);

int main(int argc, char** argv)
{
	g_rectangle = Rect(-1,-1,0,0);
	Mat srcImg(600, 800, CV_8UC3), tempImg;
	srcImg.copyTo(tempImg);
	g_rectangle = Rect(-1,-1,0,0);
	srcImg = Scalar::all(0);

	//设置鼠标回调函数
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME,on_MouseHandle,(void*)&srcImg);
	while(1)
	{
		srcImg.copyTo(tempImg);
		//鼠标左键被按下后就一直绘制矩形，直到放开鼠标左键
		if( g_bDrawingBox )
			DrawRectangle(tempImg, g_rectangle);
		imshow(WINDOW_NAME, tempImg);
		if(waitKey(10) == 27)
			break;
	}
	return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	Mat& image = *(cv::Mat*)param;
	switch(event)
	{
	case CV_EVENT_MOUSEMOVE :
		{
			if(g_bDrawingBox)
			{
				g_rectangle.width = x - g_rectangle.x;
				g_rectangle.height = y - g_rectangle.y;
			}
		}
		break;;

	case CV_EVENT_LBUTTONDOWN:
		{
			g_bDrawingBox = true;
			g_rectangle = Rect(x, y, 0 ,0);
		}
		break;

	case EVENT_LBUTTONUP:
		{
			g_bDrawingBox = false;
			if(g_rectangle.width < 0)
			{
				g_rectangle.x += g_rectangle.width;
				g_rectangle.y *= -1;
			}

			if(g_rectangle.height < 0)
			{
				g_rectangle.y += g_rectangle.height;
				g_rectangle.height *= -1;
			}

			//绘制一个矩形
			DrawRectangle(image, g_rectangle);
		}
		break;
	}
}

void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	rectangle(img, box.tl(),box.br(),Scalar(g_rng.uniform(0,255),
		g_rng.uniform(0,255),g_rng.uniform(0,255)));
}