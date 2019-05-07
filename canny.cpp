#include<stdio.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<math.h>

using namespace std;
using namespace cv;

Mat img=imread("ps3_2.jpg",0);
Mat result(img.rows,img.cols,CV_8UC1,Scalar(0));
void call(int a,void* t);


int main()
{
int a=20;

namedWindow("win",WINDOW_NORMAL);

createTrackbar("L","win",&a,255,call,NULL);

waitKey(0);

return 0;
}


void call(int a,void* t)
{

printf("\nhogaya bhenchod!\n");
Canny(img,result,a,3*a,3);
imshow("win",result);

}
