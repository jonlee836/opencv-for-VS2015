#include "analyzePoints.h"

using namespace cv;
using namespace std;
	
Point analyzePoints::getMidpoint(Point a, Point b){  
  return Point((a.x+b.x)/2, (a.y+b.y)/2);
}