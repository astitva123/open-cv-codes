#include<stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<math.h>

using namespace std;
using namespace cv;

void histogram(int [],Mat img);

Mat imgd=imread("darkimage.PNG",0);
//Mat imgl=imread("lightimage.PNG",0);
Mat imghc=imread("highcontrast.PNG",0);
//Mat imglc=imread("lowcontrast.PNG",0);

Mat dark(imgd.rows*imgd.rows,2560*6,CV_8UC1,Scalar(255));
//Mat light(imgd.rows*imgd.rows,2560*6,CV_8UC1,Scalar(255));
Mat highc(imgd.rows*imgd.rows,2560*6,CV_8UC1,Scalar(255));
//Mat lowc(imgd.rows*imgd.rows,2560*6,CV_8UC1,Scalar(255));

int arr[256]={0};

void a(int arr[],Mat);

int main()
{

int i;	
	
//	namedWindow("darkim",WINDOW_NORMAL);
//	namedWindow("lightim",WINDOW_NORMAL);
	namedWindow("highcim",WINDOW_NORMAL);
//	namedWindow("lowcim",WINDOW_NORMAL);

//	a(arr,imgd);
//	histogram(arr,dark);
	//for(i=0;i<256;i++,arr[i]=0);


//	a(arr,imgl);
//	histogram(arr,light);
//	for(i=0;i<256;i++,arr[i]=0);	
	
	a(arr,imghc);
	histogram(arr,highc);
//	for(i=0;i<256;i++,arr[i]=0);
	
//	a(arr,imglc);
//	histogram(arr,lowc);
	
//	imshow("darkim",dark);
//	imshow("lightim",light);
	imshow("highcim",highc);
//	imshow("lowcim",lowc);
	
	waitKey(0);

return 0;
}

void histogram(int arr[],Mat result)
{

	int i,j;
	
	for(i=0;i<2560*5;i++)
	{
		for(j=0;j<10*arr[i/50];j++)
		{
	
			result.at<uchar>(result.rows-j-1,i)={0};
	
		}
	}



}

void a(int arr[],Mat img)
{

	int i,j;

	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
	
			(arr[img.at<uchar>(i,j)])++; 

	
		}
	}


}



















