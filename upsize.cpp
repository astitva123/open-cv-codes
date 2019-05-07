#include<stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main()
{

int i,j;

Mat img=imread("lenna.jpg",1);
Mat result(3*img.rows,3*img.cols,CV_8UC3,Scalar(0,0,0));

namedWindow("wino",WINDOW_AUTOSIZE);
namedWindow("winR",WINDOW_AUTOSIZE);

for(i=0;i<3*img.rows;i++)
{

for(j=0;j<3*img.cols;j++)
{

result.at<Vec3b>(i,j)=img.at<Vec3b>(i/3,j/3);

}

}

imshow("wino",img);
imshow("winr",result);

waitKey(0);

return 0;
}
