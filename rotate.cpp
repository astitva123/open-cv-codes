#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<math.h>

using namespace std;
using namespace cv;

int main()
{

int i,j,x,y,x1,y1;
float theta;

printf("enter the angle of rotation: ");
scanf("%f",&theta);

Mat img=imread("lenna.jpg",1);
Mat result(2*img.rows,2*img.cols,CV_8UC3,Scalar(0,0,0));

x=img.cols;
y=img.rows;

namedWindow("original",WINDOW_AUTOSIZE);
namedWindow("rotated",WINDOW_AUTOSIZE);

for(i=0;i<img.rows;i++)
{
for(j=0;j<img.cols;j++)
{
x1=((j-x)*cos(theta)-(img.rows-i-1-y)*sin(theta));
y1=((img.rows-i-1-y)*cos(theta)+(j-x)*sin(theta));

result.at<Vec3b>(y+y1,x+x1)={img.at<Vec3b>(img.rows-i-1-y,j-x)[0],img.at<Vec3b>(img.rows-i-1-y,j-x)[1],img.at<Vec3b>(img.rows-i-1-y,j-x)[2]};
}
}

imshow("original",img);
imshow("rotated",result);

waitKey(0);

return 0;
}
