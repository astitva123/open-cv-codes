#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"

using namespace std;
using namespace cv;

void callback(int a,void*t);
Mat img=imread("lenna.jpg",1);
Mat result(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));

int rhigh=127,bhigh=127,ghigh=127;

int main()
{

	int b=255;
	
	namedWindow("win",WINDOW_NORMAL);
	
	createTrackbar("ramar","win",&rhigh,b,callback,NULL);
	createTrackbar("gakhbar","win",&ghigh,b,callback,NULL);
	createTrackbar("banthony","win",&bhigh,b,callback,NULL);
	
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
			if(img.at<Vec3b>(i,j)[2]<rhigh){ result.at<Vec3b>(i,j)[2]=0;}
			else{ result.at<Vec3b>(i,j)[2]=255;}
			if(img.at<Vec3b>(i,j)[1]<ghigh){ result.at<Vec3b>(i,j)[1]=0;}
			else{ result.at<Vec3b>(i,j)[1]=255;}
			if(img.at<Vec3b>(i,j)[0]<bhigh){ result.at<Vec3b>(i,j)[0]=0;}
			else{ result.at<Vec3b>(i,j)[0]=255;}
		}
	}
	
	imshow("win",result);

}

