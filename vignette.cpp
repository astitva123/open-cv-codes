#include<stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<math.h>

using namespace std;
using namespace cv;

Mat img=imread("lenna.jpg",1);
Mat result(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));

void callback(int,void*);
float dist(int,int);

int main()
{

int i,j,a=img.cols/2;

namedWindow("win",WINDOW_NORMAL);

createTrackbar("radius","win",&a,12000,callback,NULL);

waitKey(0);
return 0;
}

void callback(int a,void *t)
{

float temp;
int i,j;

for(i=0;i<img.rows;i++)
{
for(j=0;j<img.cols;j++)
{
temp=dist(i,j);
if(temp>=a)
{
temp=temp/a;
result.at<Vec3b>(i,j)[0]=(img.at<Vec3b>(i,j)[0]/temp);
result.at<Vec3b>(i,j)[1]=(img.at<Vec3b>(i,j)[1]/temp);
result.at<Vec3b>(i,j)[2]=(img.at<Vec3b>(i,j)[2]/temp);
}
else result.at<Vec3b>(i,j)=img.at<Vec3b>(i,j);
}
}
imshow("win",result);
}

float dist(int x,int y)
{

return (pow(x-img.cols/2,2)+pow(y-img.cols/2,2));
}
