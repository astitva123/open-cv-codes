#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include  "opencv2/core/core.hpp"
#include<stdio.h>

using namespace cv;
using namespace std;

int main()
{

	int i,j;
	
	Mat img(1080,1080,CV_8UC3,Scalar(0,0,0));
	
	namedWindow("win",WINDOW_NORMAL);
	
	for(i=0;i<img.rows;i++)
	{	
		for(j=0;j<img.cols;j++)
		{
	
			if(i<=img.cols-j) img.at<Vec3b>(i,j)={0,i/6,i/5};
			else img.at<Vec3b>(i,j)={i/5,i/6,0};

		}

	}

	imshow("win",img);


	waitKey(0);

return 0;
}
