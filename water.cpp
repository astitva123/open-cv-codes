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
Mat result(2*img.rows,img.cols,CV_8UC3,Scalar(0,0,0));

namedWindow("win",WINDOW_NORMAL);

for(i=0;i<2*img.rows;i++)
for(j=0;j<img.cols;j++)
{
if(i<img.rows) result.at<Vec3b>(i,j)=img.at<Vec3b>(i,j);
else result.at<Vec3b>(i,j)=img.at<Vec3b>(2*img.rows-i,j);
}

imshow("win",result);

waitKey(0);


return 0;
}
