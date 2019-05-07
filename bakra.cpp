#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

Mat img(360,360,CV_8UC1,Scalar(0));

int main()
{

	namedWindow("win",WINDOW_NORMAL);
	img.at<uchar>(140,233)=255;

	imshow("win",img);

	waitKey(0);
	return 0;
}