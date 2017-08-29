#include <opencv2/opencv.hpp>
using namespace cv;

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

		vector<int> hull;
		//检测凸包
		convexHull(Mat(points), hull, true);

		//把随机点绘制出来
		image = Scalar::all(0);
		for(int i = 0; i < count; i++)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED, CV_AA);

		int hullcount = (int)hull.size();			//凸包点个数
		Point point0 = points[hull[hullcount-1]];	//凸包最后一个点

		for(int i = 0; i < hullcount; i++)			//把凸包点用连线连接起来
		{
			Point point = points[hull[i]];
			line(image, point0, point, Scalar(255, 255, 255),
				2, CV_AA);
			point0 = point;
		}

		imshow("凸包检测示例", image);

		if(waitKey() == 27)
			break;
	}

	return 0;
}