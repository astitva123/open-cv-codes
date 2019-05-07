#include<stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

int fd;

int m(int,int,Mat);
int n(int,int,Mat);
void direction(Mat,int,int);
void LED_CHECK();
void IMAGE_SEGMENT();

int hue,sat,val,cur_contours,size,line_count=0;

Mat img1;
Mat img2;



void settings(const char *abc)
{
      fd = open(abc,O_RDWR | O_NOCTTY); /* ttyUSB0 is the FT232 based USB2SERIAL Converter   */
      usleep(3500000);
                                    /* O_RDWR Read/Write access to serial port           */
                                    /* O_NOCTTY - No terminal will control the process   */
                                    /* O_NDELAY -Non Blocking Mode,Does not care about-  */
                                    /* -the status of DCD line,Open() returns immediatly */                                        
                                    
            if(fd == -1)                        /* Error Checking */
                   printf("\n  Error! in Opening  ");
            else
                   printf("\n  Opened Successfully ");
       struct termios toptions;         /* get current serial port settings */
       tcgetattr(fd, &toptions);        /* set 9600 baud both ways */
       cfsetispeed(&toptions, B9600);
       cfsetospeed(&toptions, B9600);   /* 8 bits, no parity, no stop bits */
       toptions.c_cflag &= ~PARENB;
       toptions.c_cflag &= ~CSTOPB;
       toptions.c_cflag &= ~CSIZE;
       toptions.c_cflag |= CS8;         /* Canonical mode */
       toptions.c_lflag |= ICANON;       /* commit the serial port settings */
       tcsetattr(fd, TCSANOW, &toptions);
}

void sendCommand(const char a)
{
	char *abc=&a;
   write(fd, abc, 1);
}

/*void SEND(int A)
{
	A=A+1000;
	char d;
	while(A>0)
	{	
		d='0'+(A%10);
		sendCommand(&d);
		A=A/10;
	}
	d="\n";
	sendCommand(&d);
}*/


int main(int argc,char** argv)
{
	settings(argv[1]);
	VideoCapture vid(0);
	printf("enter hue,sat,val\n");
	scanf("%d %d %d",&hue,&sat,&val)

	while(1)
	{
		vid>>img1;
		vid>>img2; 
		//IMAGE_SEGMENT();
		direction(img1,a,b);
		//LED_CHECK();
		line_count++;
	}


	return 0;
}


/*int m(int x,int y,Mat img)
{

	int i,j;
	
	for(i=-1;i<3;i++)
	for(j=-1;j<3;j++)
	{
		
		if (img.at<uchar>(x+i,y+j)>=127) return 255;
	}

return 0;

}

int n(int x, int y,Mat result)
{

	int i,j;
	
	for(i=-1;i<3;i++)
	for(j=-1;j<3;j++)
	{
		
		if (result.at<uchar>(x+i,y+j)<127) return 0;
	}

return 255;

}*/

void direction(Mat img,int a,int b)
{
	int i,j,k,countl=0,countr=0,flag=0;

	Mat result(img.rows,img.cols,CV_8UC1,Scalar(0));
	Mat fres(img.rows,img.cols,CV_8UC1,Scalar(0));

	namedWindow("win",WINDOW_NORMAL);

	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
			if(img.at<Vec3b>(i,j)[0]>200&&img.at<Vec3b>(i,j)[1]>200&&img.at<Vec3b>(i,j)[2]>200){ fres.at<uchar>(i,j)=255;}
			else{ fres.at<uchar>(i,j)=0;}
		}
	}

	/*Canny(img,result,a,3*a,3);

	for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			fres.at<uchar>(i,j)=m(i,j,result);
		}
	}*/


	/*for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			result.at<uchar>(i,j)=n(i,j,fres);
		}
	}*/


	/*for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			fres.at<uchar>(i,j)=n(i,j,result);
		}
	}*/

	for(i=img.cols/2;i<img.cols;i++)
	{
		for(j=img.rows-1;j>=0;j--)
		{
			if(fres.at<uchar>(j,i)==255) countr++;
			else break;
		}
	}

	for(i=img.cols/2;i>=0;i--)
	{
		for(j=img.rows-1;j>=0;j--)
		{
			if(fres.at<uchar>(j,i)==255) countl++;
			else break;    
		}
	}

	imshow("win",result);

	if(countl-countr>t) {
		printf("left\n");
		sendCommand(A);
	}
	else if(countr-countl>t) {
		printf("right\n");
		sendCommand(D);
	}
	else{
printf("straight\n");
		sendCommand(W);
	}

	waitKey(20);

}

void LED_CHECK()
{
	vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;

	Canny( img2, img2, thresh, thresh*2, 3 );
  
  	findContours( img2 , contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );


  	int size=contours.size();


  	cur_contours=size;

	if(line_count<=50)
	{
		prev_contours=size;
		
	}

	if( prev_contours-cur_contours > 0 )
	{
		SEND(1000);
	}
	else
	{
		//LED off
	}

	prev_contours=cur_contours;

}

void IMAGE_SEGMENT()
{
	int i,j;

	Mat hsv(img2.rows,img2.cols,CV_8UC3,Scalar(0,0,0));//cvCreateImage(cvSize(cols,rows),IPL_DEPTH_8U,3); //The hsv intermediate is initialized
  	cvtColor(img2,hsv,COLOR_BGR2HSV);
	for(int i=0;i<img2.cols;i++)
	{
		for(int j=0;j<img2.rows;j++)
		{
			Vec3b HSV=hsv.at<Vec3b>(i,j);
			int H=HSV.val[0]; //hue
			int S=HSV.val[1]; //saturation
			int V=HSV.val[2]; //value
			//if((IMGDATA(hsv,i,j,0)> hue-TOLH && IMGDATA(hsv,i,j,1)< hue+TOLH) && (IMGDATA(hsv,i,j,1)>sat-TOLS && IMGDATA(hsv,i,j,1)<sat+TOLS) && (IMGDATA(hsv,i,j,2)>val-TOLV && IMGDATA(hsv,i,j,2)<val+TOLV) )
			if( H> hue-5 && H< hue+5 && S>sat-100 && S<sat+100 && V>val-150 && V<val+150 )
        		img2.at<uchar>(j,i)=255;
      		else
        		img2.at<uchar>(j,i)=0;
		}
	}
}