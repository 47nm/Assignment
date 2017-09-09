#ifndef GridUtil_h
#define GridUtil_h
#include "glut.h"

class Color {
public:
	GLubyte red;
	GLubyte blue;
	GLubyte green;

	Color();
	Color(GLubyte r, GLubyte g, GLubyte b);
};


//represents a grid point.
class GridPoint {
	// there is no invariant on point hence no getter and setters


public:
	bool state;
	int x, y;
	const static bool STATE_ON = true;
	const static bool STATE_OFF = false;
	void setOn();
	void setOff();
	void toggle();
	GridPoint();
	GridPoint(bool, int, int);
	

};


#endif

