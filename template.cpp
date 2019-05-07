#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<bits/stdc++.h>

using namespace std;
using namespace cv;

Mat img=imread("coins.jpeg",1);
Mat templ=imread("temp.jpeg",1);

int match_method;

void MatchingMethod( int, void* );

int main()
{
	
 namedWindow( "image_window", CV_WINDOW_NORMAL );
  namedWindow( "result_window", CV_WINDOW_NORMAL );

char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar( trackbar_label, " image_window", &match_method,5, MatchingMethod );


  waitKey(0);
	return 0;
}

void MatchingMethod( int a, void* b )
{

Mat img_display;
Mat result;
  img.copyTo( img_display );

   int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_rows, result_cols, CV_32FC1 );

   matchTemplate( img, templ, result, a );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

  imshow( "image_window", img_display );
  imshow( "result_window", result );


}