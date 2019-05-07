#include<stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

void callback(int,void*);

int main()
{

Mat img1=imread("download.jpeg",1);
Mat img2=imread("download1.jpeg",1);
Mat result(img1.rows,img1.cols,CV_8UC3,Scalar(0,0,0));
int a=50;
namedWindow("win",WINDOW_AUTOSIZE);

createTaskbar("morph","win",&a,100,callback,NULL);

return 0;
}

void callback(int a,void *t)
{

int i,j;

for(i=0;i<result.cols)

}
