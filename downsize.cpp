#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"

using namespace std;
using namespace cv;

int  main()
{

Mat img=imread("lenna.jpg",1);
Mat result(img.rows/3,img.cols/3,CV_8UC3,Scalar(0,0,0));

int i,j;

namedWindow("original",WINDOW_AUTOSIZE);
namedWindow("downsized",WINDOW_AUTOSIZE);

for(i=0;i<img.rows;i++)
for(j=0;j<img.cols;j++)
{
result.at<Vec3b>(i/3,j/3)[0]+=(img.at<Vec3b>(i,j)[0])/9;
result.at<Vec3b>(i/3,j/3)[1]+=(img.at<Vec3b>(i,j)[1])/9;
result.at<Vec3b>(i/3,j/3)[2]+=(img.at<Vec3b>(i,j)[2])/9;
}
imshow("downsized",result);
imshow("original",img);

waitKey(0);

return 0;
}
