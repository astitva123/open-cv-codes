#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<bits/stdc++.h>

using namespace std;
using namespace cv;

void bfs(int,int);
Mat img=imread("images.png",0);
Mat result(img.rows,img.cols,CV_8UC1,Scalar(0));

int c=0;

typedef struct
{
	int x,y;
}b;

queue <b> bf;

int main()
{

	int i,j;
	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
			if(img.at<uchar>(i,j)>127) bfs(i,j);
		}
	}


    printf("\n %d\n",c);
    waitKey(0);
	return 0;
}

void bfs(int x,int y)
{
	b pt,npt;

	pt.x=x;
	pt.y=y;

	bf.push(pt);
	

	while(!bf.empty())
	{
		pt=bf.front();
		if(pt.x+1<img.rows&&img.at<uchar>(pt.x+1,pt.y)>127) 
			{
			    npt.x=pt.x+1;
			    npt.y=pt.y;	
				bf.push(npt);
				img.at<uchar>(npt.x,npt.y)=0;

			}

		if(pt.x-1>0&&img.at<uchar>(pt.x-1,pt.y)>127) 
			{
			    npt.x=pt.x-1;
			    npt.y=pt.y;	
				bf.push(npt);
				img.at<uchar>(npt.x,npt.y)=0;

			}	
	    if(pt.y+1<img.cols&&img.at<uchar>(pt.x,pt.y+1)>127) 
			{
			    npt.x=pt.x;
			    npt.y=pt.y+1;	
				bf.push(npt);
				img.at<uchar>(npt.x,npt.y)=0;

			}	
	    if(pt.y-1>0&&img.at<uchar>(pt.x,pt.y-1)>127) 
			{
			    npt.x=pt.x;
			    npt.y=pt.y-1;	
				bf.push(npt);
				img.at<uchar>(npt.x,npt.y)=0;

			}	
			
	
        
        printf("\n%d  %d\n",pt.x,pt.y);
        bf.pop();
        if(pt.x%5==0&&pt.y%5==0)
        	{imshow("win",img);
        waitKey(0);}

	}
	c++;
}