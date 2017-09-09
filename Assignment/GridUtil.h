#ifndef GridUtil_h
#define GridUtil_h
#include <math.h>
#include "glut.h"

class Color {
public:
	GLubyte red;
	GLubyte blue;
	GLubyte green;

	Color();
	Color(GLubyte r, GLubyte g, GLubyte b);
};

class Point {
public:
	int x, y;
	Point() {
		x = y = 0;
	}
	Point(int _x, int _y) :x(_x), y(_y) {

	}
	double distance(const Point& _point) {
		double xsquare = static_cast<double>(_point.x - x) * static_cast<double>(_point.x - x);
		double ysquare = static_cast<double>(_point.y - y) * static_cast<double>(_point.y - y);
		double value = sqrt(xsquare + ysquare);
		return value;
	}
};

//represents a grid point.
class GridPoint: public Point{
	// there is no invariant on point hence no getter and setters


public:
	bool state;
	const static bool STATE_ON = true;
	const static bool STATE_OFF = false;
	void setOn();
	void setOff();
	void toggle();
	GridPoint();
	GridPoint(bool, int, int);
	

};

class Line {
public:
	Point start, end;
	Line():start(Point()),end(Point()) {
	}
	Line(Point _start, Point _end) :start(_start), end(_end) {
	}
	double length() {
		return start.distance(end);
	}
};

#endif

