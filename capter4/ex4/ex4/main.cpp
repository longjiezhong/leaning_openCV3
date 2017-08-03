#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

/*
图像的引用与复制问题
1 只复制信息头
2 把信息头和数据矩阵都复制过来
*/
int main(int argc, char** argv)
{
	Mat a, c;	//定义了两个信息头
	a = imread("1.bmp");
	Mat b(a);   //只复制了信息头和矩阵指针，而不复制矩阵数据，因为矩阵指针已经指向了矩阵数据
	c = a;		//复制了信息头和矩阵指针
	/*上面3个变量都指向了同一个图像数据矩阵*/

	//感兴趣区域
	Mat d(a,Rect(10,10,100,100));
	Mat e = a(Range::all(), Range(1,30));

	Mat f = a.clone();	//把a的信息头和矩阵数据都复制了一遍到f
	Mat g;
	a.copyTo(g);		//把a的信息头和矩阵数据都复制了一遍到g

	Mat m(2, 2, CV_8UC3, Scalar(0, 0, 255));	//直接用构造函数
	cout << "m = " << endl << " " << m << endl;

	IplImage* img = cvLoadImage("1.bmp",1);
	Mat mtx(img);								//把IplImage转换成Mat
	imshow("mtx",mtx);

	Mat n;
	n.create(4, 4, CV_8UC(2));					//用create开辟内存
	cout << "n = " << endl << " " << n << endl;

	//对小矩阵用逗号分隔符初始化函数
	Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "C = " << endl << " " << C << endl;

	//为已存在的对象创建新信息头
	Mat RowClone = C.row(1).clone();			//复制了第2行的数据
	cout << "RowClone = " << endl << " " << RowClone << endl << endl;

	//格式化输出图像
	Mat r = Mat(6, 6, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));
	//cout << "r(format of opencv) = " << endl << " " << r << ";"  <<endl << endl;
	//cout << "r(format of Python) = " << endl << " " << format(r, "python") << ";"  <<endl << endl;
	//cout << "r(format of csv) = " << endl << " " << format(r, "csv") << ";"  <<endl << endl;
	//cout << "r(format of C) = " << endl << " " << format(r, "C") << ";"  <<endl << endl;

	Point2f p(6,2);
	cout << "【二维点】 p = " << p << ";\n" << endl;

	Point3f p3(6,2,0);
	cout << "【三维点】 p3 = " << p3 << ";\n" << endl;

	vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	cout << "【基于Mat的vector】 shortvet = " << endl <<  " " << Mat(v) << ";\n" << endl;

	vector<Point2f> points(20);
	for(size_t i = 0; i < points.size(); ++i)
		points[i] = Point2f((float)(i * 5), (float)(i % 7));
	cout << "【二维点向量】points = " << endl << " " << points << ";";

	/*
	常用数据结构与函数
	1 点的表示：Point类
	2 颜色的表示：Scalar类
	3 尺寸的表示：Size类
	4 矩形的表示：Rect类
	5 颜色空间转换：cvtColor()函数
	*/

	waitKey(0);
	return 0;
}