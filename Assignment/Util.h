#ifndef Util_h
#define Util_h
#include <math.h>
#include "glut.h"


enum problem {
	problem1,
	problem2
};


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
		return sqrt(static_cast<double>(squaredDistance(_point)));
	}
	long long squaredDistance(const Point& _point) {
		long long xsquare = static_cast<long long>(_point.x - x) * static_cast<long long>(_point.x - x);
		long long ysquare = static_cast<long long>(_point.y - y) * static_cast<long long>(_point.y - y);
		return (xsquare + ysquare);
		
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
	Line(){
	}
	Line(Point _start, Point _end) :start(_start), end(_end) {
	}
	double length() {
		return start.distance(end);
	}
};

class Circle {
public:
	Point center;
	int radius;
	Circle():radius(0){
	}
	Circle(Point p, int r):center(p),radius(r) {
	}

};
#endif

