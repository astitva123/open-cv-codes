#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

int m(int,int,Mat);
int n(int,int,Mat);

int main()
{
	
	int i,j,cx,cy,flag=0,cxt,cyt,vy,vx;
	//float r1,g1,b1;
	Mat img,temp;

	VideoCapture vid("AirHockey.mp4");

	  vector <vector<Point> > contours;
	  vector <vector<Point> > contourst;
  	  vector <Vec4i> hierarchy;
  	  Moments m1;
  	  Moments m2;

while (1)
{

vid>>img;

Mat himg;
Mat ans(img.rows,img.cols,CV_8UC1,Scalar(0));

cvtColor(img,himg,CV_RGB2HSV);							
Mat result(himg.rows,himg.cols,CV_8UC1,Scalar(0));
Mat fres(result.rows,result.cols,CV_8UC1,Scalar(0));

namedWindow("win",WINDOW_NORMAL);
namedWindow("win1",WINDOW_NORMAL);
namedWindow("winedge",WINDOW_NORMAL);

imshow("win1",himg);

for(i=0;i<himg.rows;i++)
{
	for(j=0;j<himg.cols;j++)
	{
		if(himg.at<Vec3b>(i,j)[2]>=40&&himg.at<Vec3b>(i,j)[2]<=243&&himg.at<Vec3b>(i,j)[1]>=105&&himg.at<Vec3b>(i,j)[1]<=255&&himg.at<Vec3b>(i,j)[0]>=0&&himg.at<Vec3b>(i,j)[0]<=45) fres.at<uchar>(i,j)={255};
		else fres.at<uchar>(i,j)={0};
	}

}

for(i=1;i<fres.rows-1;i++)
	{
		for(j=1;j<fres.cols-1;j++)
		{
			result.at<uchar>(i,j)=m(i,j,fres);
		}
	}

	for(i=1;i<fres.rows-1;i++)
	{
		for(j=1;j<fres.cols-1;j++)
		{
			fres.at<uchar>(i,j)=m(i,j,result);
		}
	}

	for(i=1;i<fres.rows-1;i++)
	{
		for(j=1;j<fres.cols-1;j++)
		{
			result.at<uchar>(i,j)=n(i,j,fres);
		}
	}

	for(i=1;i<fres.rows-1;i++)
	{
		for(j=1;j<fres.cols-1;j++)
		{
			fres.at<uchar>(i,j)=n(i,j,result);
		}
	}

	Canny(fres,result,50,150,3);

	imshow("winedge",result);

	for(i=1;i<fres.rows-1;i++)
	{
		for(j=1;j<fres.cols-1;j++)
		{
			fres.at<uchar>(i,j)=m(i,j,result);
		}
	}

	for(i=1;i<fres.rows-1;i++)
	{
		for(j=1;j<fres.cols-1;j++)
		{
			result.at<uchar>(i,j)=m(i,j,fres);
		}
	}

	/*for(i=1;i<fres.rows-1;i++)
	{
		for(j=1;j<fres.cols-1;j++)
		{
			fres.at<uchar>(i,j)=m(i,j,result);
		}
	}*/

	findContours(fres,contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	Mat contour(result.rows,result.cols,CV_8UC1,Scalar(0));
	
	double area;

	for(i=0;i<contours.size();i++)
	{	
		m1=moments(contours[i]);

		area=contourArea(contours[i]);
		cx = (int)(m1.m10/m1.m00);
		cy = (int)(m1.m01/m1.m00);
        
    	if(area>150&&area<900&&(cy<520)&&cy>235&&cx>410)//||(area>600&&area<1100))
    	{
    		printf("\n %lf\n",area);
    		
    		if(cx>625&&cx<665&&cy>350&&cy<400)continue;
    		else drawContours(contour,contours,i, 255, 2, 8);
    		
    		//break;
    	}
    	
    }

    printf("\n%d\n",(int)contourst.size()); 
   // contourst.reserve(contours.size());

    printf("\n%d\n",(int)contourst.size());
    printf("\n%d\n",(int)contours.size());  

    if(flag==0)
    {
    	contourst=contours;

    	//for(i=0;i<contours.size();i++) contourst[i].push_back(contours[i]);
    		printf("\n%d\n",(int)contourst.size()); 

    }

	printf("\n%d\n",(int)contourst.size()); 
	printf("yes");

    if(flag==1)
    {

    	
    		for(i=0;i<contours.size();i++)
	    	{

	    		if(area>150&&area<900)//&&(cy<520)&&cy>235&&cx>410)
    			{

	    		m1=moments(contours[i]);
	    		m2=moments(contourst[i]);

	    		cx = (int)(m1.m10/m1.m00);
				cy = (int)(m1.m01/m1.m00);

				cxt = (int)(m2.m10/m2.m00);
				cyt = (int)(m2.m01/m2.m00);

				if(cy<520&&cyt<520&&cy>235&&cyt>235&&cx>140&&cxt>140)
				{
					if(cx>625&&cx<665&&cy>350&&cy<400&&cxt>625&&cxt<665&&cyt>350&&cyt<400)
					{
						if(cxt>cx)
						{
							vx=cxt-cx;
							vy=cyt-cy;

							if(vy>0)
							{
								if((140-cx)*vy/vx<520-cy)  ans.at<uchar>((cx-140)*vy/vx+cy,140)=255;
								else 
								{
									ans.at<uchar>(520-(cx-140-(vx*(520-cy)/vy)),140)=255;
								}  
							}

							else
							{
								if((140-cx)*(-vy)/vx<cy-235)  ans.at<uchar>(cy-(cx-140)*(-vy)/vx,140)=255;
								else 
								{
									ans.at<uchar>(235-(cx-140-(vx*(235-cy)/(-vy))),140)=255;
								}	
							}
						}
					}
				}
	    		}
    		}

    	for(i=0;i<contours.size();i++) contourst=contours;//contourst[i].push_back(contours[i]);
    }


	imshow("win",contour);
	imshow("answer",ans);
	waitKey(0);
	printf("*************************************************************************************************************************************************\n");

	contour.copyTo(temp);
	flag=1;
}
	waitKey(0);


	return 0;
}



int m(int x,int y,Mat t)
{

	int i,j;
	
	for(i=-1;i<3;i++)
	for(j=-1;j<3;j++)
	{
		
		if (t.at<uchar>(x+i,y+j)==255) return 255;
	}

return 0;

}

int n(int x, int y,Mat t)
{

	int i,j;
	
	for(i=-1;i<3;i++)
	for(j=-1;j<3;j++)
	{
		
		if (t.at<uchar>(x+i,y+j)==0) return 0;
	}

return 255;
}