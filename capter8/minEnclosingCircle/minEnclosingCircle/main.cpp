#include <opencv2/opencv.hpp>
using namespace cv;

//�����ܰ�2d���Χ����СԲ

int main( )
{
	Mat image(600, 600, CV_8UC3);
	RNG&  rng = theRNG();

	while(1)
	{
		int count = (unsigned) rng%100 + 3;
		//����������
		vector<Point> points;

		for(int i = 0; i < count; i++)
		{
			Point point;
			//ȷ����λ��
			point.x = rng.uniform(image.cols/4, image.cols*3/4);
			point.y = rng.uniform(image.cols/4, image.cols*3/4);

			//�ѵ�ŵ�����������
			points.push_back(point);
		}

		Point2f center;
		float radius = 0;
		minEnclosingCircle(Mat(points), center, radius);

		//���������Ƴ���
		image = Scalar::all(0);
		for(int i = 0; i < count; i++)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED, CV_AA);

		circle(image, center, cvRound(radius), Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255)), 2, CV_AA);

		imshow("Բ��Χʾ��ʾ��", image);

		if(waitKey() == 27)
			break;
	}

	return 0;
}