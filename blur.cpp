#include<stdio.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

Mat img=imread("veg.jpg",0);
Mat mn(img.rows-1,img.cols-1,CV_8UC1,Scalar(0));
Mat md(img.rows-1,img.cols-1,CV_8UC1,Scalar(0));
Mat ga(img.rows-1,img.cols-1,CV_8UC1,Scalar(0));

float meanblur(int,int);
int medianblur(int,int);
float gaussblur(int,int);

int arr[9];

int main()
{

	int i,j;
	
	namedWindow("mean",WINDOW_NORMAL);
	namedWindow("median",WINDOW_NORMAL);
	namedWindow("gauss",WINDOW_NORMAL);
	namedWindow("original",WINDOW_NORMAL);
	
	for(i=0;i<img.rows-1;i++)
	{
		for(j=0;j<img.cols-1;j++)
		{

			mn.at<uchar>(i,j)=meanblur(i,j);
	
		}	
	}

	imshow("mean",mn);

	for(i=0;i<img.rows-1;i++)
	{
		for(j=0;j<img.cols-1;j++)
		{
	
			md.at<uchar>(i,j)=medianblur(i,j);
	
		}
	}
	
	imshow("median",md);

	for(i=0;i<img.rows-1;i++)
	{
		for(j=0;j<img.cols-1;j++)
		{
	
			ga.at<uchar>(i,j)=gaussblur(i,j);
	
		}
	}

	imshow("gauss",ga);
	imshow("original",img);
	
	waitKey(0);

return 0;
}

float meanblur(int x,int y)
{

	int i,j;
	float sum=0;
	
	for(i=-1;i<2;i++)
	{
		for(j=-1;j<2;j++)
		{
			sum+=img.at<uchar>(x+i,y+j);
		
		}
	}
return sum/9;

}

int medianblur(int x,int y)
{
	int i,j,k=0;
	for(i=-1;i<2;i++)
	{
		for(j=-1;j<2;j++)
		{
			arr[k++]=img.at<uchar>(x+i,y+j);
	
		}
	}

	sort(arr,arr+9);

return arr[4];

}

float gaussblur(int x,int y)
{
	int i,j;
	float k=0;

	for(i=-1;i<2;i++)
	{
		for(j=-1;j<2;j++)
		{
			if(i==0&&j==0) k+=(img.at<uchar>(x,y))/4;
			else if((i==0&&j==-1)||(i==-1&&j==0)||(i==1&&j==0)||(i==0&&j==1)) k+=(img.at<uchar>(x+i,y+i))/8;
			     else k+=(img.at<uchar>(x+i,y+i))/16;

		}
	}

return k;

}












