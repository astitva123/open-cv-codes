#include<stdio.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<math.h>

using namespace std;
using namespace cv;

Mat img=imread("rubik.jpg",0);


void call(int ,void *);
float a1(int,int);
float b(int,int);
int m(int x,int y,Mat);
int n(int x, int y,Mat);

int main()
{

	int i,j,a=212;
	namedWindow("win",WINDOW_NORMAL);
	namedWindow("win1",WINDOW_NORMAL);
	namedWindow("win2",WINDOW_NORMAL);

	createTrackbar("threshold","win",&a,255,call,NULL);
        

	waitKey(0);

	return 0;
}

void call(int a,void* t)
{
	Mat result(img.rows-1,img.cols-1,CV_8UC1,Scalar(0));
	Mat result1(img.rows-1,img.cols-1,CV_8UC1,Scalar(0));
	Mat result2(img.rows-1,img.cols-1,CV_8UC1,Scalar(0));

	int i,j,gx,gy;
	
	for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
	
			gx=a1(i,j);
			gy=b(i,j);
	
			if(sqrt(gx*gx+gy*gy)>(float)a) result.at<uchar>(i,j)=255; 

		}
	}

	imshow("win",result);

	for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			result1.at<uchar>(i,j)=m(i,j,result);
		}
	}

	imshow("win1",result1);

	for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			result2.at<uchar>(i,j)=n(i,j,result1);
		}
	}

	imshow("win2",result2);

}

float a1(int x,int y)
{

	int i,j;
	float gx=0;
	
	for(i=-1;i<3;i++)
	{
		for(j=-1;j<3;j++)
		{
			if(j==-1) gx-=img.at<uchar>(x+i,y+j);
			if(j==1)  gx+=img.at<uchar>(x+i,y+j);

		}
	}

return gx/6;

}

float b(int x,int y)
{

	int i,j;
	float gy=0;
	
	for(i=-1;i<3;i++)
	{
		for(j=-1;j<3;j++)
		{
			if(i==-1) gy-=img.at<uchar>(x+i,y+j);
			if(i==1)  gy+=img.at<uchar>(x+i,y+j);
		
		}
	}

}

int m(int x,int y,Mat result)
{

	int i,j;
	
	for(i=-1;i<3;i++)
	for(j=-1;j<3;j++)
	{
		
		if (result.at<uchar>(x+i,y+j)==255) return 255;
	}

return 0;

}

int n(int x, int y,Mat result)
{

	int i,j;
	
	for(i=-1;i<3;i++)
	for(j=-1;j<3;j++)
	{
		
		if (result.at<uchar>(x+i,y+j)==0) return 0;
	}

return 255;

}









