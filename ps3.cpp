#include<stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

int m(int,int,Mat);
int n(int,int,Mat);
void direction(Mat,int,int);

int main()
{
    
	Mat img=imread("ps3_1.jpg",0);
	direction(img,106,36);
	img=imread("ps3_2.jpg",0);
	direction(img,255,48);
	img=imread("ps3_3.jpg",0);
	direction(img,73,48);

	return 0;
}


int m(int x,int y,Mat img)
{

	int i,j;
	
	for(i=-1;i<3;i++)
	for(j=-1;j<3;j++)
	{
		
		if (img.at<uchar>(x+i,y+j)>=127) return 255;
	}

return 0;

}

int n(int x, int y,Mat result)
{

	int i,j;
	
	for(i=-1;i<3;i++)
	for(j=-1;j<3;j++)
	{
		
		if (result.at<uchar>(x+i,y+j)<127) return 0;
	}

return 255;

}

void direction(Mat img,int a,int b)
{
	int i,j,k,countl=0,countr=0,flag=0;

	Mat result(img.rows,img.cols,CV_8UC1,Scalar(0));
	Mat fres(img.rows,img.cols,CV_8UC1,Scalar(0));

	namedWindow("win",WINDOW_NORMAL);

	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
			if(img.at<uchar>(i,j)<b){ fres.at<uchar>(i,j)=0;}
			else{ fres.at<uchar>(i,j)=255;}
		}
	}

	/*Canny(img,result,a,3*a,3);

	for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			fres.at<uchar>(i,j)=m(i,j,result);
		}
	}*/


	/*for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			result.at<uchar>(i,j)=n(i,j,fres);
		}
	}*/


	/*for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			fres.at<uchar>(i,j)=n(i,j,result);
		}
	}*/

	for(i=img.cols/2;i<img.cols;i++)
	{
		for(j=img.rows-1;j>=0;j--)
		{
			if(fres.at<uchar>(j,i)==255) countr++;
			else break;
		}
	}

	for(i=img.cols/2;i>=0;i--)
	{
		for(j=img.rows-1;j>=0;j--)
		{
			if(fres.at<uchar>(j,i)==255) countl++;
			else break;    
		}
	}

	imshow("win",result);

	if(countl>countr) printf("left");
	if(countl<countr) printf("right");
	if(countl==countr) printf("straight");

	waitKey(0);

}
