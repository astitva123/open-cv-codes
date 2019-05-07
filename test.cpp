#include<stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"

using namespace std;
using namespace cv;

int main()
{
int i,j;

Mat img(20,20,CV_8UC3,Scalar(0,0,0));

namedWindow("image",WINDOW_NORMAL);

for(i=0;i<img.rows;i++)
for(j=0;j<img.cols;j++)
{

if(i==1&&j>3&&j<16)

img.at<Vec3b>(i,j)={123,43,234};



if(i>1&&i<17&&j==16-i)

img.at<Vec3b>(i,j)={45,123,243};

}

imshow("image",img);
waitKey(0);

return 0;
}
