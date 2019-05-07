#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"

using namespace std;
using namespace cv;

void callback(int a,void*t);
Mat img=imread("ps3_3.jpg",0);
Mat result(img.rows,img.cols,CV_8UC1,Scalar(0));

int main()
{

	int a=127,b=255;
	
	namedWindow("win",WINDOW_NORMAL);
	
	createTrackbar("anthony","win",&a,b,callback,NULL);
	
	waitKey(0);
return 0;
}

void callback(int a,void *t)
{

	int i,j;
	
	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
			if(img.at<uchar>(i,j)<a){ result.at<uchar>(i,j)=0;}
			else{ result.at<uchar>(i,j)=255;}
		}
	}
	
	imshow("win",result);

}
