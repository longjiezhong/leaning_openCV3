#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

#define WINDOW_NAME1 "����ͼ1"
#define WINDOW_NAME2 "����ͼ2"
#define WINDOW_WIDTH 600

//������Բ
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;

	ellipse(img,
		Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2),	//Բ��λ��
		Size(WINDOW_WIDTH/4, WINDOW_WIDTH/16),	//�᳤��
		angle,									//ƫת�Ƕ�
		0,										//Բ����ʼ�ĽǶ�
		360,									//Բ���ս�ĽǶ�
		Scalar(255, 129, 0),					//������ɫ
		thickness,								//������ϸ
		lineType );								//��������
}

//����ʵ��Բ
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,
		center,									//Բ������
		WINDOW_WIDTH/32,						//Բ�뾶
		Scalar(0, 0, 255),						//Բ��ɫ
		thickness,								//������ϸ
		lineType );								//��������
}

//���ư������
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

	//��������ڲ�
	fillPoly(img,
		ppt,						//����ζ������꼯��
		npt,						//����εĶ������
		1,							//������������߶ε�����
		Scalar(255, 255, 255),		//����ε���ɫ
		lineType );					//��ɶ���ε�����������
}

//�����߶�
void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img,
		start,					//�߶���ʼλ��
		end,					//�߶ν���Ϊֹ
		Scalar(0, 0, 0),		//�߶���ɫ
		thickness,
		lineType );
}

int main(void)
{
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	//������Բ
	DrawEllipse( atomImage, 90);
	DrawEllipse( atomImage, 0);
	DrawEllipse( atomImage, -45);
	DrawEllipse( atomImage, 45);

	//����ʵ��Բ
	DrawFilledCircle( atomImage, Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2));

	//���ƶ����
	DrawPolygon( rookImage );

	//���ƾ���
	rectangle( rookImage,
		Point(0, 7*WINDOW_WIDTH/8),
		Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255),
		-1,
		8 );

	//�����߶�
	DrawLine( rookImage, Point( 0, 15*WINDOW_WIDTH/16 ), Point( WINDOW_WIDTH, 15*WINDOW_WIDTH/16 ) );
	DrawLine( rookImage, Point( WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/4, WINDOW_WIDTH ) );
	DrawLine( rookImage, Point( WINDOW_WIDTH/2, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/2, WINDOW_WIDTH ) );
	DrawLine( rookImage, Point( 3*WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( 3*WINDOW_WIDTH/4, WINDOW_WIDTH ) );

	imshow( WINDOW_NAME1, atomImage);
	imshow( WINDOW_NAME2, rookImage);

	//����ʾ��ͼ���������Ļ��ָ��λ��
	moveWindow( WINDOW_NAME1, 0, 200);
	moveWindow( WINDOW_NAME2, WINDOW_WIDTH, 200);

	waitKey(0);
	return 0;
}