#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	
	int i,j;
	
	Mat img=imread("lenna.jpg",1);
	Mat result(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));

	namedWindow("win",WINDOW_NORMAL);
	
	for(i=0;i<img.rows;i++)
	for(j=0;j<img.cols;j++)
	{
	
		if(j<(img.cols)/2) result.at<Vec3b>(i,j)=img.at<Vec3b>(i,j);
		else result.at<Vec3b>(i,j)=img.at<Vec3b>(i,img.cols-j);

	}

	imshow("win",result);
	waitKey(0);

return 0;
}
