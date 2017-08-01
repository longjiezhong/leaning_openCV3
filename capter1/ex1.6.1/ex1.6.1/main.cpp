#include <opencv2\opencv.hpp>

using namespace cv;

int main()
{
	Mat frame;
	//VideoCapture capture("1.avi");//打开视频文件
	VideoCapture capture(0);		//打开摄像头
	if(!capture.read(frame))  //从视频文件中读出一帧图像
		return -1;
	VideoWriter writer;
	writer.open("out.avi",CV_FOURCC('D','I','V','X'),24,frame.size(),true);

	while(1)
	{
		if(!capture.read(frame))  //从视频文件中读出一帧图像
			break;
		writer << frame;		  //把一帧图像存储到视频文件中
		imshow("读取视频",frame);
		waitKey(30);
	}

	writer.release();
	capture.release();
	return 0;
}