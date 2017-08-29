#include <opencv2/opencv.hpp>
using namespace cv;

//测试能把2d点包围的最小圆

int main( )
{
	Mat image(600, 600, CV_8UC3);
	RNG&  rng = theRNG();

	while(1)
	{
		int count = (unsigned) rng%100 + 3;
		//点数组里面
		vector<Point> points;

		for(int i = 0; i < count; i++)
		{
			Point point;
			//确定点位置
			point.x = rng.uniform(image.cols/4, image.cols*3/4);
			point.y = rng.uniform(image.cols/4, image.cols*3/4);

			//把点放到点数组里面
			points.push_back(point);
		}

		Point2f center;
		float radius = 0;
		minEnclosingCircle(Mat(points), center, radius);

		//把随机点绘制出来
		image = Scalar::all(0);
		for(int i = 0; i < count; i++)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED, CV_AA);

		circle(image, center, cvRound(radius), Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255)), 2, CV_AA);

		imshow("圆包围示例示例", image);

		if(waitKey() == 27)
			break;
	}

	return 0;
}