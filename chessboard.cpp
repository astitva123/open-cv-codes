#include<stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main()
{

	int i,j;
	
	Mat img(8,8,CV_8UC1,Scalar(0));
	
	namedWindow("win",WINDOW_NORMAL);
	
	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{

			if(i%2==j%2) img.at<uchar>(i,j)=0;
			else img.at<uchar>(i,j)=255;
	
		}

	}

	imshow("win",img);
	
	waitKey(0);

return 0;
}


