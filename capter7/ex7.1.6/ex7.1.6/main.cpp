#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//ԭͼ��ԭͼ�ĻҶȰ棬Ŀ��ͼ
Mat g_srcImage, g_srcGrayImage,g_dstImage;

//Canny��Ե�����ر���
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold=1;//TrackBarλ�ò���  

//Sobel��Ե�����ر���
Mat g_sobelGradient_X, g_sobelGradient_Y;
Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
int g_sobelKernelSize=1;//TrackBarλ�ò���  

int g_LaplacianKernelSize=1;

//Scharr�˲�����ر���
Mat g_scharrGradient_X, g_scharrGradient_Y;
Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;


//-----------------------------------��ȫ�ֺ����������֡�--------------------------------------
//		������ȫ�ֺ�������
//-----------------------------------------------------------------------------------------------
static void on_Canny(int, void*);//Canny��Ե��ⴰ�ڹ������Ļص�����
static void on_Sobel(int, void*);//Sobel��Ե��ⴰ�ڹ������Ļص�����
static void on_Laplacian(int, void*);//������˹����
void Scharr( );//��װ��Scharr��Ե�����ش���ĺ���

//���ؼ���ۺ�
int main( int argc, char** argv )
{
	//����ԭͼ
	g_srcImage = imread("1.jpg");
	if( !g_srcImage.data ) { printf("Oh��no����ȡsrcImage����~�� \n"); return false; }

	//��ʾԭʼͼ
	namedWindow("��ԭʼͼ��");
	imshow("��ԭʼͼ��", g_srcImage);

	// ������srcͬ���ͺʹ�С�ľ���(dst)
	g_dstImage.create( g_srcImage.size(), g_srcImage.type() );

	// ��ԭͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor( g_srcImage, g_srcGrayImage, CV_BGR2GRAY );

	// ������ʾ����
	namedWindow( "��Ч��ͼ��Canny��Ե���", CV_WINDOW_AUTOSIZE );
	namedWindow( "��Ч��ͼ��Sobel��Ե���", CV_WINDOW_AUTOSIZE );
	namedWindow( "��Ч��ͼ��Laplacian��Ե���", CV_WINDOW_AUTOSIZE );

	// ����trackbar
	createTrackbar( "����ֵ��", "��Ч��ͼ��Canny��Ե���", &g_cannyLowThreshold, 120, on_Canny );
	createTrackbar( "����ֵ��", "��Ч��ͼ��Sobel��Ե���", &g_sobelKernelSize, 3, on_Sobel );
	createTrackbar( "����ֵ��", "��Ч��ͼ��Laplacian��Ե���", &g_LaplacianKernelSize, 3, on_Laplacian );

	// ���ûص�����
	on_Canny(0, 0);
	on_Sobel(0, 0);
	on_Laplacian(0, 0);

	//���÷�װ��Scharr��Ե������ĺ���
	Scharr( );

	//��ѯ��ȡ������Ϣ��������Q�������˳�
	while((char(waitKey(1)) != 'q')) {}

	return 0;
}

//-----------------------------------��on_Canny( )������----------------------------------
//		������Canny��Ե��ⴰ�ڹ������Ļص�����
//-----------------------------------------------------------------------------------------------
void on_Canny(int, void*)
{
	// ��ʹ�� 3x3�ں�������
	blur( g_srcGrayImage, g_cannyDetectedEdges, Size(3,3) );

	// �������ǵ�Canny����
	Canny( g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold*3, 3 );

	//�Ƚ�g_dstImage�ڵ�����Ԫ������Ϊ0 
	g_dstImage = Scalar::all(0);

	//ʹ��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ���룬����ԭͼg_srcImage����Ŀ��ͼg_dstImage��
	g_srcImage.copyTo( g_dstImage, g_cannyDetectedEdges);

	//��ʾЧ��ͼ
	imshow( "��Ч��ͼ��Canny��Ե���", g_dstImage );
}

void on_Laplacian(int, void*)
{
	Mat src_gray, dst;
	
	GaussianBlur(g_srcGrayImage, src_gray, Size(3, 3), 0, 0, BORDER_DEFAULT);

	Laplacian(src_gray, dst, CV_16S, g_LaplacianKernelSize*2+1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst, g_dstImage);

	imshow("��Ч��ͼ��Laplacian��Ե���", g_dstImage);

}


//-----------------------------------��on_Sobel( )������----------------------------------
//		������Sobel��Ե��ⴰ�ڹ������Ļص�����
//-----------------------------------------------------------------------------------------
void on_Sobel(int, void*)
{
	// �� X�����ݶ�
	Sobel( g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
	convertScaleAbs( g_sobelGradient_X, g_sobelAbsGradient_X );//�������ֵ���������ת����8λ

	// ��Y�����ݶ�
	Sobel( g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
	convertScaleAbs( g_sobelGradient_Y, g_sobelAbsGradient_Y );//�������ֵ���������ת����8λ

	// �ϲ��ݶ�
	addWeighted( g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage );

	//��ʾЧ��ͼ
	imshow("��Ч��ͼ��Sobel��Ե���", g_dstImage); 

}


//-----------------------------------��Scharr( )������----------------------------------
//		��������װ��Scharr��Ե�����ش���ĺ���
//-----------------------------------------------------------------------------------------
void Scharr( )
{
	// �� X�����ݶ�
	Scharr( g_srcImage, g_scharrGradient_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( g_scharrGradient_X, g_scharrAbsGradient_X );//�������ֵ���������ת����8λ

	// ��Y�����ݶ�
	Scharr( g_srcImage, g_scharrGradient_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( g_scharrGradient_Y, g_scharrAbsGradient_Y );//�������ֵ���������ת����8λ

	// �ϲ��ݶ�
	addWeighted( g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage );

	//��ʾЧ��ͼ
	imshow("��Ч��ͼ��Scharr�˲���", g_dstImage); 
}
