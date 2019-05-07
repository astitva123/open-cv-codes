#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<math.h>

using namespace std;
using namespace cv;

Mat img=imread("j.png",0);
Mat result(img.rows,img.cols,CV_8UC1,Scalar(0));
Mat fres(img.rows,img.cols,CV_8UC1,Scalar(0));

int m(int,int);
int n(int,int);

int main()
{

	int i,j;

	namedWindow("win",WINDOW_NORMAL);
	namedWindow("final",WINDOW_NORMAL);
	
	for(i=0;i<img.rows;i++)
	{
	
		for(j=0;j<img.cols;j++)
		{
			if(img.at<uchar>(i,j)<150) img.at<uchar>(i,j)=0;
			else img.at<uchar>(i,j)=255;
	
		}
		
	}

	for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			result.at<uchar>(i,j)=m(i,j);
		}
	}

	imshow("win",result);

	for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			fres.at<uchar>(i,j)=n(i,j);
		}
	}
	
	imshow("final",fres);

	waitKey(0);

return 0;
}

	int m(int x,int y)
	{

		int i,j;
		
		for(i=-1;i<3;i++)
		for(j=-1;j<3;j++)
		{
			
			if (img.at<uchar>(x+i,y+j)==255) return 255;
		}

	return 0;

	}

	int n(int x, int y)
	{

		int i,j;
		
		for(i=-1;i<3;i++)
		for(j=-1;j<3;j++)
		{
			
			if (result.at<uchar>(x+i,y+j)==0) return 0;
		}

	return 255;

	}


