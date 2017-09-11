#include <math.h>
#include "GridUtil.h"

# define M_PIl          3.141592653589793238462643383279502884L

using namespace std;
void markNearestGridPointsToCircle( SquareGrid* squareGrid,const Circle circle, int &_radiusOfOuterCircle, int  &_radiusOfInnerCircle) {

	//if squareGrid is null, then error should be thrown, but currently handling gracefully
	if (squareGrid == NULL){
		_radiusOfOuterCircle = _radiusOfInnerCircle = 0;
		return;
	}
	
	Point pointOnCircle;
	float thetaIncrement = (float)squareGrid->pitch/(circle.radius!=0?circle.radius:1)/2 ;
	double radiusOfOuterCircle = 0.0,radiusOfInnerCircle = DBL_MAX;
	double temp=0.0 ;
	// for each(at a certain interval) point on circumference. find the nearest grid point.
	for (float theta = 0; theta < 2 * M_PIl; theta += thetaIncrement) {
		int indexOfX, indexOfY;
		pointOnCircle.x = circle.center.x + circle.radius*cos(theta);
		pointOnCircle.y = circle.center.y + circle.radius*sin(theta);
		indexOfX = static_cast<int>(round((pointOnCircle.x - squareGrid->start.x) / squareGrid->pitch));
		indexOfY = static_cast<int>(round((pointOnCircle.y - squareGrid->start.y) / squareGrid->pitch));

		if (indexOfX < squareGrid->dots &&  indexOfY < squareGrid->dots && indexOfX >= 0 && indexOfY >= 0) {
			squareGrid->gridPoints[indexOfX][indexOfY].setOn();
			temp = squareGrid->gridPoints[indexOfX][indexOfY].squaredDistance(circle.center);
			if (radiusOfOuterCircle < temp)
				radiusOfOuterCircle = temp;
			if (radiusOfInnerCircle > temp)
				radiusOfInnerCircle = temp;
		}
			
	}
	_radiusOfOuterCircle = static_cast<int>(sqrt(radiusOfOuterCircle));
	_radiusOfInnerCircle = static_cast<int>(sqrt(radiusOfInnerCircle));
	//since grid has been changed, notify the observers to show it on display.
	squareGrid->notifyObservers();
}

Circle equateBestFitCircle(SquareGrid* squareGrid) {
	
	const int maxIterations = 256;
	const double tolerance = 1e-06;
	double centerX=0.0, centerY=0.0, radius =0.0;
	double xAvr = 0.0, yAvr = 0.0;
	int countOfPoints =0;
	vector<GridPoint> allpoints;
	//if squareGrid is null, then error should be thrown, but currently handling gracefully
	if (squareGrid == NULL)
		return Circle();
	//taking average of all Xs, and Ys for initial guess
	for (auto& row : squareGrid->gridPoints) {
		for (auto& col : row) {
			if (col.state == GridPoint::STATE_ON) {
				xAvr += col.x;
				yAvr += col.y;
				countOfPoints++;
				allpoints.push_back(col);
			}
		}
	}
	xAvr /= countOfPoints;
	yAvr /= countOfPoints;
	centerX = xAvr;
	centerY = yAvr;


	//multiple iteration for least square best fit algo to calculate center and radius 
	for (int j = 0; j < maxIterations; j++) {
		/* update the iterates */
		double tempX = centerX;
		double tempY = centerY;

		/* compute average L, dL/da, dL/db */
		double LAvr = 0.0;
		double LaAvr = 0.0;
		double LbAvr = 0.0;

		for (int i = 0; i < countOfPoints; i++) {
			double dx = allpoints[i].x - centerX;
			double dy = allpoints[i].y - centerY;
			double L = sqrt(dx * dx + dy * dy);
			if (fabs(L) > tolerance) {
				LAvr += L;
				LaAvr -= dx / L;
				LbAvr -= dy / L;
			}
		}
		LAvr /= countOfPoints;
		LaAvr /= countOfPoints;
		LbAvr /= countOfPoints;

		centerX = xAvr + LAvr * LaAvr;
		centerY = yAvr + LAvr * LbAvr;
		radius = LAvr;

		if (fabs(centerX - tempX) <= tolerance && fabs(centerY - tempY) <= tolerance)
			break;
	}

	return Circle(Point(static_cast<int>(centerX), static_cast<int>(centerY)),radius);
}