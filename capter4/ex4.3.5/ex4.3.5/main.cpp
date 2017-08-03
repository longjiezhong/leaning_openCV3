#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

#define WINDOW_NAME1 "绘制图1"
#define WINDOW_NAME2 "绘制图2"
#define WINDOW_WIDTH 600

//绘制椭圆
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;

	ellipse(img,
		Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2),	//圆心位置
		Size(WINDOW_WIDTH/4, WINDOW_WIDTH/16),	//轴长度
		angle,									//偏转角度
		0,										//圆弧起始的角度
		360,									//圆弧终结的角度
		Scalar(255, 129, 0),					//线条颜色
		thickness,								//线条粗细
		lineType );								//线条类型
}

//绘制实心圆
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,
		center,									//圆心坐标
		WINDOW_WIDTH/32,						//圆半径
		Scalar(0, 0, 255),						//圆颜色
		thickness,								//线条粗细
		lineType );								//线条类型
}

//绘制凹多边形
void DrawPolygon(Mat img)
{
	int lineType = 8;
	Point rookPoints[1][20];
	rookPoints[0][0] = Point(WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8);
	rookPoints[0][1] = Point(3*WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8);
	rookPoints[0][2] = Point(3*WINDOW_WIDTH/4, 13*WINDOW_WIDTH/16);
	rookPoints[0][3] = Point(11*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16);
	rookPoints[0][4] = Point(19*WINDOW_WIDTH/32, 3*WINDOW_WIDTH/8);
	rookPoints[0][5] = Point(3*WINDOW_WIDTH/4, 3*WINDOW_WIDTH/8);
	rookPoints[0][6] = Point(3*WINDOW_WIDTH/4, WINDOW_WIDTH/8);
	rookPoints[0][7] = Point(26*WINDOW_WIDTH/40, WINDOW_WIDTH/8);
	rookPoints[0][8] = Point(26*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
	rookPoints[0][9] = Point(22*WINDOW_WIDTH/40, WINDOW_WIDTH/4);

	rookPoints[0][10] = Point(22*WINDOW_WIDTH/40, WINDOW_WIDTH/8);
	rookPoints[0][11] = Point(18*WINDOW_WIDTH/40, WINDOW_WIDTH/8);
	rookPoints[0][12] = Point(18*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
	rookPoints[0][13] = Point(14*WINDOW_WIDTH/40, WINDOW_WIDTH/4);
	rookPoints[0][14] = Point(14*WINDOW_WIDTH/40, WINDOW_WIDTH/8);
	rookPoints[0][15] = Point(WINDOW_WIDTH/4, WINDOW_WIDTH/8);
	rookPoints[0][16] = Point(WINDOW_WIDTH/4, 3*WINDOW_WIDTH/8);
	rookPoints[0][17] = Point(13*WINDOW_WIDTH/32, 3*WINDOW_WIDTH/8);
	rookPoints[0][18] = Point(5*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16);
	rookPoints[0][19] = Point(WINDOW_WIDTH/4, 13*WINDOW_WIDTH/16);

	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };

	//填充多边形内部
	fillPoly(img,
		ppt,						//多边形定点坐标集合
		npt,						//多边形的顶点个数
		1,							//组成填充区域的线段的数量
		Scalar(255, 255, 255),		//多边形的颜色
		lineType );					//组成多边形的线条的类型
}

//绘制线段
void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img,
		start,					//线段起始位置
		end,					//线段结束为止
		Scalar(0, 0, 0),		//线段颜色
		thickness,
		lineType );
}

int main(void)
{
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	//绘制椭圆
	DrawEllipse( atomImage, 90);
	DrawEllipse( atomImage, 0);
	DrawEllipse( atomImage, -45);
	DrawEllipse( atomImage, 45);

	//绘制实心圆
	DrawFilledCircle( atomImage, Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2));

	//绘制多边形
	DrawPolygon( rookImage );

	//绘制矩形
	rectangle( rookImage,
		Point(0, 7*WINDOW_WIDTH/8),
		Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255),
		-1,
		8 );

	//绘制线段
	DrawLine( rookImage, Point( 0, 15*WINDOW_WIDTH/16 ), Point( WINDOW_WIDTH, 15*WINDOW_WIDTH/16 ) );
	DrawLine( rookImage, Point( WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/4, WINDOW_WIDTH ) );
	DrawLine( rookImage, Point( WINDOW_WIDTH/2, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/2, WINDOW_WIDTH ) );
	DrawLine( rookImage, Point( 3*WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( 3*WINDOW_WIDTH/4, WINDOW_WIDTH ) );

	imshow( WINDOW_NAME1, atomImage);
	imshow( WINDOW_NAME2, rookImage);

	//把显示的图像放置在屏幕的指定位置
	moveWindow( WINDOW_NAME1, 0, 200);
	moveWindow( WINDOW_NAME2, WINDOW_WIDTH, 200);

	waitKey(0);
	return 0;
}