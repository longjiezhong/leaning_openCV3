#include <opencv2\opencv.hpp>

using namespace cv;

int main()
{
	Mat frame;
	//VideoCapture capture("1.avi");//����Ƶ�ļ�
	VideoCapture capture(0);		//������ͷ
	if(!capture.read(frame))  //����Ƶ�ļ��ж���һ֡ͼ��
		return -1;
	VideoWriter writer;
	writer.open("out.avi",CV_FOURCC('D','I','V','X'),24,frame.size(),true);

	while(1)
	{
		if(!capture.read(frame))  //����Ƶ�ļ��ж���һ֡ͼ��
			break;
		writer << frame;		  //��һ֡ͼ��洢����Ƶ�ļ���
		imshow("��ȡ��Ƶ",frame);
		waitKey(30);
	}

	writer.release();
	capture.release();
	return 0;
}