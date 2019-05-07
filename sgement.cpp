#include<stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat img=imread("ps2_shot3.png",1);
Mat result;//(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));


float max(float,float,float);
float min(float,float,float);

void callback(int,void*);

int rlow=127,rhigh=127,glow=127,ghigh=127,blow=127,bhigh=127;


int main()
{

int b=255,i,j,r1,g1,b1;

cvtColor(img,result,CV_RGB2HSV);
Mat fres(result.rows,result.cols,CV_8UC1,Scalar(0));

namedWindow("win",WINDOW_NORMAL);

createTrackbar("maxred","win",&rhigh,b,callback,&fres);
createTrackbar("maxgreen","win",&ghigh,b,callback,&fres);
createTrackbar("maxblue","win",&bhigh,b,callback,&fres);
createTrackbar("minred","win",&rlow,b,callback,&fres);
createTrackbar("mingreen","win",&glow,b,callback,&fres);
createTrackbar("minblue","win",&blow,b,callback,&fres);

waitKey(0);

return 0;
}

void callback(int a,void*t)
{

																																					
Mat*t1=(Mat*)t;

int i,j;

for(i=0;i<img.rows;i++)
{
for(j=0;j<img.cols;j++)
{
if(result.at<Vec3b>(i,j)[2]>=rlow&&result.at<Vec3b>(i,j)[2]<=rhigh&&result.at<Vec3b>(i,j)[1]>=glow&&result.at<Vec3b>(i,j)[1]<=ghigh&&result.at<Vec3b>(i,j)[0]>=blow&&result.at<Vec3b>(i,j)[0]<=bhigh) (*t1).at<uchar>(i,j)={255};
else (*t1).at<uchar>(i,j)={0};
}

}

imshow("win",*t1);

}

float max(float a,float b, float c)
{
	if(a>b&&a>c) return a;
	if(b>c&&c>a) return b;
	return c;
}

float min(float a,float b, float c)
{
	if(a<b&&a<c) return a;
	if(b<c&&c<a) return b;
	return c;
}







