#include<stdio.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<math.h>

using namespace std;
using namespace cv;


vector <vector<Point> > contours;
vector <vector<Point> > contours_t;
vector <Vec4i> hierarchy;
Moments m1;
Moments m2;


//void call(int a,void* t);


int main()
{

	int a=20,count=0,i,led1_t=1,area,led2_t=1,count1=0,count2=0,count_frame=0;

	namedWindow("win",WINDOW_NORMAL);

	/*createTrackbar("L","win",&a,255,call,NULL);*/

  VideoCaptire vid(0);

  while(1)
  {

    //LED

    Mat img,led;
    Mat pathled;

    vid>>img;
    vid>>pathled;
    vid>>led;

    //Mat img=imread("ps3_3.jpg",0);
    Mat result(img.rows,img.cols,CV_8UC1,Scalar(0));
    //Mat led=imread("ps3_3.ppg",1);
    Mat detect(led.rows,led.cols,CV_8UC3,Scalar(0,0,0));
    Mat detect2(detect.rows,detect.cols,CV_8UC1,Scalar(0));
    Mat detect1(img.rows,img.cols,CV_8UC1,Scalar(0));
    Mat detect_t(img.rows,img.cols,CV_8UC1,Scalar(0));
    cvtColor(led,detect,CV_RGB2HSV);
    cvtColor(pathled,pathled,CV_RGB2HSV);


    for(i=0;i<detect.rows;i++)
    {
      for(j=0;j<detect.cols;j++)
      {
        if(detect.at<Vec3b>(i,j)[2]>=40&&detect.at<Vec3b>(i,j)[2]<=243&&detect.at<Vec3b>(i,j)[1]>=105&&detect.at<Vec3b>(i,j)[1]<=255&&detect.at<Vec3b>(i,j)[0]>=0&&detect.at<Vec3b>(i,j)[0]<=45) detect1.at<uchar>(i,j)={255};
        else detect1.at<uchar>(i,j)={0};
      }
    }  
    
    Canny(detect1,detect2,/*variable*/,/*3*variable*/);
    
    findContours(detect2,contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    for(i=0;i<contours.size();i++)
    {
      m1=moments(contours[i]);
      if(contourArea(contour[i])>/*variable*/&&contourArea(contour[i])</*variable*/&&((int)(m1.m10/m1.m00)</*variable*/||(int)(m1.m10/m1.m00)>/*variable*/)&&(int)(m1.m01/m1.m00)</*variable*/) count++;
    }

    if(count) printf("\nblink\n");

    //T junction detection 


    for(i=0;i<pathled.rows;i++)
    {
      for(j=0;j<pathled.cols;j++)
      {
        if(pathled.at<Vec3b>(i,j)[2]>=40&&pathled.at<Vec3b>(i,j)[2]<=243&&pathled.at<Vec3b>(i,j)[1]>=105&&pathled.at<Vec3b>(i,j)[1]<=255&&pathled.at<Vec3b>(i,j)[0]>=0&&pathled.at<Vec3b>(i,j)[0]<=45) detect_t.at<uchar>(i,j)={255};
        else detect_t.at<uchar>(i,j)={0};
      }
    } 

     Canny(detect_t,detect_t,/*variable*/,/*3*variable*/);
     findContours(detect_t,contours_t, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) ); 
     if(contours_t.size()>0) area=contourArea(contours_t[0]);

     
     if(contours_t.size()>=1||area>/*variable*/)
     {
      if (count_frame</*variable*/)
      {
        printf("stop\n");
        for(i=0;i<contours_t.size();i++)
        {
          m2=moments(contourst_t[i]);
        }
      }


      
     }


    //path detection


  Canny(img,result,a,3*a,3);
  Mat fres(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
  float slope;
  double length;
  int l=0,f=0,r=0,count=0,maxleft=0,minleft=img.cols/2,maxright=0,minright=img.cols/2,pos,minlefty,maxlefty,minrighty,mrighty,flag=0;
  
  vector<Vec4i> lines;
    int i;
    count=0;

    HoughLinesP( result, lines, 1, CV_PI/180, 80, 30, 120);
    for(i = 0; i < lines.size(); i++ )
    {
        line( fres, Point(lines[i][0], lines[i][1]),
        Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
        slope=-(float)(lines[i][3]-lines[i][1])/(lines[i][2]-lines[i][0]);
        length=sqrt(pow((double)(lines[i][3]-lines[i][1]),2.0)+pow((double)(lines[i][2]-lines[i][0]),2.0));

        if(length>400&&slope>0.1&&lines[i][0]<minleft) minleft=lines[i][0] ; 
        if(length>400&&slope>0.1&&lines[i][0]>maxleft) maxleft=lines[i][0] ; 
        if(length>400&&slope>0.1&&lines[i][2]<minleft) minleft=lines[i][2] ; 
        if(length>400&&slope>0.1&&lines[i][2]>maxleft) maxleft=lines[i][2] ; 
        if(length>400&&slope>0.1&&lines[i][1]>maxlefty) maxlefty=lines[i][1] ; 
        if(length>400&&slope>0.1&&lines[i][1]<minlefty) minlefty=lines[i][1] ; 
        if(length>400&&slope>0.1&&lines[i][3]>maxlefty) maxlefty=lines[i][3] ; 
        if(length>400&&slope>0.1&&lines[i][3]<minlefty) minlefty=lines[i][3] ; 
        if(length>400&&slope<-0.1&&lines[i][0]<minright) minright=lines[i][0];          
        if(length>400&&slope<-0.1&&lines[i][0]>maxright) maxright=lines[i][0];          
        if(length>400&&slope<-0.1&&lines[i][2]>maxright) minright=lines[i][2];          
        if(length>400&&slope<-0.1&&lines[i][2]<minright) minright=lines[i][2];          
        if(length>400&&slope<-0.1&&lines[i][1]<minrighty) minrighty=lines[i][1];          
        if(length>400&&slope<-0.1&&lines[i][1]>maxrighty) maxrighty=lines[i][1];          
        if(length>400&&slope<-0.1&&lines[i][3]>maxrighty) maxrighty=lines[i][3];          
        if(length>400&&slope<-0.1&&lines[i][3]<minrighty) minrighty=lines[i][3];          


        if(/*length>400&&*/slope>0.1&&l==0) l=1; 
        if(/*length>400&&*/slope<-0.1&&r==0) r=1; 
        if(/*length>400&&*/slope<0.1&&slope>-0.1&&f==0) f=1;

        printf("\n %f %lf \n",-(float)(lines[i][3]-lines[i][1])/(lines[i][2]-lines[i][0]),length);

        if(f==1&&r==1&&l==1) count=3;
        if((f==0&&r==1&&l==1)|| (f==1&&r==1&&l==0) || (f==1&&r==0&&l==1)) count=2;
        if(f==0&&r==0&&l==1 || (f==0&&r==1&&l==0) || (f==1&&r==0&&l==0)) count=1;

    }
         printf("\n%d l=%d f=%d r=%d\n",count,l,f,r );

         if(maxlefty-minlefty>maxrighty-minrighty) flag=0;
         else flag=1;

         if(count==3)
         {
          pos= (maxright+maxleft+minright+minleft)/4;
          if(pos-img.cols>0) printf("\n right\n");
          else printf("\n left\n");
         }

         if(count==2)
         {
          if(f==1&&l==1) {printf("\n right\n");}
          if(f==1&&r==1) {printf("\n left\n");}
          if(l==1&&r==1) {printf("straight");}
          }

          if(count==1)
          {
            if(l==1) printf("right");
            if(r==1) printf("\n left\n");
            if(f==1) if (flag)
            {
              printf("\n  right  \n");
            }
            else printf("\n left  \n");
          }


imshow("win",fres);

  }

	waitKey(0);

	return 0;
}


/*void call(int a,void* t)
{

	Canny(img,result,a,3*a,3);
	Mat fres(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
	float slope;
	double length;
	int l=0,f=0,r=0,count=0,maxleft=0,minleft=img.cols/2,maxright=0,minright=img.cols/2,pos;
	
	vector<Vec4i> lines;
  	int i;
  	count=0;

    HoughLinesP( result, lines, 1, CV_PI/180, 80, 30, 120);
    for(i = 0; i < lines.size(); i++ )
    {
         line( fres, Point(lines[i][0], lines[i][1]),
         Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
         slope=-(float)(lines[i][3]-lines[i][1])/(lines[i][2]-lines[i][0]);
         length=sqrt(pow((double)(lines[i][3]-lines[i][1]),2.0)+pow((double)(lines[i][2]-lines[i][0]),2.0));

		 if(length>400&&slope>0.1&&lines[i][0]<minleft) minleft=lines[i][0] ; 
		 if(length>400&&slope>0.1&&lines[i][0]>maxleft) maxleft=lines[i][0] ; 
		 if(length>400&&slope>0.1&&lines[i][2]<minleft) minleft=lines[i][2] ; 
		 if(length>400&&slope>0.1&&lines[i][2]>maxleft) maxleft=lines[i][2] ; 
         if(length>400&&slope<-0.1&&lines[i][0]<minright) minright=lines[i][0];          
         if(length>400&&slope<-0.1&&lines[i][0]>maxright) maxright=lines[i][0];          
         if(length>400&&slope<-0.1&&lines[i][2]>maxright) minright=lines[i][2];          
         if(length>400&&slope<-0.1&&lines[i][2]<minright) minright=lines[i][2];          

         if(/*length>400&&*///slope>0.1&&l==0) l=1; 
         //if(/*length>400&&*///slope<-0.1&&r==0) r=1; 
         //if(/*length>400&&*///slope<0.1&&slope>-0.1&&f==0) f=1;

        /* printf("\n %f %lf \n",-(float)(lines[i][3]-lines[i][1])/(lines[i][2]-lines[i][0]),length);

         if(f==1&&r==1&&l==1) count=3;
         if((f==0&&r==1&&l==1)|| (f==1&&r==1&&l==0) || (f==1&&r==0&&l==1)) count=2;
         if(f==0&&r==0&&l==1 || (f==0&&r==1&&l==0) || (f==1&&r==0&&l==0)) count=1;

    }
         printf("\n%d l=%d f=%d r=%d\n",count,l,f,r );

         if(count==3)
         {
         	pos= (maxright+maxleft+minright+minleft)/4;
         	if(pos-img.cols>0) printf("\n right\n");
         	else printf("\n left\n");
         }

         if(count==2)
         {
         	if(f==1&&l==1) {printf("\n right\n");}
         	if(f==1&&r==1) {printf("\n left\n");}
         	if(l==1&&r==1) {printf("straight");}
          }

          if(count==1)
          {
          	if(l==1) printf("right");
          	if(r==1) printf("\n left\n");
          	if(f==1) printf("\n ruko\n");
          }


imshow("win",fres);


}*/
