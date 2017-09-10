#include <math.h>
#include "GridUtil.h"

# define M_PIl          3.141592653589793238462643383279502884L

using namespace std;
void markNearestGridPointsToCircle( SquareGrid& squareGrid,const Circle& circle, int &_radiusOfOuterCircle, int  &_radiusOfInnerCircle) {
	
	Point pointOnCircle;
	float thetaIncrement = (float)squareGrid.pitch/(circle.radius!=0?circle.radius:1)/2 ;
	double radiusOfOuterCircle = 0.0,radiusOfInnerCircle = DBL_MAX;
	double temp=0.0 ;
	
	for (float theta = 0; theta < 2 * M_PIl; theta += thetaIncrement) {
		int indexOfX, indexOfY;
		pointOnCircle.x = circle.center.x + circle.radius*cos(theta);
		pointOnCircle.y = circle.center.y + circle.radius*sin(theta);
		indexOfX = static_cast<int>(round((pointOnCircle.x - squareGrid.start.x) / squareGrid.pitch));
		indexOfY = static_cast<int>(round((pointOnCircle.y - squareGrid.start.y) / squareGrid.pitch));

		if (indexOfX < squareGrid.dots &&  indexOfY < squareGrid.dots && indexOfX >= 0 && indexOfY >= 0) {
			squareGrid.gridPoints[indexOfX][indexOfY].setOn();
			temp = squareGrid.gridPoints[indexOfX][indexOfY].squaredDistance(circle.center);
			if (radiusOfOuterCircle < temp)
				radiusOfOuterCircle = temp;
			if (radiusOfInnerCircle > temp)
				radiusOfInnerCircle = temp;
		}
			
	}
	_radiusOfOuterCircle = static_cast<int>(sqrt(radiusOfOuterCircle));
	_radiusOfInnerCircle = static_cast<int>(sqrt(radiusOfInnerCircle));
	squareGrid.notifyObservers();
}

