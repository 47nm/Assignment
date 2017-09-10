#include "Util.h"
Color::Color() {
	red = blue = green = 0;
}
Color::Color(GLubyte r, GLubyte g, GLubyte b) {
	red = r;
	blue = b;
	green = g;

}


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


