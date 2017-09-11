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
	Point();
	Point(int _x, int _y);
	double distance(const Point& _point);
	long long squaredDistance(const Point& _point);
};

//represents a grid point.
class GridPoint: public Point{
	
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
	Line();
	Line(Point _start, Point _end);
	double length();
};

class Circle {
public:
	Point center;
	int radius;
	Circle();
	Circle(Point p, int r);

};
#endif

