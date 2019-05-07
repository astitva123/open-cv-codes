#include "opencv2/highgui/highgui.hpp"

#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/core/core.hpp"

#include <iostream>

using namespace cv;

using namespace std;

 

int main()

{

 int i,j;

 Mat img1(1,1,CV_8UC3,Scalar(0,0,0));

 VideoCapture vid(0);

 Mat frame;

 while(1)

 {

  vid>>frame;

  for(i=0;i<=frame.cols;i++)

  {

   for(j=0;j<=frame.rows;j++)

   {

    img1.at<Vec3b>(0,0)=frame.at<Vec3b>(j,i);

    frame.at<Vec3b>(j,frame.cols-i-1)=img1.at<Vec3b>(0,0);

   }

  }

  imshow("win",frame);

  waitKey(1);

 }

 return 0;

}

