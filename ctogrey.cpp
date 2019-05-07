#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int maxi(int,int,int);
int minu(int,int,int);

int main()
{

	int i,j;
	
	Mat img=imread("lenna.jpg",1);
	Mat result(img.rows,img.cols,CV_8UC1,Scalar(0));
	
	namedWindow("win",WINDOW_NORMAL);
	
	for(i=0;i<img.rows;i++)
		for(j=0;j<img.cols;j++)
		result.at<uchar>(i,j)=(img.at<Vec3b>(i,j)[0]+img.at<Vec3b>(i,j)[1]+img.at<Vec3b>(i,j)[2])/3;
	
	printf("method 1\n");
	
	imshow("win",result);
	waitKey(0);
	
	for(i=0;i<img.rows;i++)
		for(j=0;j<img.cols;j++)
			result.at<uchar>(i,j)=(maxi(img.at<Vec3b>(i,j)[0],img.at<Vec3b>(i,j)[1],img.at<Vec3b>(i,j)[2])+minu(img.at<Vec3b>(i,j)[0],img.at<Vec3b>(i,j)[1],img.at<Vec3b>(i,j)[2]))/2;

	printf("method 2\n");
	imshow("win",result);
	waitKey(0);
	
	
	for(i=0;i<img.rows;i++)
		for(j=0;j<img.cols;j++)
			result.at<uchar>(i,j)=(0.21*img.at<Vec3b>(i,j)[0]+0.72*img.at<Vec3b>(i,j)[1]+0.07*img.at<Vec3b>(i,j)[2]);
	
	printf("method 3\n");
	imshow("win",result);
	waitKey(0);

result=imread("lenna.jpg",0);
imshow("win",result);
waitKey(0);
	
return 0;
}

int maxi(int a,int b,int c)
{

	if(a>b&&a>c) return a;
	if(b>a&&b>c) return b;
return c;

}

int minu(int a,int b,int c)
{
	if(a<b&&a<c) return a;
	if(b<a&&b<c) return b;
return c;

}
