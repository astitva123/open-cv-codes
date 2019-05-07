#include<stdio.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;
int main()
{

Mat img=imread("j.png",0);
namedWindow("win",WINDOW_NORMAL);
imshow("win",img);

waitKey(0);

return 0;
}
