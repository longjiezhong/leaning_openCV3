#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	double time0 = static_cast<double>(getTickCount());	//记录起始时间
	int divedeWith = 10;
	Mat table(1, 256, CV_8UC1);
	uchar* t = table.data;				//定义一个表
	for(int i = 0; i < 256; i++)		//初始化这个表,颜色缩减
		t[i] = divedeWith * (i / divedeWith);

	Mat lookUpTable(1, 256, CV_8UC1);	//定义一个Mat
	uchar *p = lookUpTable.data;
	for(int i = 0; i < 256; ++i)
		p[i] = t[i];					//Mat从表手动取得数据

	for(int i = 0; i < 256; ++i)
		p[i] = i;						//Mat从表来取得数据

	cout << lookUpTable << endl;
	cout << endl;

	LUT(lookUpTable, table, lookUpTable);	//调用库提供的查找表

	cout << lookUpTable << endl;

	//耗时 = （结束时间 - 起始时间）/时钟频率
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "运行时间 = " << time0 << endl;

	return 0;
}