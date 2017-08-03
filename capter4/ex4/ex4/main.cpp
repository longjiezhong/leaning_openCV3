#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

/*
ͼ��������븴������
1 ֻ������Ϣͷ
2 ����Ϣͷ�����ݾ��󶼸��ƹ���
*/
int main(int argc, char** argv)
{
	Mat a, c;	//������������Ϣͷ
	a = imread("1.bmp");
	Mat b(a);   //ֻ��������Ϣͷ�;���ָ�룬�������ƾ������ݣ���Ϊ����ָ���Ѿ�ָ���˾�������
	c = a;		//��������Ϣͷ�;���ָ��
	/*����3��������ָ����ͬһ��ͼ�����ݾ���*/

	//����Ȥ����
	Mat d(a,Rect(10,10,100,100));
	Mat e = a(Range::all(), Range(1,30));

	Mat f = a.clone();	//��a����Ϣͷ�;������ݶ�������һ�鵽f
	Mat g;
	a.copyTo(g);		//��a����Ϣͷ�;������ݶ�������һ�鵽g

	Mat m(2, 2, CV_8UC3, Scalar(0, 0, 255));	//ֱ���ù��캯��
	cout << "m = " << endl << " " << m << endl;

	IplImage* img = cvLoadImage("1.bmp",1);
	Mat mtx(img);								//��IplImageת����Mat
	imshow("mtx",mtx);

	Mat n;
	n.create(4, 4, CV_8UC(2));					//��create�����ڴ�
	cout << "n = " << endl << " " << n << endl;

	//��С�����ö��ŷָ�����ʼ������
	Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "C = " << endl << " " << C << endl;

	//Ϊ�Ѵ��ڵĶ��󴴽�����Ϣͷ
	Mat RowClone = C.row(1).clone();			//�����˵�2�е�����
	cout << "RowClone = " << endl << " " << RowClone << endl << endl;

	//��ʽ�����ͼ��
	Mat r = Mat(6, 6, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));
	//cout << "r(format of opencv) = " << endl << " " << r << ";"  <<endl << endl;
	//cout << "r(format of Python) = " << endl << " " << format(r, "python") << ";"  <<endl << endl;
	//cout << "r(format of csv) = " << endl << " " << format(r, "csv") << ";"  <<endl << endl;
	//cout << "r(format of C) = " << endl << " " << format(r, "C") << ";"  <<endl << endl;

	Point2f p(6,2);
	cout << "����ά�㡿 p = " << p << ";\n" << endl;

	Point3f p3(6,2,0);
	cout << "����ά�㡿 p3 = " << p3 << ";\n" << endl;

	vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	cout << "������Mat��vector�� shortvet = " << endl <<  " " << Mat(v) << ";\n" << endl;

	vector<Point2f> points(20);
	for(size_t i = 0; i < points.size(); ++i)
		points[i] = Point2f((float)(i * 5), (float)(i % 7));
	cout << "����ά��������points = " << endl << " " << points << ";";

	/*
	�������ݽṹ�뺯��
	1 ��ı�ʾ��Point��
	2 ��ɫ�ı�ʾ��Scalar��
	3 �ߴ�ı�ʾ��Size��
	4 ���εı�ʾ��Rect��
	5 ��ɫ�ռ�ת����cvtColor()����
	*/

	waitKey(0);
	return 0;
}