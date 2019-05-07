#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<bits/stdc++.h>

using namespace std;
using namespace cv;

void dfs(int,int);
Mat img=imread("dfs_path.jpg",0);
Mat result(img.rows/10,img.cols/10,CV_8UC1,Scalar(255));
Mat imgr(img.rows/5,img.cols/5,CV_8UC1,Scalar(0));
Size x;


int main()
{

        
resize(img,imgr,x,0.1,0.1,INTER_LINEAR);
		dfs(0,0);


		namedWindow("win",WINDOW_NORMAL);
		imshow("win",result);

		waitKey(0);

		return 0;
}

void dfs(int x,int y)
{
 	result.at<uchar>(x,y)=0;
 	if(x%5==0&&y%5==0) {imshow("win",result);
 	waitKey(0);}

		if(x-1!=-1&&result.at<uchar>(x-1,y)>127&&imgr.at<uchar>(x-1,y)>127) dfs(x-1,y);
	
    
	
	if(y+1!=img.cols&&result.at<uchar>(x,y+1)>127&&imgr.at<uchar>(x,y+1)>127) dfs(x,y+1);
	
	if(y-1!=-1&&result.at<uchar>(x,y-1)>127&&imgr.at<uchar>(x,y-1)>127) dfs(x,y-1);
	if(x+1!=img.rows&&result.at<uchar>(x+1,y)>127&&imgr.at<uchar>(x+1,y)>127) dfs(x+1,y);


}