#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<bits/stdc++.h>

using namespace std;
using namespace cv;

Mat img;

int m(int x,int y,Mat);
int n(int x,int y,Mat);

int main()
{
	  vector <vector<Point> > contours;
  	  vector <Vec4i> hierarchy;
  	  Moments m1;


	namedWindow("win",WINDOW_NORMAL);

	int i,j,cx,cy;

	VideoCapture vid(0);

	while(1)
	{	

	vid>>img;
	Mat result(img.rows,img.cols,CV_8UC1,Scalar(0));
    Mat fres(img.rows,img.cols,CV_8UC1,Scalar(0));
		

	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
			if(img.at<Vec3b>(i,j)[2]>=130&&img.at<Vec3b>(i,j)[2]<=255&&img.at<Vec3b>(i,j)[1]>=200&&img.at<Vec3b>(i,j)[1]<=255&&img.at<Vec3b>(i,j)[0]>=20&&img.at<Vec3b>(i,j)[0]<=120) result.at<uchar>(i,j)=255;
			else result.at<uchar>(i,j)=0;
		}

	}

	for(i=1;i<result.rows-1;i++)
	{
		for(j=1;j<result.cols-1;j++)
		{
			fres.at<uchar>(i,j)=n(i,j,result);
		}
	}
	for(i=1;i<fres.rows-1;i++)
	{
		for(j=1;j<fres.cols-1;j++)
		{
			result.at<uchar>(i,j)=n(i,j,fres);
		}
	}


	for(i=1;i<result.rows-1;i++)
	{
		for(j=1;j<result.cols-1;j++)
		{
			fres.at<uchar>(i,j)=m(i,j,result);
		}
	}
	

	Canny(fres,result,50,3*50,3);

	for(i=1;i<result.rows-1;i++)
	{
		for(j=1;j<result.cols-1;j++)
		{
			fres.at<uchar>(i,j)=m(i,j,result);
		}
	}

		for(i=1;i<fres.rows-1;i++)
	{
		for(j=1;j<fres.cols-1;j++)
		{
			result.at<uchar>(i,j)=n(i,j,fres);
		}
	}

	findContours(fres,contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	Mat contour(result.rows,result.cols,CV_8UC1,Scalar(0));
	
	double area;

	for(i=0;i<contours.size();i++)
	{	
		area=contourArea(contours[i]);

    	if(area>1000)
    	{
    		
    	drawContours(contour,contours,-1, 255, 2, 8);
    		m1=moments(contours[i]);
    		break;
    	}
    	
    } 

    imshow("win",contour);
    waitKey(40);

    cx = (int)(m1.m10/m1.m00);
	cy = (int)(m1.m01/m1.m00);
    	if(area>36722)
    	{	
    		i=-127;
    		if(cx-contour.cols/2>127||cx-contour.cols/2<-127)
    			j=127;
    		else j=abs(cx-contour.cols/2);


    	}
		else 
		{
			i=127;
			if(cx-contour.cols/2>127||cx-contour.cols/2<-127)
    			j=127;
    		else j=abs(cx-contour.cols/2);

		}    	
printf("\n %d  %d \n",i,j);
	}

	//imshow("win",contour);
	//waitKey(0);

	return 0;
}

int m(int x,int y,Mat r)
{

	int i,j;
	
	for(i=-1;i<3;i++)
	for(j=-1;j<3;j++)
	{
		
		if (r.at<uchar>(x+i,y+j)==255) return 255;
	}

return 0;

}

int n(int x, int y,Mat r)
{

	int i,j;
	
	for(i=-1;i<3;i++)
	for(j=-1;j<3;j++)
	{
		
		if (r.at<uchar>(x+i,y+j)==0) return 0;
	}

return 255;

}
