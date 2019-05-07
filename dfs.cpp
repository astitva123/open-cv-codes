#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<bits/stdc++.h>

using namespace std;
using namespace cv;

void dfs(int,int);
Mat img=imread("index.png",0);
Mat result=imread("index.png",0);

int main()
{
		dfs(20,23);

		return 0;
}

void dfs(int x,int y)
{
 	result.at<uchar>(x,y)=0;
    printf("\n%d %d \n",x,y);

    if(x%5==0&&y%5==0) 
{
    	imshow("win",result);
waitKey(0);}
	if(x==img.rows-1&&y==img.cols-1)
	{
		namedWindow("win",WINDOW_NORMAL);
		imshow("win",result);
		waitKey(0);
		exit(0);
	}

	
	if(y+1!=img.cols&&result.at<uchar>(x,y+1)>127) dfs(x,y+1);
	if(x+1!=img.rows&&result.at<uchar>(x+1,y)>127) dfs(x+1,y);
	if(x-1!=-1&&result.at<uchar>(x-1,y)>127) dfs(x-1,y);
	if(y-1!=-1&&result.at<uchar>(x,y-1)>127) dfs(x,y-1);



}