#include "Util.h"
//!definition of Color members
Color::Color() {
	red = blue = green = 0;
}
Color::Color(GLubyte r, GLubyte g, GLubyte b) {
	red = r;
	blue = b;
	green = g;

}


//!definition of Point members
Point::Point() {
	x = y = 0;
}
Point::Point(int _x, int _y) :x(_x), y(_y) {

}
double Point::distance(const Point& _point) {
	return sqrt(static_cast<double>(squaredDistance(_point)));
}

long long Point::squaredDistance(const Point& _point) {
	long long xsquare = static_cast<long long>(_point.x - x) * static_cast<long long>(_point.x - x);
	long long ysquare = static_cast<long long>(_point.y - y) * static_cast<long long>(_point.y - y);
	return (xsquare + ysquare);

}


//!definition of Line members
Line::Line() {
}
Line::Line(Point _start, Point _end) :start(_start), end(_end) {
}
double Line::length() {
	return start.distance(end);
}

//!definition of Circle members
Circle::Circle() :radius(0) {
}
Circle::Circle(Point p, int r) :center(p), radius(r) {
}

//!definition of GridPoint members
void GridPoint::setOn() {
	state = STATE_ON;
}
void GridPoint::setOff() {
	state = STATE_OFF;
}
void GridPoint::toggle() {
	state = !state;
}
GridPoint::GridPoint() {
	state = GridPoint::STATE_OFF;
}
GridPoint::GridPoint(bool _state, int _x, int _y) {
	x = _x;
	y = _y;
	state = _state;
}


