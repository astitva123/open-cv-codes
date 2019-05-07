#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<bits/stdc++.h>
#include <math.h>
#include <stdlib.h>

using namespace std;
using namespace cv;


Mat img=imread("sq.png",0);
int a=sqrt(pow(img.rows,2)+pow(img.cols,2));
Mat result ((int)a,361,CV_8UC1,Scalar(0));

int main()
{
	namedWindow("win",WINDOW_NORMAL);
	int i,j,theta,r;

	for(i=0;i<img.rows;i++)
	{ 
		for(j=0;j<img.cols;j++)
		
	     {   

			if(img.at<uchar>(i,j)>90)
			{
				for(theta=0;theta<181;theta++)
				{
					r=(int)(i*cos(theta*3.14159265/180)+j*sin(theta*3.14159265/180));
					if(r>0)
					if(result.at<uchar>(r,theta)!=255) result.at<uchar>(r,theta)=result.at<uchar>(r,theta)+4;
				}
			}
		}
	}

	imshow("win",result);
	waitKey(0);


	return 0;
}