#include "opencv2/opencv.hpp"
#include <iostream>
#include <time.h>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//��д��ʽ��һ��yaml�ļ�
	FileStorage fs("test.yaml", FileStorage::WRITE);

	fs << "frameCount" << 5;		//���ļ�д����
	time_t rawtime; 
	time(&rawtime);
	fs << "calibrationDate" << asctime(localtime(&rawtime));

	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);

	//���ļ�дMat���ݽṹ
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;

	//дvector�ṹ
	fs << "features" << "[";
	for(int i = 0; i < 3; i++)
	{
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 256;

		//дmap�ṹ
		fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
		for(int j = 0; j < 8; j++)
			fs << ((lbp >> j) & 1);
		fs << "]" << "}";
	}

	fs << "]";
	fs.release();

	cout << "�ļ�д���!" << endl;
	getchar();

	system("color 6F");
	FileStorage fs2("test.yaml", FileStorage::READ);

	int frameCount = (int)fs2["frameCount"];
	std::string date;
	fs2["calibrationDate"] >> date;

	//��ȡMat
	Mat cameraMatrix2, distCoeffs2;
	fs2["cameraMatrix"] >> cameraMatrix2;
	fs2["distCoeffs"] >> distCoeffs2;

	cout 
		<< "frameCount:" <<frameCount << endl
		<< "calibrationDate:" <<date << endl
		<< "cameraMatrix:" <<cameraMatrix2 << endl
		<< "distCoeffs:" <<distCoeffs2 << endl;

	//��ȡ����ֵ
	FileNode features = fs2["features"];
	FileNodeIterator it = features.begin(), it_end = features.end();
	int idx = 0;
	std::vector<uchar> lbpval;

	for(; it != it_end; it++, idx++)
	{
		cout << "feature #" << idx << ": ";
		cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";
		(*it)["lbp"] >> lbpval;
		for(int i = 0; i< (int)lbpval.size(); i++)
			cout << " " << (int)lbpval[i];
		cout << ")" << endl;
	}

	fs2.release();

	cout << "�ļ���ȡ��ϣ�" << endl;
	getchar();
	return 0;
}