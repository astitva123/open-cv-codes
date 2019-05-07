#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

Mat img=imread("ps2_shot.png",1);
Mat result(img.rows,img.cols,CV_8UC1,Scalar(0));

int main()
{
	int i,j;
	 vector <vector<Point> > contours;
  	  vector <Vec4i> hierarchy;
  	  Moments m1;

  	  namedWindow("win",WINDOW_NORMAL);

	for(i=0;i<img.rows;i++)
{
for(j=0;j<img.cols;j++)
{
if(img.at<Vec3b>(i,j)[2]>=0&&img.at<Vec3b>(i,j)[2]<=85&&img.at<Vec3b>(i,j)[1]>=94&&img.at<Vec3b>(i,j)[1]<=181&&img.at<Vec3b>(i,j)[0]>=103&&img.at<Vec3b>(i,j)[0]<=225) result.at<uchar>(i,j)={255};
else result.at<uchar>(i,j)={0};
}

}


	findContours(result,contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	Mat contour(result.rows,result.cols,CV_8UC1,Scalar(0));
	
	double area;

	for(i=0;i<contours.size();i++)
	{	
		area=contourArea(contours[i]);
        printf("\n%lf\n",area);
    	if(area>1050&&area<1400)
    	{
    		
    	drawContours(contour,contours,-1, 255, 2, 8);
    		m1=moments(contours[i]);
    	//	break;
    	}
    	
    }

    imshow("win",contour); 

    waitKey(0);


	return 0;
}