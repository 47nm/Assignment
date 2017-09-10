
#include "MyCanvas.h"
#include <iostream>


MyCanvas::MyCanvas()
{
}

MyCanvas::~MyCanvas()
{
}


void MyCanvas::display()
{
    // Clear the canvas
    clear();

	if (mode == problem::problem1) {
		
		drawLine(line);
		drawCircle(actualCircle.center.x, actualCircle.center.y, static_cast<GLuint>(actualCircle.radius), 127, 0, 0);
		drawCircle(innerCircle.center.x, innerCircle.center.y, static_cast<GLuint>(innerCircle.radius), 0, 127, 0);
		drawCircle(outerCircle.center.x, outerCircle.center.y, static_cast<GLuint>(outerCircle.radius), 0, 127, 0);

	}
	else if (mode == problem::problem2) {

		//draw best fit circle 
		drawCircle(actualCircle.center.x, actualCircle.center.y, static_cast<GLuint>(actualCircle.radius), 127, 0, 0);
		
	}
	
	drawGrid();

    // -------------------------------------------------------------------------------------------
    // Make changes appear on screen
    swapBuffers();
}

void MyCanvas::onMouseButton(int button, int state, int x, int y)
{

    // Process mouse button events.
	switch (button) {
	case GLUT_LEFT_BUTTON:
		std::cout << "Canvas::onMouseButton: " << state << ", " << x << ", " << y << std::endl;
		switch (mode) {
		case problem::problem1:
			switch (mouseClickLastState)
			{
			case GLUT_UP:
				switch (state)
				{
				case GLUT_DOWN:
					line.start.x = x;
					line.start.y = y;
					line.end.x = x;
					line.end.y = y;
					squareGrid.clearGrid();
					actualCircle.radius = innerCircle.radius = outerCircle.radius = 0;
					mouseClickLastState = GLUT_DOWN;
					
					break;
				case GLUT_UP: // not possible
					break;
				}
			case GLUT_DOWN:
				switch (state)
				{
				case GLUT_UP:
					line.end.x = x;
					line.end.y = y;
					mouseClickLastState = GLUT_UP;
					drawNearestCircles(state);
					
					break;
				case GLUT_DOWN: // not possible
					break;
				}
			}
			break;
		case problem::problem2:
			if (state == GLUT_DOWN) {				
				squareGrid.toggleGridPoint(Point(x, y));
			}
			break;
		}

	}
	
	refresh();
}

void MyCanvas::onKeyboard(unsigned char key, int x, int y)
{
    // Process keyboard events.
    std::cout << "Canvas::onKeyboard: '" << key << "', " << x << ", " << y << std::endl;
    switch (key) {
    case 27: // ESC
        exit(0);
        break;
    case 'G':
	case 'g':
		if (mode == problem::problem2) {
			actualCircle = equateBestFitCircle(squareGrid);
		}
		break;
	case 'C':
	case 'c':
		line.end.x = line.start.x;
		line.end.y = line.start.y;
		innerCircle.radius = outerCircle.radius = actualCircle.radius = 0;
		squareGrid.clearGrid();
	default:
        break;
    }
    refresh();
}
