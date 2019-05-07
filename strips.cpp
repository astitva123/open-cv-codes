#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"

using namespace cv;
using namespace std;

int main()
{

	int i,j=0;

	Mat img (20,20,CV_8UC3,Scalar(0,0,0));

	namedWindow("image",WINDOW_NORMAL);
	
	for(i=0;i<img.rows;i++)
	{
		if(i%2==0)img.at<Vec3b>(i,j)={23,245,231};
		for(j=0;j<img.cols;j++)
		{
	
			if(j%2==0) img.at<Vec3b>(i,j)={123,234,42};
	
		}
	j=j-1;
	}

	imshow("image",img);

	waitKey(0);

return 0;
}
