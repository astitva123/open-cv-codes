#include<stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace cv;

Mat img=imread("dfs_path.jpg",0);
Mat result=imread("dfs_path.jpg",0);


void df(int,int);

int main()
{
namedWindow("win",WINDOW_NORMAL);
df(0,0);

return 0;
}

void df(int x,int y)
{
	result.at<uchar>(x,y)=0;
	if(x==img.rows-1&&y==img.cols-1)
	{
		imshow("win",result);
		waitKey(0);
		exit(0);
	}

	int i,j;
	for(i=-1;i<3;i++)
	{
		for(j=-1;j<3;j++)
		{
			if((x+i)>=0&&(x+i)<img.cols&&(y+j)>=0&&(y+j)<img.cols)
				{ 
					if(img.at<uchar>(x+i,y+j)>=127) df(x+i,y+j);
				}	
		}
	}

}
