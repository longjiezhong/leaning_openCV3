#include <opencv2/opencv.hpp>
using namespace cv;

//�����ܰ�2d���Χ����С����

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

		//�Ը�����2d�㼯��Ѱ����С����İ�Χ����
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);							//��ȡ���ε�4����

		//���������Ƴ���
		image = Scalar::all(0);
		for(int i = 0; i < count; i++)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED, CV_AA);
		
		for(int i = 0; i < 4; i++)			//��͹������������������
		{
			line(image, vertex[i], vertex[(i+1)%4], Scalar(255, 255, 255),
				2, CV_AA);
		}

		imshow("���ΰ�Χʾ��ʾ��", image);

		if(waitKey() == 27)
			break;
	}

	return 0;
}