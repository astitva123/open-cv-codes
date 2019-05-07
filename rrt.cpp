#include "stdio.h"
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/contrib/contrib.hpp"

using namespace cv;
using namespace std;

typedef struct
{
  int x;
  int y;
}coordi;

struct Node1 {
    vector<Node1 *> children;
    Node1 *parent;
    coordi position;
};

Node1 start_node1;
Node1 end_node1;
Mat img;
Node1* node1s[5000];
int totnode1s = 0;
int reached = 0;
int step_size = 10;
int iter = 0;

void init()
{
    start_node1.position.x = 50;
    start_node1.position.y = 50;
    start_node1.parent = NULL;
    for(int i=start_node1.position.x - 5; i < start_node1.position.x + 5; i++)
    {
      for(int j=start_node1.position.y - 5; j < start_node1.position.y + 5; j++)
      {
        img.at<Vec3b>(i, j)[0] = 255;
        img.at<Vec3b>(i, j)[1] = 0;
        img.at<Vec3b>(i, j)[2] = 0;
      }
    }
    node1s[totnode1s++] = &start_node1;
    end_node1.position.x = 350;
    end_node1.position.y = 350;
    for(int i=end_node1.position.x - 5; i < end_node1.position.x + 5; i++)
    {
      for(int j=end_node1.position.y - 5; j < end_node1.position.y + 5; j++)
      {
        img.at<Vec3b>(i, j)[0] = 0;
        img.at<Vec3b>(i, j)[1] = 0;
        img.at<Vec3b>(i, j)[2] = 255;
      }
    }
    srand(time(NULL));
}
float node1_dist(coordi p, coordi q)
{
  coordi v;
  v.x = p.x - q.x;
  v.y = p.y - q.y;
  return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
int near_node1(Node1 rnode1)
{
  float min_dist = 999.0, dist= node1_dist(start_node1.position, rnode1.position);
  int lnode1 = 0, i = 0;
  for(i=0; i<totnode1s; i++)
  {
    dist = node1_dist(node1s[i]->position, rnode1.position);
    if(dist<min_dist)
    {
      min_dist = dist;
      lnode1 = i;
    }
  }
  return lnode1;
}
coordi stepping(coordi nnode1, coordi rnode1)
{
  coordi interm, step;
  float magn = 0.0, x = 0.0, y = 0.0;
  interm.x = rnode1.x - nnode1.x;
  interm.y = rnode1.y - nnode1.y;
  magn = sqrt((interm.x)*(interm.x) + (interm.y)*(interm.y));
  x = (float)(interm.x / magn);
  y = (float)(interm.y / magn);
  step.x = (int)(nnode1.x + step_size*x);
  step.y = (int)(nnode1.y + step_size*y);
  return step;
}
int check_validity_1(coordi p, coordi q)
{
  coordi large, small;
  int i = 0, j1 = 0, j2 = 0;
  double slope;
  if(q.x<p.x)
  {
    small = q;
    large = p;
  }
  else
  {
    small = p;
    large = q;
  }
  if(large.x == small.x)
    return 0;
  slope = ((double)large.y - small.y)/((double)large.x - small.x);
  for(i=small.x+1; i<large.x; i++)
  {
    j1 = (int)((i*slope) - (small.x)*(slope) + small.y);
    j2 = j1 + 1;
    if((i<0) || (i>400) || (j1<0) || (j1>400) || (j2<0) || (j2>400))
      continue;
    if(((int)img.at<Vec3b>(i, j1)[0] <250) && ((int)img.at<Vec3b>(i, j1)[1] < 250) && ((int)img.at<Vec3b>(i, j1)[2] < 250))
     return 0;
     if(((int)img.at<Vec3b>(i, j2)[0] <250) && ((int)img.at<Vec3b>(i, j2)[1] < 250) && ((int)img.at<Vec3b>(i, j2)[2] < 250))
      return 0;
  }
  return 1;
}
int check_validity_2(coordi p, coordi q)
{
  coordi large, small;
  int i = 0, j1 = 0, j2 = 0;
  double slope;
  if(q.y<p.y)
  {
    small = q;
    large = p;
  }
  else
  {
    small = p;
    large = q;
  }
  if(large.x == small.x)
    return 0;
  slope = ((double)large.y - small.y)/((double)large.x - small.x);
  for(i=small.y+1; i<large.y; i++)
  {
    j1 = (int)(((i - small.y)/slope) + small.x);
    j2 = j1 + 1;
    if((i<0) || (i>400) || (j1<0) || (j1>400) || (j2<0) || (j2>400))
      continue;
    if(((int)img.at<Vec3b>(j1, i)[0] <250) && ((int)img.at<Vec3b>(j1, i)[1] < 250) && ((int)img.at<Vec3b>(j1, i)[2] < 250))
     return 0;
     if(((int)img.at<Vec3b>(j2, i)[0] <250) && ((int)img.at<Vec3b>(j2, i)[1] < 250) && ((int)img.at<Vec3b>(j2, i)[2] < 250))
      return 0;
  }
  return 1;
}
void draw_path()
{
  Node1 up, down;
  int breaking = 0;
  down = end_node1;
  up = *(end_node1.parent);
  while(1)
  {
    line(img, Point(up.position.y, up.position.x), Point(down.position.y, down.position.x), Scalar(0, 255, 0), 2, 8);
    if(up.parent == NULL)
      break;
    up = *(up.parent);
    down = *(down.parent);
  }
}

void rrt()
{
  int flag1 = 0, index = 0, flag2 = 0;
    Node1* rnode1 = new Node1;
    Node1* stepnode1 = new Node1;
    (rnode1->position).x = rand() % 400 + 1;
    (rnode1->position).y = rand() % 400 + 1;
    index = near_node1(*rnode1);
    if((node1_dist(rnode1->position, node1s[index]->position)) < step_size)
      return;
    else
      stepnode1->position = stepping(node1s[index]->position, rnode1->position);
    flag1 = check_validity_1(node1s[index]->position, stepnode1->position);
    flag2 = check_validity_2(node1s[index]->position, stepnode1->position);
    if((flag1 == 1) && (flag2 == 1))
    {
      node1s[totnode1s++] = stepnode1;
      stepnode1->parent = node1s[index];
      (node1s[index]->children).push_back(stepnode1);
      line(img, Point((stepnode1->position).y, (stepnode1->position).x), Point(node1s[index]->position.y, node1s[index]->position.x), Scalar(0, 255, 255), 2, 8);
      for(int i=stepnode1->position.x - 2; i < stepnode1->position.x + 2; i++)
      {
        for(int j=stepnode1->position.y - 2; j < stepnode1->position.y + 2; j++)
        {
          if((i<0) || (i>400) || (j<0) || (j>400))
            continue;

          img.at<Vec3b>(i, j)[0] = 0;
          img.at<Vec3b>(i, j)[1] = 255;
          img.at<Vec3b>(i, j)[2] = 0;
        }
      }
      if((check_validity_1(stepnode1->position, end_node1.position)) && (check_validity_2(stepnode1->position, end_node1.position)) && (node1_dist(stepnode1->position,end_node1.position) < step_size))
      {
        reached = 1;
        node1s[totnode1s++] = &end_node1;
        end_node1.parent = stepnode1;
        (node1s[totnode1s-1]->children).push_back(&end_node1);
        draw_path();
      }
    }
    iter++;
}

int main()
{
  img = imread("rrt.png", CV_LOAD_IMAGE_COLOR);
  init();
  while((reached == 0))
    rrt();

  namedWindow( "window", WINDOW_AUTOSIZE );
  imshow("window", img);
  imwrite("output.png", img);
  waitKey();
  return 0;
}
