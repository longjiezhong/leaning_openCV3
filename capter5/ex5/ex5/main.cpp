#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	double time0 = static_cast<double>(getTickCount());	//��¼��ʼʱ��
	int divedeWith = 10;
	Mat table(1, 256, CV_8UC1);
	uchar* t = table.data;				//����һ����
	for(int i = 0; i < 256; i++)		//��ʼ�������,��ɫ����
		t[i] = divedeWith * (i / divedeWith);

	Mat lookUpTable(1, 256, CV_8UC1);	//����һ��Mat
	uchar *p = lookUpTable.data;
	for(int i = 0; i < 256; ++i)
		p[i] = t[i];					//Mat�ӱ��ֶ�ȡ������

	for(int i = 0; i < 256; ++i)
		p[i] = i;						//Mat�ӱ���ȡ������

	cout << lookUpTable << endl;
	cout << endl;

	LUT(lookUpTable, table, lookUpTable);	//���ÿ��ṩ�Ĳ��ұ�

	cout << lookUpTable << endl;

	//��ʱ = ������ʱ�� - ��ʼʱ�䣩/ʱ��Ƶ��
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "����ʱ�� = " << time0 << endl;

	return 0;
}